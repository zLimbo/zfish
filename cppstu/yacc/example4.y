%{
#include <stdio.h>
#include <string.h>

//在lex.yy.c里定义，会被yyparse()调用。在此声明消除编译和链接错误。
extern int yylex(void); 

// 在此声明，消除yacc生成代码时的告警
extern int yyparse(void); 

int yywrap()
{
	return 1;
}

// 该函数在y.tab.c里会被调用，需要在此定义
void yyerror(const char *s)
{
	printf("[error] %s\n", s);
}

int main()
{
	yyparse();
	return 0;
}

static int i = 0;
%}

%token NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

%%
commands: /* empty */
| commands command  {
	
	printf("\ti=%d\n", i++);
}
;

command: heat_switch | target_set ;

heat_switch:
TOKHEAT STATE
{
	printf("\tHeat turned on or off. i=%d\n", i++);
};

target_set: target_set2 
{
	printf("\ttarget_set2. i=%d\n", i++);
};

target_set2:
TOKTARGET TOKTEMPERATURE NUMBER
{
	printf("\tTemperature set. i=%d\n", i++);
};
%%