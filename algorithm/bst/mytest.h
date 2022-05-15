#ifndef __MYTEST_H__
#define __MYTEST_H__

#define COLOR(msg, code) "\033[1;" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

#endif // __MYTEST_H__
