#include <stdio.h>

// 内部定义【静态】全局变量
static int a1 = 10;

// 内部定义【非静态】全局变量
int a2 = 20;

// 声明外部变量
extern int b;

// 声明外部函数
extern void func_b(void);

// 内部定义的【静态】函数
static void func_a2(void)
{
    printf("in func_a2 \n");
}

// 内部定义的【非静态】函数
void func_a3(void)
{
    printf("in func_a3 \n");
}

// 被 main 调用
void func_a1(void)
{
    printf("in func_a1 \n");

    // 操作内部变量
    a1 = 11;
    a2 = 21;

    // 操作外部变量
    b  = 31;

    // 调用内部函数
    func_a2();
    func_a3();

    // 调用外部函数
    func_b();
}