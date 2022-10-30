template <typename R, typename... Arg>
class myfunction {
    typedef R (*F)(Arg...);

private:
    class __callbase {
    public:
        virtual R operator()(Arg... arg) = 0;
        virtual ~__callbase() {}
    };

    class __callable : public __callbase {
    public:
        __callable(F f) : functor(f) {}

        virtual R operator()(Arg... arg) {
            return functor(arg...);
        }

    private:
        F functor;
    };

    __callbase *base_;

public:
    R operator()(Arg... arg) {
        return (*base_)(arg...);  //这里调用基类对象的()操作符
    }

    myfunction(R (*f)(Arg...)) : base_(new __callable(f)) {}

    ~myfunction() {
        if (base_) {
            delete base_;
            base_ = nullptr;
        }
    }
};
