#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

// 声明外部变量
extern int a2;
extern void func_a1();

typedef void (*pfunc)(void);

int main(void)
{
    printf("in main \n");

    // 打印此进程的全局符号表
    void *handle = dlopen(0, RTLD_NOW);
    if (NULL == handle)
    {
        printf("dlopen failed! \n");
        return -1;
    }

    printf("\n------------ main ---------------\n");
    // 打印 main 中变量符号的地址
    pfunc addr_main = dlsym(handle, "main");
    if (NULL != addr_main)
        printf("addr_main = 0x%x \n", (unsigned int)addr_main);
    else
        printf("get address of main failed! \n");

    printf("\n------------ liba.so ---------------\n");
    // 打印 liba.so 中变量符号的地址
    unsigned int *addr_a1 = dlsym(handle, "a1");
    if (NULL != addr_a1)
        printf("addr_a1 = 0x%x \n", (unsigned int)addr_a1);
    else
        printf("get address of a1 failed! \n");

    unsigned int *addr_a2 = dlsym(handle, "a2");
    if (NULL != addr_a2)
        printf("addr_a2 = 0x%x \n", (unsigned int)addr_a2);
    else
        printf("get address of a2 failed! \n");

    // 打印 liba.so 中函数符号的地址
    pfunc addr_func_a1 = dlsym(handle, "func_a1");
    if (NULL != addr_func_a1)
        printf("addr_func_a1 = 0x%x \n", (unsigned int)addr_func_a1);
    else
        printf("get address of func_a1 failed! \n");

    pfunc addr_func_a2 = dlsym(handle, "func_a2");
    if (NULL != addr_func_a2)
        printf("addr_func_a2 = 0x%x \n", (unsigned int)addr_func_a2);
    else
        printf("get address of func_a2 failed! \n");

    pfunc addr_func_a3 = dlsym(handle, "func_a3");
    if (NULL != addr_func_a3)
        printf("addr_func_a3 = 0x%x \n", (unsigned int)addr_func_a3);
    else
        printf("get address of func_a3 failed! \n");


    printf("\n------------ libb.so ---------------\n");
    // 打印 libb.so 中变量符号的地址
    unsigned int *addr_b = dlsym(handle, "b");
    if (NULL != addr_b)
        printf("addr_b = 0x%x \n", *addr_b);
    else
        printf("get address of b failed! \n");

    // 打印 libb.so 中函数符号的地址
    pfunc addr_func_b = dlsym(handle, "func_b");
    if (NULL != addr_func_b)
        printf("addr_func_b = 0x%x \n", (unsigned int)addr_func_b);
    else
        printf("get address of func_b failed! \n");

    dlclose(handle);

    // 操作外部变量
    a2 = 100;
 
    // 调用外部函数
    func_a1();

    // 为了让进程不退出，方便查看虚拟空间中的地址信息
    while(1) sleep(5);
    return 0;
}