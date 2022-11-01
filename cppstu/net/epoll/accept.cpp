// 进程调用accept时会进入inet_csk_accept，这是accept的核心所在
struct sock *inet_csk_accept(struct sock *sk, int flags, int *err)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct sock *newsk;
	int error;

	lock_sock(sk);

	/* We need to make sure that this socket is listening,
	 * and that it has something pending.
	 */
	error = -EINVAL;
    // 确认socket处于监听状态
	if (sk-&gt;sk_state != TCP_LISTEN)
		goto out_err;

	/* Find already established connection */
    /*接下来要找到一个建立好的连接*/
	if (reqsk_queue_empty(&amp;icsk-&gt;icsk_accept_queue)) { // 如果sock的连接队列是空
		long timeo = sock_rcvtimeo(sk, flags &amp; O_NONBLOCK);

		/* If this is a non blocking socket don't sleep */
		error = -EAGAIN;
		if (!timeo) // 如果设置了非阻塞模式则直接返回，err是喜闻乐见的-EAGAIN
			goto out_err;
        // 如果处于阻塞模式，则进入inet_csk_wait_for_connect，进程将处于阻塞状态，直接到新到的连接唤醒
		error = inet_csk_wait_for_connect(sk, timeo);
		if (error)
			goto out_err;
	}
    // 到这里，连接队列会有至少一条可用连接用到返回
	newsk = reqsk_queue_get_child(&amp;icsk-&gt;icsk_accept_queue, sk);
	WARN_ON(newsk-&gt;sk_state == TCP_SYN_RECV);
out:
	release_sock(sk);
	return newsk;
out_err:
	newsk = NULL;
	*err = error;
	goto out;
}
EXPORT_SYMBOL(inet_csk_accept);

// inet_csk_wait_for_connect会将进程挂起，直到被新到的连接唤醒
static int inet_csk_wait_for_connect(struct sock *sk, long timeo)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	DEFINE_WAIT(wait); // 定义一个等待节点，用于挂在socket监听队列下
	int err;

	for (;;) {
        // 使用prepare_to_wait_exclusive确认互斥等待，在一个事件到达后内核只会唤醒等待队列中的一个进程
		prepare_to_wait_exclusive(sk_sleep(sk), &amp;wait,
					  TASK_INTERRUPTIBLE);
		release_sock(sk);
		if (reqsk_queue_empty(&amp;icsk-&gt;icsk_accept_queue))
            // 再一次判断队列是否空，空则进入调度，此时当前进程将被挂起
			timeo = schedule_timeout(timeo);
		lock_sock(sk);
		err = 0;
		if (!reqsk_queue_empty(&amp;icsk-&gt;icsk_accept_queue))
			break;
		err = -EINVAL;
		if (sk-&gt;sk_state != TCP_LISTEN)
			break;
		err = sock_intr_errno(timeo);
		if (signal_pending(current))
			break;
		err = -EAGAIN;
		if (!timeo)
			break;
	}
	finish_wait(sk_sleep(sk), &amp;wait);
	return err;
}