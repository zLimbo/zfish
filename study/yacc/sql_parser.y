%define api.pure
%locations
%no-lines
%verbose
%parse-param {struct _ParseResult* result}
%lex-param { YYLEX_PARAM }
%{
#include <stdint.h>
#include <ctype.h>
#include "sc_parse_node.h"
#include "sc_non_reserved_keywords.h"
#define YYLEX_PARAM result->yyscan_info_

%}
%union
{
    struct _ParseNode*     node;
    const struct _NonReservedKeyword *non_reserved_keyword;
    int ival;
}

%{
#include <stdio.h>
#include "sql_parser.lex.h"

extern void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s,...);

extern ParseNode* merge_tree(void *malloc_pool, ScItemType node_tag, ParseNode* source_tree);

extern ParseNode* new_terminal_node(void *malloc_pool, ScItemType type);

extern ParseNode* new_non_terminal_node(void *malloc_pool, ScItemType node_tag, int num, ...);

extern char* copy_expr_string(ParseResult* p, int expr_start, int expr_end);

extern ParseNode* new_node(void *malloc_pool, ScItemType type, int num);


#define ISSPACE(c) ((c) == ' ' || (c) == '\n' || (c) == '\r' || (c) == '\t' || (c) == '\f' || (c) == '\v')

#define malloc_terminal_node(node, malloc_pool, type) \
do \
{ \
  if ((node = new_terminal_node(malloc_pool, type)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for malloc"); \
    YYABORT; \
  } \
} while(0)

#define malloc_non_terminal_node(node, malloc_pool, node_tag, ...) \
do \
{ \
  if ((node = new_non_terminal_node(malloc_pool, node_tag, ##__VA_ARGS__)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for malloc"); \
    YYABORT; \
  } \
} while(0)

#define merge_nodes(node, malloc_pool, node_tag, source_tree) \
do \
{ \
  if (source_tree == NULL) \
  { \
    node = NULL; \
  } \
  else if ((node = merge_tree(malloc_pool, node_tag, source_tree)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for merging nodes"); \
    YYABORT; \
  } \
} while (0)

#define dup_expr_string(str_ptr, result, expr_start, expr_end) \
  do \
  { \
    str_ptr = NULL; \
    int start = expr_start; \
    while (start <= expr_end && ISSPACE(result->input_sql_[start - 1])) \
      start++; \
    if (start >= expr_start \
      && (str_ptr = copy_expr_string(result, start, expr_end)) == NULL) \
    { \
      yyerror(NULL, result, "No more space for copying expression string"); \
      YYABORT; \
    } \
  } while (0)

#define malloc_new_node(node, malloc_pool, type, num) \
do \
{ \
  if ((node = new_node(malloc_pool, type, num)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for mallocing"); \
    return ERROR; \
  } \
} while (0)
%}


%token <node> NAME
%token <node> SCAN_HEIGHT
%token <node> STRING
%token <node> INTNUM
%token <node> DATE_VALUE
%token <node> HINT_VALUE
%token <node> BOOL
%token <node> APPROXNUM
%token <node> NULLX
%token <node> UNKNOWN
%token <node> QUESTIONMARK
%token <node> SYSTEM_VARIABLE
%token <node> TEMP_VARIABLE
%token <node> FILENAME

%left	UNION EXCEPT
%left	INTERSECT
%left	OR
%left	AND
%right NOT
%left COMP_LE COMP_LT COMP_EQ COMP_GT COMP_GE COMP_NE
%left CNNOP
%left LIKE
%nonassoc BETWEEN
%nonassoc IN
%nonassoc IS NULLX BOOL UNKNOWN
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%right UMINUS
%left '(' ')'
%left '.'
%token VERSION USERS PARTICIPANTS PARTICIPANT CONSENSUS_PROTOCAL DEPTH
%token ADD AND ANY ALL ALTER AS ASC
%token BETWEEN BEGI BIGINT BINARY BOOLEAN BOTH BY
%token CASCADE CASE CHARACTER CLUSTER CNNOP COMMENT COMMIT
       CONSISTENT COLUMN COLUMNS CREATE CREATETIME
       CURRENT_USER CHANGE_OBI SWITCH_CLUSTER
%token DATE DATETIME DEALLOCATE DECIMAL DEFAULT DELETE DESC DESCRIBE
       DISTINCT DOUBLE DROP DUAL
%token ELSE END END_P ERROR EXCEPT EXECUTE EXISTS EXPLAIN
%token FLOAT FOR FROM FULL FROZEN FORCE
%token GLOBAL GLOBAL_ALIAS GRANT GROUP
%token HAVING HINT_BEGIN HINT_END HOTSPOT HEIGHT TO
%token IDENTIFIED IF IN INNER INTEGER INTERSECT INSERT INTO IS
%token JOIN JSON
%token KEY
%token LEADING LEFT LIMIT LIKE LOCAL LOCKED
%token MEDIUMINT MEMORY MOD MODIFYTIME MASTER MODE
%token NOT NUMERIC
%token OFFSET ON OR ORDER OPTION OUTER
%token PARAMETERS PASSWORD PRECISION PREPARE PRIMARY
%token READ_STATIC REAL RENAME REPLACE RESTRICT PRIVILEGES REVOKE RIGHT RESET
       ROLLBACK KILL READ_CONSISTENCY
%token SCHEMA SCOPE SELECT INVOKE SESSION SESSION_ALIAS CHECK HISTORY DEPLOY TRACE GET
       SET SHOW SMALLINT SNAPSHOT SPFILE START STATIC SYSTEM STRONG SET_MASTER_CLUSTER SET_SLAVE_CLUSTER SLAVE SCAN
%token TABLE TABLES CONTRACT CONTRACTS THEN TIME TIMESTAMP TINYINT TRAILING TRANSACTION CHAIN OFFCHAIN BLOCK BLOCKS_INFO
%token UNION UPDATE USER USING 
%token VALUES VARCHAR VARBINARY
%token WHERE WHEN WITH WORK PROCESSLIST QUERY CONNECTION WEAK

%token <non_reserved_keyword>
       AUTO_INCREMENT CHUNKSERVER COMPRESS_METHOD CONSISTENT_MODE
       EXPIRE_INFO GRANTS JOIN_INFO
       MERGESERVER REPLICA_NUM ROOTSERVER ROW_COUNT SERVER SERVER_IP
       SERVER_PORT SERVER_TYPE STATUS TABLE_ID TABLET_BLOCK_SIZE TABLET_MAX_SIZE
       UNLOCKED UPDATESERVER USE_BLOOM_FILTER VARIABLES VERBOSE WARNINGS

%type <node> sql_stmt stmt_list stmt
%type <node> select_stmt check_stmt invoke_stmt deploy_stmt trace_stmt get_stmt insert_stmt reset_stmt update_stmt //delete_stmt history_stmt
%type <node> create_table_stmt drop_table_stmt//create_contract_stmt opt_table_option_list table_option
%type <node> table_list 
//%type <node> explain_stmt explainable_stmt kill_stmt
%type <node> expr_list expr expr_const  simple_expr //arith_expr
%type <node> column_ref
%type <node> func_expr //in_expr case_expr
//%type <node> case_arg when_clause_list when_clause case_default
//%type <node> update_asgn_list update_asgn_factor
%type <node> contract_element_list contract_element function_definition //column_definition table_element_list table_element
%type <node> data_type opt_if_exists//opt_if_not_exists 
%type <node> replace_or_insert opt_insert_columns column_list
%type <node> insert_vals_list insert_vals int_param
%type <node> select_no_parens select_with_parens //select_clause
%type <node> simple_select select_expr_list param_list //no_table_select select_limit
%type <node> opt_where opt_history_range opt_groupby opt_having //opt_order_by order_by
//%type <node> opt_select_limit limit_expr opt_for_update
//%type <node> opt_asc_desc sort_list sort_key
%type <node> opt_distinct projection param //distinct_or_all
%type <node> from_list table_factor relation_factor joined_table
%type <node> join_type join_outer
%type <node> opt_float opt_time_precision opt_char_length opt_int_length opt_decimal opt_precision
//%type <node> opt_equal_mark opt_verbose
%type <node> opt_column_attribute_list column_attribute
%type <node> show_stmt opt_show_condition opt_like_condition
//%type <node> prepare_stmt stmt_name preparable_stmt
//%type <node> variable_set_stmt var_and_val_list var_and_val to_or_eq
//%type <node> execute_stmt argument_list argument opt_using_args
//%type <node> deallocate_prepare_stmt deallocate_or_drop
//%type <ival> opt_drop_behavior opt_full opt_scope
%type <node> create_user_stmt user_specification user_specification_list user password
%type <node> user_list //drop_user_stmt
%type <node> set_password_stmt opt_for_user
//%type <node> rename_user_stmt rename_info rename_list
//%type <node> lock_user_stmt lock_spec
%type <node> grant_stmt priv_type_list priv_type
//%type <node> revoke_stmt opt_on_priv_level
//%type <node> opt_limit opt_for_grant_user opt_flag opt_is_global
//%type <node> parameterized_trim
//%type <ival> opt_with_consistent_snapshot opt_config_scope
//%type <node> opt_work begin_stmt commit_stmt rollback_stmt
%type <node> alter_table_stmt alter_column_actions alter_column_action
//%type <node> opt_column alter_column_behavior
//%type <node> alter_system_stmt alter_system_actions alter_system_action
//%type <node> server_type opt_cluster_or_address opt_comment
%type <node> column_name relation_name function_name column_label chain_name contract_name scan_height mode_name//contract_function_name // 
%type <node> opt_hint opt_hint_list hint_option //opt_force
%type <node> opt_when //when_func when_func_stmt when_func_name
%type <non_reserved_keyword> unreserved_keyword
//%type <ival> consistency_level
%type <node> hint_options //opt_comma_list
%type <node> get_opt rules//gyc


%start sql_stmt
%%

sql_stmt:
    stmt_list END_P
    {
        merge_nodes($$, result->malloc_pool_, T_STMT_LIST, $1);
        result->result_tree_ = $$;
        YYACCEPT;
    }
  ;

stmt_list:
    stmt_list ';' stmt
    {
        if ($3 != NULL)
          malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
        else
          $$ = $1;
    }
  | stmt
    {
        $$ = ($1 != NULL) ? $1 : NULL;
    }
  ;

stmt:
    select_stmt       { $$ = $1; }
  | insert_stmt       { $$ = $1; }
  | alter_table_stmt  { $$ = $1; }
  | create_table_stmt { $$ = $1; }
  | check_stmt        { $$ = $1; }
  | invoke_stmt       { $$ = $1; }
  | trace_stmt        { $$ = $1; }
  | deploy_stmt       { $$ = $1; }
  | get_stmt          { $$ = $1; }
  | show_stmt         { $$ = $1; }
  | create_user_stmt  { $$ = $1; }
  | set_password_stmt { $$ = $1; }
  | grant_stmt        { $$ = $1; }
  | reset_stmt        { $$ = $1; }
  | drop_table_stmt   { $$ = $1; }
  | update_stmt       { $$ = $1; }
  ;

/*****************************************************************************
 *
 *	expression grammar
 *
 *****************************************************************************/

expr_list:
    expr
    {
        $$ = $1;
    }
  | expr_list ',' expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

column_ref:
    column_name
    { $$ = $1;}
  | relation_name '.' column_name
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, $3);
        dup_expr_string($$->str_value_, result, @3.first_column, @3.last_column);
    }
  | chain_name '.' relation_name '.' column_name
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 3, $1, $3, $5);
        dup_expr_string($$->str_value_, result, @5.first_column, @5.last_column);
    }
  | relation_name '.' '*'
    {
        ParseNode *node = NULL;
        malloc_terminal_node(node, result->malloc_pool_, T_STAR);
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, node);
    }
  | chain_name '.' relation_name '.' '*'
    {
        ParseNode *node = NULL;
        malloc_terminal_node(node, result->malloc_pool_, T_STAR);
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 3, $1, $3, node);
    }
  ;

expr_const:
  STRING {  }
  | DATE_VALUE { $$ = $1; }
  | INTNUM {  }
  | APPROXNUM {  }
  | BOOL {  }
  | NULLX {  }
  | QUESTIONMARK {  }
  | TEMP_VARIABLE {  }
  | SYSTEM_VARIABLE {  }
  | SESSION_ALIAS '.' column_name {  }
  ;

simple_expr:
    column_ref
    { $$ = $1; }
  | expr_const
    { $$ = $1; }
  | '(' expr ')'
    { $$ = $2; }
  | '(' expr_list ',' expr ')'
    {
        ParseNode* node = NULL;
        malloc_non_terminal_node(node, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);
        merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, node);
    }
  | func_expr
    {
        $$ = $1;
    }
  | select_with_parens	    %prec UMINUS
    {
        printf("select with parens in simple expr");
    }
  ;

/* used by the expression that use range value, e.g. between and */
//arith_expr:
//    simple_expr   {  }
//  | '+' arith_expr %prec UMINUS
//    {

//    }
//  | '-' arith_expr %prec UMINUS
//    {

//    }
//  | arith_expr '+' arith_expr {  }
//  | arith_expr '-' arith_expr {  }
//  | arith_expr '*' arith_expr {  }
//  | arith_expr '/' arith_expr {  }
//  | arith_expr '%' arith_expr {  }
//  | arith_expr '^' arith_expr {  }
//  | arith_expr MOD arith_expr {  }

expr:
    simple_expr   { $$ = $1; }
  | '+' expr %prec UMINUS
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);
    }
  | '-' expr %prec UMINUS
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);
    }
  | expr '+' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3); }
  | expr '-' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS, 2, $1, $3); }
  | expr '*' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3); }
  | expr '/' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3); }
  | expr '%' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3); }
  | expr '^' expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3); }
  | expr MOD expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3); }
  | expr COMP_LE expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LE, 2, $1, $3); }
  | expr COMP_LT expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LT, 2, $1, $3); }
  | expr COMP_EQ expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EQ, 2, $1, $3); printf("get expr = expr\n");}
  | expr COMP_GE expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GE, 2, $1, $3); }
  | expr COMP_GT expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GT, 2, $1, $3); }
  | expr COMP_NE expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NE, 2, $1, $3); }
  | expr LIKE expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 2, $1, $3); }
  | expr NOT LIKE expr { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_LIKE, 2, $1, $4); }
  | expr AND expr %prec AND
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_AND, 2, $1, $3);
    }
  | expr OR expr %prec OR
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_OR, 2, $1, $3);
    }
  | NOT expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT, 1, $2);
    }
  | expr IS NULLX
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);
    }
  | expr IS NOT NULLX
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);
    }
  | expr IS BOOL
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);
    }
  | expr IS NOT BOOL
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);
    }
  | expr IS UNKNOWN
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);
    }
  | expr IS NOT UNKNOWN
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);
    }
//  | expr BETWEEN arith_expr AND arith_expr	    %prec BETWEEN
//    {

//    }
//  | expr NOT BETWEEN arith_expr AND arith_expr	  %prec BETWEEN
//    {

//    }
//  | expr IN in_expr
//    {

//    }
//  | expr NOT IN in_expr
//    {

//    }
  | expr CNNOP expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_OP_CNN, 2, $1, $3);
    }
  ;

//in_expr:
//    select_with_parens
//    {

//    }
//  | '(' expr_list ')'
//    {  }
//  ;

//case_expr:
//    CASE case_arg when_clause_list case_default END
//    {

//    }
//  ;

//case_arg:
//    expr                  {  }
//  | /*EMPTY*/             {  }
//  ;

//when_clause_list:
//    when_clause
//    { }
//  | when_clause_list when_clause
//    {  }
//  ;

//when_clause:
//    WHEN expr THEN expr
//    {

//    }
//  ;

//case_default:
//    ELSE expr                { }
//  | /*EMPTY*/                {  }
//  ;

func_expr:
    function_name '(' '*' ')'
    {
        if(strcasecmp($1->str_value_,"count") != 0)
        {
            yyerror(&@1, result, "Only COUNT function can be with '*' parameter!");
            YYABORT;
        }
        else
        {
            ParseNode* node = NULL;
            malloc_terminal_node(node, result->malloc_pool_, T_STAR);
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 1, node);
        }
    }
//  | function_name '(' distinct_or_all expr ')'
//    {

//    }
  | function_name '(' expr_list ')'
    {

        if(strcasecmp($1->str_value_, "count") == 0)
        {
            // count only has one arg
            if($3->type_ == T_LINK_NODE)
            {
                yyerror(&@1,result, "COUNT function only support 1 parameter");
                YYABORT;
            }
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, NULL, $3);
        }
        else if(strcasecmp($1->str_value_, "sum") == 0)
        {
            if($3->type_ == T_LINK_NODE)
            {
                yyerror(&@1, result, "SUM function support 1 parameter");
                YYABORT;
            }
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, NULL, $3);
        }
        else if(strcasecmp($1->str_value_, "max") == 0)
        {
            if($3->type_ == T_LINK_NODE)
            {
                yyerror(&@1, result, "MAX function only support 1 parameter");
                YYABORT;
            }
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, NULL, $3);
        }
        else if(strcasecmp($1->str_value_, "min") == 0)
        {
            if($3->type_ == T_LINK_NODE)
            {
                yyerror(&@1, result, "MIN function only support 1 parameter");
                YYABORT;
            }
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, NULL, $3);
        }
        else if(strcasecmp($1->str_value_, "avg") == 0)
        {
            if($3->type_ == T_LINK_NODE)
            {
                yyerror(&@1, result, "AVG function only support 1 parameter");
                YYABORT;
            }
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, NULL, $3);
        }
        else /* system function */
        {
            ParseNode* params = NULL;
            merge_nodes(params, result->malloc_pool_, T_EXPR_LIST, $3);
            malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, params);
        }
    }
//  | function_name '(' expr AS data_type ')'
//    {

//    }
//  | function_name '(' parameterized_trim ')'
//    {

//    }
//  | function_name '(' ')'
//    {

//    }
  ;

//when_func:
//    when_func_name '(' when_func_stmt ')'
//    {

//    }
//;

//when_func_name:  
//    ROW_COUNT
//   {
//      malloc_non_terminal_node($$, result->malloc_pool_, T_ROW_COUNT, 1, NULL);
//    }
//  ;

//when_func_stmt:
//    select_stmt
//  | insert_stmt
//  | update_stmt
//  | delete_stmt
//  ;

//distinct_or_all:
//    ALL
//    {

//    }
//  | DISTINCT
//    {

//    }
//  ;


/*****************************************************************************
 *
 *	delete grammar
 *
 *****************************************************************************/

//delete_stmt:
//    DELETE FROM relation_factor opt_where opt_when
//    {

//    }
//  ;


/*****************************************************************************
 *
 *	update grammar
 *
 *****************************************************************************/

update_stmt:
     UPDATE SCAN HEIGHT SET int_param//contract_name
     {
         malloc_non_terminal_node($$, result->malloc_pool_, T_UPDATE, 1,
                                  $5     /* 1. scan_height */
                                  );
     }
   | UPDATE relation_factor ADD rules opt_insert_columns //VALUES insert_vals_list
     {
	 ParseNode* val_list = NULL;
	 malloc_new_node(val_list, result->malloc_pool_, T_STRING, 0);
	 val_list->str_value_ = strdup("ADD");
         malloc_non_terminal_node($$, result->malloc_pool_, T_UPDATE, 4,
				  $2,    /* 1. table name */
				  val_list,
				  $4,    /* 2. RULES */
				  $5    /* 2. rule column */
                    //              val_list     /* 3. rule value */
                                  );
     }
   | UPDATE relation_factor DELETE rules opt_insert_columns //VALUES insert_vals_list
     {
	 ParseNode* val_list = NULL;
	 malloc_new_node(val_list, result->malloc_pool_, T_STRING, 0);
	 val_list->str_value_ = strdup("DELETE");
         malloc_non_terminal_node($$, result->malloc_pool_, T_UPDATE, 4,
				  $2,    /* 1. table name */
				  val_list,
				  $4,    /* 2. RULES */
				  $5    /* 2. rule column */
                    //              val_list     /* 3. rule value */
                                  );
     }
;

/*****************************************************************************
 *
 *	get grammar
 *
*****************************************************************************/

get_stmt:
   GET get_opt column_label COMP_EQ INTNUM
   {
       ParseNode* t_project_list = NULL;
       ParseNode* t_project_item = NULL;
       ParseNode* t_ident1 = NULL;
       ParseNode* t_from_list = NULL;
       ParseNode* t_op_eq = NULL;

       /** 转大写 */
       char* tmp_char = $2->str_value_;
       for(int i=0;i<strlen(tmp_char);++i)
         tmp_char[i] = toupper(tmp_char[i]);

        if(0 == strcmp("TRANSACTION_DATA", $2->str_value_))
        {
            $2->str_value_ = strdup("transaction");
        }
        else if(0 == strcmp("BLOCK_DATA", $2->str_value_))
        {
            $2->str_value_ = strdup("block");
        }
        else
        {
            yyerror(NULL, result, "unrecognized column.");
        }

        malloc_new_node(t_ident1, result->malloc_pool_, T_STAR, 0);

        t_ident1->str_value_ = strdup("*");

        merge_nodes(t_project_item, result->malloc_pool_, T_PROJECT_ITEM, t_ident1);
        t_project_item->str_value_ = strdup("*");
        merge_nodes(t_project_list, result->malloc_pool_, T_PROJECT_LIST, t_project_item);

        merge_nodes(t_from_list, result->malloc_pool_, T_FROM_LIST, $2);

        malloc_non_terminal_node(t_op_eq, result->malloc_pool_, T_OP_EQ,2,
                                 $3,
                                 $5
                                 );
        malloc_non_terminal_node($$, result->malloc_pool_, T_GET,3,
                                 t_project_list,
                                 t_from_list,
                                 t_op_eq
                                 );
   }
 ;

get_opt:
   NAME
   {
     $$ = $1;
   }
 ;


/*****************************************************************************
 *
 *	trace grammar
 *
*****************************************************************************/

trace_stmt:
    TRACE opt_history_range NAME COMP_EQ STRING
    {
        ParseNode* t_project_list = NULL;
        ParseNode* t_project_item = NULL;
        ParseNode* t_ident1 = NULL;
        ParseNode* t_from_list = NULL;
        ParseNode* t_ident2 = NULL;
        ParseNode* t_op_and = NULL;
         ParseNode* t_op_eq = NULL;

         /** 转大写 */
         char* tmp_char = $3->str_value_;
         for(int i=0;i<strlen(tmp_char);++i)
           tmp_char[i] = toupper(tmp_char[i]);


         if(0 == strcmp("OPERATOR", $3->str_value_))
         {
             $3->str_value_ = strdup("caller");
         }
         else if(0 == strcmp("FUNCTION", $3->str_value_))
         {
             $3->str_value_ = strdup("func_name");
         }
         else
         {
             yyerror(NULL, result, "unrecognized column.");
         }

         malloc_new_node(t_ident1, result->malloc_pool_, T_STAR, 0);
         malloc_new_node(t_ident2, result->malloc_pool_, T_IDENT, 0);

         t_ident1->str_value_ = strdup("*");
         t_ident2->str_value_ = strdup("transaction");

         merge_nodes(t_project_item, result->malloc_pool_, T_PROJECT_ITEM, t_ident1);
         t_project_item->str_value_ = strdup("*");
         merge_nodes(t_project_list, result->malloc_pool_, T_PROJECT_LIST, t_project_item);

         merge_nodes(t_from_list, result->malloc_pool_, T_FROM_LIST, t_ident2);

        malloc_non_terminal_node(t_op_eq, result->malloc_pool_, T_OP_EQ,2,
                                 $3,
                                 $5
                                 );
        malloc_non_terminal_node(t_op_and, result->malloc_pool_, T_OP_AND,2,
                                 $2,
                                 t_op_eq
                                 );
        malloc_non_terminal_node($$, result->malloc_pool_, T_TRACE,3,
                                 t_project_list,
                                 t_from_list,
                                 t_op_and
                                 );
    }
  ;


/*****************************************************************************
 *
 *	create grammar
 *
 *****************************************************************************/

create_table_stmt:
//    CREATE TABLE opt_if_not_exists relation_factor '(' table_element_list ')'
//    opt_table_option_list
//    {

//    }
//  |
      CREATE TABLE relation_factor '(' contract_element_list ')'
    {
       ParseNode* contract_elements = NULL;
       merge_nodes(contract_elements, result->malloc_pool_, T_TABLE_ELEMENT_LIST, $5);
       malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_TABLE, 2,
                                $3,                        /* table name */
                                contract_elements         /*s */
                                );
    }
    |CREATE TABLE relation_factor '(' contract_element_list ')' WITH '(' MODE ':' mode_name ')' //Actually,this is mode_name 
    {
       ParseNode* contract_elements = NULL;
       merge_nodes(contract_elements, result->malloc_pool_, T_TABLE_ELEMENT_LIST, $5);
       malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_TABLE, 3,
                                $3,                        /* table name */
                                contract_elements,         /*s */
                                $11                        /* mode name */
                                );
    }
    |CREATE TABLE relation_factor '(' contract_element_list ')' WITH '(' mode_name ':' mode_name')'// gyc
    {
       ParseNode* contract_elements = NULL;
       merge_nodes(contract_elements, result->malloc_pool_, T_TABLE_ELEMENT_LIST, $5);
       malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_TABLE, 4,
                                $3,                        /* table name */
                                contract_elements,         /*s */
                                $9,                        /* contractTemplate */
				$11                       /* contractTemplate */
                                );
    };  //gyc
  

//create_contract_stmt:
//    CREATE CONTRACT relation_factor ON INTNUM '(' contract_element_list ')'
//    {

//    }
//   ;

//opt_if_not_exists:
//    IF NOT EXISTS
//    {  }
//  ;

//table_element_list:
//    table_element
//    {

//    }
//  | table_element_list ',' table_element
//    {

//    }
//  ;

contract_element_list:
    contract_element
    {
        $$ = $1;
    }
  | contract_element_list ',' contract_element
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

contract_element:
    function_definition
    {
        $$ = $1;
    }
  ;

function_definition:
     column_name data_type opt_column_attribute_list
     {
        ParseNode* attributes = NULL;
        merge_nodes(attributes, result->malloc_pool_, T_COLUMN_ATTRIBUTES, $3);
        malloc_non_terminal_node($$, result->malloc_pool_, T_FUNCTION_DEFINITION, 3, $1, $2, attributes);
     }
   ;

//table_element:
//    column_definition
//    {

//    }
//  | PRIMARY KEY '(' column_list ')'
//    {

//    }
//  ;

//column_definition:
//    column_name data_type opt_column_attribute_list
//    {

//    }
//  ;

data_type:
    TINYINT
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER); }
  | SMALLINT
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER); }
  | MEDIUMINT
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER); }
  | INTEGER opt_int_length
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER); }
  | BIGINT
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER); }
  | JSON
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_JSON); }
  | DECIMAL opt_decimal
    {
      malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);
    }
  | NUMERIC opt_decimal
    {
      malloc_terminal_node($$, result->malloc_pool_, T_TYPE_NUMERIC);
    }
  | BOOLEAN
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_BOOLEAN); }
  | FLOAT opt_float
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_FLOAT); }
  | REAL
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE); }
  | DOUBLE opt_precision
    {
        (void)($2);
        malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);
    }
  | TIMESTAMP opt_time_precision
    {
        if($2 == NULL)
            malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);
        else
            malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP, 1, $2);
    }
  | DATETIME opt_time_precision
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP); }
  | CHARACTER opt_char_length
    {
        if($2 == NULL)
            malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);
        else
            malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);
    }
  | BINARY opt_char_length
    {
        if($2 == NULL)
            malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);
        else
            malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);
    }
  | VARCHAR opt_char_length
    {
        if($2 == NULL)
            malloc_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR);
        else
            malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);
    }
  | VARBINARY opt_char_length
    {
        if($2 == NULL)
            malloc_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR);
        else
            malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);
    }
  | CREATETIME
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CREATETIME); }
  | MODIFYTIME
    { malloc_terminal_node($$, result->malloc_pool_, T_TYPE_MODIFYTIME); }
  | DATE
    {
        malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DATE);
        yyerror(&@1, result, "DATE type is not supported");
        YYABORT;
    }
  | TIME opt_time_precision
    {
        if ($2 == NULL)
          malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIME);
        else
          malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIME, 1, $2);
        yyerror(&@1, result, "TIME type is not supported");
        YYABORT;
    }
  ;

opt_decimal:
    '(' INTNUM ',' INTNUM ')'
    { $$ = NULL;}
  | '(' INTNUM ')'
    { $$ = NULL; }
  | /*EMPTY*/
    { $$ = NULL; }
  ;

opt_float:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_precision:
    PRECISION    { $$ = NULL; }
  | /*EMPTY*/    { $$ = NULL; }
  ;

opt_time_precision:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_char_length:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_int_length:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_column_attribute_list:
    opt_column_attribute_list column_attribute
    { malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2); }
  | /*EMPTY*/
    { $$ = NULL; }
  ;

column_attribute:
    NOT NULLX
    {
        (void)($2);
        malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);
    }
  | NULLX
    {
        (void)($1);
        malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);
    }
  | DEFAULT expr_const
    { $$ = NULL; }
  | AUTO_INCREMENT
    { $$ = NULL; }
  | PRIMARY KEY
    { malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_PRIMARY_KEY); }
  ;

//opt_table_option_list:
//    table_option
//    {

//    }
//  | opt_table_option_list ',' table_option
//    {

//    }
//  | /*EMPTY*/
//    {

//    }
//  ;

//table_option:
//    JOIN_INFO opt_equal_mark STRING
//    {

//    }
//  | EXPIRE_INFO opt_equal_mark STRING
//    {

//    }
//  | TABLET_MAX_SIZE opt_equal_mark INTNUM
//    {

//    }
//  | TABLET_BLOCK_SIZE opt_equal_mark INTNUM
//    {

//    }
//  | TABLE_ID opt_equal_mark INTNUM
//    {

//    }
//  | REPLICA_NUM opt_equal_mark INTNUM
//    {

//    }
//  | COMPRESS_METHOD opt_equal_mark STRING
//    {

//    }
//  | USE_BLOOM_FILTER opt_equal_mark BOOL
//    {

//    }
//  | CONSISTENT_MODE opt_equal_mark STATIC
//    {

//    }
//  | COMMENT opt_equal_mark STRING
//    {

//    }
//  ;

//opt_equal_mark:
//    COMP_EQ     {  }
//  | /*EMPTY*/   {  }
//  ;


/*****************************************************************************
 *
 *	drop table grammar
 *
 *****************************************************************************/

drop_table_stmt:
    DROP TABLE opt_if_exists table_list
    {
      ParseNode *tables = NULL;
      merge_nodes(tables, result->malloc_pool_, T_TABLE_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_DROP_TABLE, 2, $3, tables);
    }
  ;

opt_if_exists:
    /* EMPTY */
    { $$ = NULL; }
  | IF EXISTS
    { malloc_terminal_node($$, result->malloc_pool_, T_IF_EXISTS); }
  ;

table_list:
    table_factor
    {
      $$ = $1;
    }
  | table_list ',' table_factor
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;



/*****************************************************************************
 *
 *	insert grammar
 *
 *****************************************************************************/
insert_stmt:
    replace_or_insert INTO relation_factor opt_insert_columns VALUES insert_vals_list
    opt_when
    {
      ParseNode* val_list = NULL;
      merge_nodes(val_list, result->malloc_pool_, T_VALUE_LIST, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           /* target relation */
                              $4,           /* column list */
                              val_list,     /* value list */
                              NULL,         /* value from sub-query */
                              $1,           /* is replacement */
                              $7            /* when expression */
                              );
    }
  | replace_or_insert INTO relation_factor select_stmt
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           /* target relation */
                              NULL,         /* column list */
                              NULL,         /* value list */
                              $4,           /* value from sub-query */
                              $1,           /* is replacement */
                              NULL          /* when expression */
                              );
    }
  | replace_or_insert INTO relation_factor '(' column_list ')' select_stmt
    {
      /* if opt_when is really needed, use select_with_parens instead */
      ParseNode* col_list = NULL;
      merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, $5);
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           /* target relation */
                              col_list,     /* column list */
                              NULL,         /* value list */
                              $7,           /* value from sub-query */
                              $1,           /* is replacement */
                              NULL          /* when expression */
                              );
    }
  ;

opt_when:
    /* EMPTY */
    { $$ = NULL; }
  | WHEN expr
    {
      $$ = $2;
    }
  ;

replace_or_insert:
    REPLACE
    {
      malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;
    }
  | INSERT
    {
      malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;
    }
  ;

opt_insert_columns:
    '(' column_list ')'
    {
      merge_nodes($$, result->malloc_pool_, T_COLUMN_LIST, $2);
    }
  | /* EMPTY */
    { $$ = NULL; }
  ;

column_list:
    column_name { $$ = $1; }
  | column_list ',' column_name
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

insert_vals_list:
    '(' insert_vals ')'
    {
      merge_nodes($$, result->malloc_pool_, T_VALUE_VECTOR, $2);
    }
  | insert_vals_list ',' '(' insert_vals ')' {
    merge_nodes($4, result->malloc_pool_, T_VALUE_VECTOR, $4);
    malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $4);
  }

insert_vals:
    expr { $$ = $1; }
  | insert_vals ',' expr
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

/*****************************************************************************
*
*	check grammar
*
*****************************************************************************/
check_stmt:
     CHECK CHAIN
     {
         malloc_terminal_node($$, result->malloc_pool_, T_CHECK);
     }
    ;

/*****************************************************************************
*
*	history grammar
*
*****************************************************************************/
//history_stmt:
//     SELECT HISTORY opt_history_range '['select_expr_list']' FROM from_list opt_where
//     {
//         ParseNode* project_list = NULL;
//         ParseNode* from_list = NULL;
//         merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, $5);
//         merge_nodes(from_list, result->malloc_pool_, T_FROM_LIST, $8);
//         malloc_non_terminal_node($$, result->malloc_pool_, T_HISTORY, 9,
//                                  $3,                 /* 1. range */
//                                  project_list,       /* 2. select clause */
//                                  from_list,          /* 3. from clause */
//                                  $9,                 /* 4. where */
//                                  NULL,                 /* 5. group by */
//                                  NULL,                 /* 6. having */
//                                  NULL,               /* 7. order by */
//                                  NULL,               /* 8. limit */
//                                  NULL                /* 9. when clause */
//                                  );
//     }
//    ;
opt_history_range:
       { $$ = NULL; }
    | '('')' { $$ = NULL; }
    | '(' DATE_VALUE TO DATE_VALUE ')' {
         malloc_non_terminal_node($$, result->malloc_pool_, T_HISTORY_RANGE, 2, $2, $4) ;
     }
    ;

/*****************************************************************************
 *
 *	invoke grammar
 *
 *****************************************************************************/

invoke_stmt:
     INVOKE contract_name '(' param ',' param_list ')'
     {
         ParseNode* params = NULL;
         merge_nodes(params, result->malloc_pool_, T_INVOKE_PARAM_LIST, $6);
         malloc_non_terminal_node($$, result->malloc_pool_, T_INVOKE, 3,
                                  $2,     /* 1. Starcode name */
                                  $4,     /* 2. function name */
                                  params  /* 3. args */
                                  );
     };

param_list:
     param { $$ = $1; }
   | param_list ',' param
     {
         malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
     };

param:
     STRING { $$ = $1; }
   | INTNUM { $$ = $1; }
   | BOOL { $$ = $1; }
   | APPROXNUM { $$ = $1; }
   ;

/*****************************************************************************
*
*	deploy grammar
*
*****************************************************************************/
deploy_stmt:
     DEPLOY '(' FILENAME ',' scan_height ')'
     {
         malloc_non_terminal_node($$, result->malloc_pool_, T_DEPLOY, 2,
                                  $3,     /* 1. starcode path */
                                  $5      /* 2. contract name */
                                  );
     };


/*****************************************************************************
*
*	reset block scan height grammar
*
*****************************************************************************/
reset_stmt:
     RESET SCAN HEIGHT TO int_param//contract_name
     {
         malloc_non_terminal_node($$, result->malloc_pool_, T_RESET, 1,
                                  $5     /* 1. scan_height */
                                  );
     };

int_param:
     INTNUM { $$ = $1; }
   ;

/*****************************************************************************
 *
 *	select grammar
 *
 *****************************************************************************/

select_stmt:
    select_no_parens /*opt_when*/    %prec UMINUS
    {
        $$ = $1;
//        $$->children_[14] = $2;
//        if($$->children_[12] == NULL && $2 != NULL)
//        {
//            malloc_terminal_node($$->children_[12], result->malloc_pool_, T_BOOL);
//            $$->children_[12]->value_ = 1;
//        }
    }
//  | select_with_parens    %prec UMINUS
//    {   }
  ;

select_with_parens:
    '(' select_no_parens ')'      {  }
  | '(' select_with_parens ')'    {  }
  ;

select_no_parens:
//    no_table_select
//    {

//    }
//  |
              simple_select //opt_for_update
    {
        $$ = $1;
        //$$->children_[12] = $2;
    }
//  | select_clause order_by opt_for_update
//    {

//    }
//  | select_clause opt_order_by select_limit opt_for_update
//    {

//    }
  ;

//no_table_select:
//    SELECT opt_hint opt_distinct select_expr_list opt_select_limit
//    {

//    }
//  | SELECT opt_hint opt_distinct select_expr_list
//    FROM DUAL opt_where opt_select_limit
//    {

//    }
//  ;

//select_clause:
//    simple_select	              {  }
//  | select_with_parens	        {  }
//  ;

simple_select:
    SELECT opt_hint opt_distinct select_expr_list
    FROM from_list
    opt_where opt_groupby opt_having
    {
        ParseNode* project_list = NULL;
        ParseNode* from_list = NULL;
        merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, $4);
        merge_nodes(from_list, result->malloc_pool_, T_FROM_LIST, $6);
        malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 6,
                                 $3,                 /* 1. distinct */
                                 project_list,       /* 2. select clause */
                                 from_list,          /* 3. from clause */
                                 $7,                 /* 4. where */
                                 $8,                 /* 5. group by */
                                 $9                 /* 6. having */
//                                 NULL,               /* 7. set operation */
//                                 NULL,               /* 8. al specified? */
//                                 NULL,               /* 9. former select stmt */
//                                 NULL,               /* 10. later select stmt */
//                                 NULL,               /* 11. order by */
//                                 NULL,               /* 12. limit */
//                                 NULL,               /* 13. for update */
//                                 NULL,                 /* 14. hints */
//                                 NULL                /* 15. when clause */
                                 );
    }

//  | select_clause UNION opt_distinct select_clause
//    {

//    }
//  | select_clause INTERSECT opt_distinct select_clause
//    {

//    }
//  | select_clause EXCEPT opt_distinct select_clause
//    {

//    }
  ;

opt_where:
    /* EMPTY */
    { $$ = NULL; }
  | WHERE expr
    {
        $$ = $2;
    }
  | WHERE HINT_VALUE expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 2, $3, $2);
        printf("hint expr\n");
    }
  ;

//select_limit:
//    LIMIT limit_expr OFFSET limit_expr
//    {

//    }
//  | OFFSET limit_expr LIMIT limit_expr
//    {

//    }
//  | LIMIT limit_expr
//    {

//    }
//  | OFFSET limit_expr
//    {

//    }
//  | LIMIT limit_expr ',' limit_expr
//    {

//    }
//  ;

opt_hint:
    /* EMPTY */
    {
        $$ = NULL;
    }
  | HINT_BEGIN opt_hint_list HINT_END
    {
        $$ = NULL;
    }
  ;

opt_hint_list:
    hint_options
    {
$$ = NULL;
    }
  | opt_hint_list ',' hint_options
    {
$$ = NULL;
    }
  | /*EMPTY*/
    {
$$ = NULL;
    }
  ;

hint_options:
    hint_option
    {
$$ = NULL;
    }
  | hint_options hint_option
    {
$$ = NULL;
    }
  ;

hint_option:
    READ_STATIC
    {
$$ = NULL;
    }
  | HOTSPOT
    {
$$ = NULL;
    }
//  | READ_CONSISTENCY '(' consistency_level ')'
//    {
//$$ = NULL;
//    }
//  | '(' opt_comma_list ')'
//    {
//$$ = NULL;
//    }
  ;

//opt_comma_list:
//    opt_comma_list ','
//    {
//$$ = NULL;
//    }
//  | /*EMPTY*/
//    {
//$$ = NULL;
//    }
//  ;

//consistency_level:
//  WEAK
//  {

//  }
//| STRONG
//  {

//  }
//| STATIC
//  {

//  }
//| FROZEN
//  {

//  }
//  ;
//limit_expr:
//    INTNUM
//    {  }
//  | QUESTIONMARK
//    {  }
//  ;

//opt_select_limit:
//    /* EMPTY */
//    { }
//  | select_limit
//    { }
//  ;

//opt_for_update:
//    /* EMPTY */
//    { $$ = NULL; }
//  | FOR UPDATE
//    {
//        $$ = NULL;
//    }
//  ;

//parameterized_trim:
//    expr FROM expr
//    {

//    }
//  | BOTH expr FROM expr
//    {

//    }
//  | LEADING expr FROM expr
//    {

//    }
//  | TRAILING expr FROM expr
//    {

//    }
//  | BOTH FROM expr
//    {

//    }
//  | LEADING FROM expr
//    {

//    }
//  | TRAILING FROM expr
//    {

//    }
//  ;

opt_groupby:
    /* EMPTY */
    {  $$=NULL; }
  | GROUP BY expr_list
    {
        merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $3);
    }
  ;

//opt_order_by:
//    order_by	              { }
//  | /*EMPTY*/             {  }
//  ;

//order_by:
//    ORDER BY sort_list
//    {

//    }
//  ;

//sort_list:
//    sort_key
//    {  }
//  | sort_list ',' sort_key
//    {  }
//  ;

//sort_key:
//    expr opt_asc_desc
//    {

//    }
//  ;

//opt_asc_desc: 
    /* EMPTY */
//    { malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); }
//  | ASC
//    { malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); }
//  | DESC
//    { malloc_terminal_node($$, result->malloc_pool_, T_SORT_DESC); }
//  ;


opt_having:
    /* EMPTY */
    { $$ = NULL; }
  | HAVING expr
    {
        $$ = $2;
    }
  ;

opt_distinct:
    /* EMPTY */
    {
        $$ = NULL;
    }
  | ALL
    {
        malloc_terminal_node($$, result->malloc_pool_, T_ALL);
    }
  | DISTINCT
    {
        malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);
    }
  ;

projection:
    expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_ITEM, 1, $1);
        dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);
    }
  | expr column_label
    {
        $$ = NULL;
    }
  | expr AS column_label
    {
        ParseNode* alias_node = NULL;
        malloc_non_terminal_node(alias_node, result->malloc_pool_, T_ALIAS, 2, $1, $3);
        malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, alias_node);
        dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);
        dup_expr_string(alias_node->str_value_, result, @3.first_column, @3.last_column);
    }
  | '*'
    {
        ParseNode* star_node = NULL;
        malloc_terminal_node(star_node, result->malloc_pool_, T_STAR);
        malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_ITEM, 1, star_node);
        dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);
    }
  ;

select_expr_list:
    projection
    {
        $$ = $1;
    }
  | select_expr_list ',' projection
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

from_list:
    table_factor
    { $$ = $1; }
  | from_list ',' table_factor
    { malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); } 
  ;

table_factor:
    relation_factor
    {
        $$ = $1;
    }
//  | relation_factor AS relation_name   
//    {
//      malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);
//    }
  | relation_factor USING relation_name   //gyc
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);
    }
//  | relation_factor relation_name
//    {
//      malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);
//    }
//  | select_with_parens AS relation_name
//    {
//    	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);
//    }
//  | select_with_parens relation_name
//    {
//    	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);
//    }
  | joined_table
    {
        printf("joined table \n");
        $$ = $1;
    }
  | '(' joined_table ')' AS relation_name
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $2, $5);
        yyerror(&@1, result, "qualied joined table can not be aliased!");
        YYABORT;
    }
  ;

relation_factor:
    relation_name { $$ = $1; }
  | chain_name '.' relation_name
    { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, $3); }
  | chain_name '.' relation_name '.' relation_name
    { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 3, $1, $3, $5); }
  ;

joined_table:
  /* we do not support cross join and natural join
    * using clause is not supported either
    */
    '(' joined_table ')'
    {
        $$ = $2;
    }
  | table_factor join_type JOIN table_factor ON expr
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, $2, $1, $4, $6);
    }
  | table_factor JOIN table_factor ON expr
    {
        ParseNode* node = NULL;
        malloc_terminal_node(node, result->malloc_pool_, T_JOIN_INNER);
        malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, node, $1, $3, $5);
    }
  ;

join_type:
    FULL join_outer
    {
        $$ = NULL;
    }
  | LEFT join_outer
    {
        $$ = NULL;
    }
  | RIGHT join_outer
    {
        $$ = NULL;
    }
  | INNER
    {
        printf("inner \n");
        malloc_terminal_node($$, result->malloc_pool_, T_JOIN_INNER);
    }
  ;

join_outer:
    OUTER                    { $$ = NULL; }
  | /* EMPTY */               { $$ = NULL; }
  ;


/*****************************************************************************
 *
 *	explain grammar
 *
 *****************************************************************************/
//explain_stmt:
//    EXPLAIN opt_verbose explainable_stmt
//    {

//    }
//  ;

//explainable_stmt:
//    select_stmt         {  }
//  | delete_stmt         {  }
//  | insert_stmt         {  }
//  | update_stmt         {  }
//  ;

//opt_verbose:
//    VERBOSE             {  }
//  | /*EMPTY*/           {  }
//  ;


/*****************************************************************************
 *
 *	show grammar
 *
 *****************************************************************************/
          show_stmt:
              SHOW VERSION
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_VERSION); }
            |  SHOW USERS
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_USERS); }
            |  SHOW PARTICIPANT relation_name
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_PARTICIPANT, 1, $3); }
            |  SHOW PARTICIPANTS
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_PARTICIPANTS); }
            | SHOW VARIABLES
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_VARIABLES); }
            |  SHOW CONTRACTS
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_CONTRACTS); }       
            | SHOW TABLES FROM relation_name opt_show_condition
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLES, 2, $4, $5);  }
            | SHOW COLUMNS FROM relation_factor opt_show_condition
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5); }
            | SHOW COLUMNS IN relation_factor opt_show_condition
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5); }
            | SHOW CONSENSUS_PROTOCAL
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_CONSENSUS_PROTOCAL);}
            | SHOW DEPTH
              { malloc_terminal_node($$, result->malloc_pool_, T_SHOW_BLOCK_DEPTH);}
//            | SHOW TABLE STATUS opt_show_condition
//              { $$=NULL; }
//            | SHOW SERVER STATUS opt_show_condition
//              { $$=NULL; }
//            | SHOW opt_scope VARIABLES opt_show_condition
//              { $$=NULL; }
//            | SHOW SCHEMA
//              { $$=NULL; }
//            | SHOW CREATE TABLE relation_factor
//              { $$=NULL; }

            | DESCRIBE relation_factor opt_like_condition
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3); }
            | DESC relation_factor opt_like_condition
              { malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3); }
//            | SHOW WARNINGS opt_limit
//              {
//                $$=NULL;
//              }
//            | SHOW func_expr WARNINGS
//              {
//                  $$=NULL;
//              }
//            | SHOW GRANTS opt_for_grant_user
//              {
//                  $$=NULL;
//              }
//            | SHOW PARAMETERS opt_show_condition
//              {
//                  $$=NULL;
//              }
//            | SHOW opt_full PROCESSLIST
//              {
//                  $$=NULL;
//              }
            ;
//opt_limit:
//    LIMIT INTNUM ',' INTNUM
//    {

//    }
//  | LIMIT INTNUM
//    {

//    }
//  | /* EMPTY */
//    { }
//  ;

//opt_for_grant_user:
//    opt_for_user
//    {  }
//  | FOR CURRENT_USER
//    {  }
//  | FOR CURRENT_USER '(' ')'
//    {  }
//  ;

//opt_scope:
//    GLOBAL      {  }
//  | SESSION     {  }
//  | /* EMPTY */ { }
//  ;
opt_show_condition:
    /* EMPTY */
    { $$ = NULL; }
  | LIKE STRING
    { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $2); }
  | WHERE expr
    { malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 1, $2); }
  ;

opt_like_condition:
    /* EMPTY */
    { $$ = NULL; }
  | STRING
    { malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $1); }
  ;
//opt_full:
//    /* EMPTY */
//    { }
//  | FULL
//    {  }
//  ;
/*****************************************************************************
 *
 *	create user grammar
 *
 *****************************************************************************/
create_user_stmt:
    CREATE USER user_specification_list
    {
       merge_nodes($$, result->malloc_pool_, T_CREATE_USER, $3);
    }
;
user_specification_list:
    user_specification
    {
        $$ = $1;
    }
    | user_specification_list ',' user_specification
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
;
user_specification:
    user IDENTIFIED BY password
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_USER_SPEC, 2, $1, $4);
    }
;
user:
    STRING
    {
        $$ = $1;
    }
;
password:
    STRING
    {
        $$ = $1;
    }
;

/*****************************************************************************
 *
 *	drop user grammar
 *
 *****************************************************************************/
//drop_user_stmt:
//    DROP USER user_list
//    {

//    }
//;
user_list:
    user
    {
       $$ =$1;
    }
    | user_list ',' user
    {
       malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
;

/*****************************************************************************
 *
 *	set password grammar
 *
 *****************************************************************************/
set_password_stmt:
    SET PASSWORD opt_for_user COMP_EQ password
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $5);
    }
    | ALTER USER user IDENTIFIED BY password
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $6);
    }
;
opt_for_user:
    FOR user
    {
        $$ = $2;
    }
    | /**/
    {
        $$ = NULL;
    }
;
/*****************************************************************************
 *
 *	rename user grammar
 *
 *****************************************************************************/
//rename_user_stmt:
//    RENAME USER rename_list
//    {

//    }
//;
//rename_info:
//    user TO user
//    {

//    }
//;
//rename_list:
//    rename_info
//    {

//    }
//    | rename_list ',' rename_info
//    {

//    }
//;
/*****************************************************************************
 *
 *	lock user grammar
 *
 *****************************************************************************/
//lock_user_stmt:
//    ALTER USER user lock_spec
//    {

//    }
//;
//lock_spec:
//    LOCKED
//    {

//    }
//    | UNLOCKED
//    {

//    }
//;
/*****************************************************************************
*
*  begin/start transaction grammer
*
******************************************************************************/

//opt_work:
//    WORK
//    {

//    }
//    | /*empty*/
//    {

//    }
//opt_with_consistent_snapshot:
//    WITH CONSISTENT SNAPSHOT
//    {

//    }
//    |/*empty*/
//    {

//    }
//begin_stmt:
//    BEGI opt_work
//    {

//    }
//    | START TRANSACTION opt_with_consistent_snapshot
//    {

//    }
/*****************************************************************************
*
*  commit grammer
*
******************************************************************************/
//commit_stmt:
//    COMMIT opt_work
//    {

//    }

/*****************************************************************************
*
*  rollback grammer
*
******************************************************************************/
//rollback_stmt:
//    ROLLBACK opt_work
//    {

//    }

/*****************************************************************************
*
*  kill grammer
*
******************************************************************************/
//kill_stmt:
//    KILL opt_is_global opt_flag INTNUM
//    {

//    }
//   ;
//opt_is_global:
//    /*EMPTY*/
//    {

//    }
//    | GLOBAL
//    {

//    }
//  ;
//opt_flag:
//    /*EMPTY*/
//    {

//    }
//    | QUERY
//    {

//    }
//    | CONNECTION
//    {

//    }
//  ;


/*****************************************************************************
 *
 *	grant grammar
 *
 *****************************************************************************/
grant_stmt:
    GRANT priv_type_list TO user_list
    {
        ParseNode *privileges_node = NULL;
        ParseNode *users_node = NULL;
        merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, $2);
        merge_nodes(users_node, result->malloc_pool_, T_USERS, $4);
        malloc_non_terminal_node($$, result->malloc_pool_, T_GRANT,
                                   2, privileges_node, users_node);
    }
;
priv_type_list:
    priv_type
    {
       $$ = $1;
    }
    | priv_type_list ',' priv_type
    {
        malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
;
priv_type:
    ALL
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "all";
    }
//    | ALTER
//    {

//    }
    | CREATE TABLE
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "create_table";
    }
    | CREATE USER
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "create_user";
    }
//    | DELETE
//    {

//    }
//    | DROP
//    {

//    }
    | GRANT OPTION
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "grant";
    }
//    | INSERT
//    {

//    }
//    | UPDATE
//    {

//    }
    | SELECT
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "select";
    }
//    | REPLACE
//    {

//    }
    | TRACE
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "trace";
    }
    | CHECK
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "check";
    }
    | INVOKE
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "invoke";
    }
    | DEPLOY
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "deploy";
    }
    | GET
    {
        malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
        $$->str_value_ = "get";
    }
;
/*****************************************************************************
 *
 *	revoke grammar
 *
 *****************************************************************************/
//revoke_stmt:
//    REVOKE priv_type_list opt_on_priv_level FROM user_list
//    {

//    }
//;
//opt_on_priv_level:
//    ON
//    {

//    }
//    | /*empty*/
//    {

//    }

/*****************************************************************************
 *
 *	prepare grammar
 *
 *****************************************************************************/
//prepare_stmt:
//    /* PREPARE stmt_name FROM '"' preparable_stmt '"' */
//    PREPARE stmt_name FROM preparable_stmt
//    {

//    }
//  ;

//stmt_name:
//    column_label
//    {}
//  ;

//preparable_stmt:
//    select_stmt
//    {  }
//  | insert_stmt
//    {  }
//  | update_stmt
//    {  }
//  | delete_stmt
//    { }
//  ;


/*****************************************************************************
 *
 *	set grammar
 *
 *****************************************************************************/
//variable_set_stmt:
//    SET var_and_val_list
//    {

//    }
//  ;

//var_and_val_list:
//    var_and_val
//    {

//    }
//  | var_and_val_list ',' var_and_val
//    {

//    }
//  ;

//var_and_val:
//    TEMP_VARIABLE to_or_eq expr
//    {

//    }
//  | column_name to_or_eq expr
//    {

//    }
//  | GLOBAL column_name to_or_eq expr
//    {

//    }
//  | SESSION column_name to_or_eq expr
//    {

//    }
//  | GLOBAL_ALIAS '.' column_name to_or_eq expr
//    {

//    }
//  | SESSION_ALIAS '.' column_name to_or_eq expr
//    {

//    }
//  | SYSTEM_VARIABLE to_or_eq expr
//    {

//    }
//  ;

//to_or_eq:
//    TO      {  }
//  | COMP_EQ { }
//  ;

//argument:
//    TEMP_VARIABLE
//    {  }
//  ;


/*****************************************************************************
 *
 *	execute grammar
 *
 *****************************************************************************/
//execute_stmt:
//    EXECUTE stmt_name opt_using_args
//    {

//    }
//  ;

//opt_using_args:
//    USING argument_list
//    {

//    }
//    | /*empty*/
//    {

//    }

//argument_list:
//    argument
//    {

//    }
//  | argument_list ',' argument
//    {

//    }
//  ;


/*****************************************************************************
 *
 *	DEALLOCATE grammar
 *
 *****************************************************************************/
//deallocate_prepare_stmt:
//    deallocate_or_drop PREPARE stmt_name
//    {

//    }
//  ;

//deallocate_or_drop:
//    DEALLOCATE
//    {  }
//  | DROP
//    {  }
//  ;


/*****************************************************************************
 *
 *	ALTER TABLE grammar
 *
 *****************************************************************************/
alter_table_stmt:
     ALTER TABLE relation_factor ADD alter_column_actions
    {
      /*ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, alter_actions);*/
      ParseNode* alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, $5);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2,
                                $3,                        /* table name */
                                alter_actions         /*s */
                                );

    }
  ;

alter_column_actions:
    alter_column_action
    {
      $$ = $1;
    }
  | alter_column_actions ',' alter_column_action
    {
      malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);
    }
  ;

alter_column_action:
    function_definition
    {
      $$ = $1;
    }
  /* we don't have table constraint, so ignore it */
  ;


//opt_column:
//    COLUMN          { $$ = NULL; }
//  | /*EMPTY*/       { $$ = NULL; }
//  ;

/*****************************************************************************
 *
 *	ALTER SYSTEM grammar
 *
 *****************************************************************************/
//alter_system_stmt:
//    ALTER SYSTEM SET alter_system_actions
//    {

//    }
//    |
//    ALTER SYSTEM opt_force CHANGE_OBI MASTER COMP_EQ STRING
//    {

//    }
//    |
//    ALTER SYSTEM opt_force SWITCH_CLUSTER MASTER COMP_EQ STRING
//    {

//    }
//    |
//    ALTER SYSTEM SET_MASTER_CLUSTER MASTER COMP_EQ STRING
//    {

//    }
//    |
//    ALTER SYSTEM SET_SLAVE_CLUSTER SLAVE COMP_EQ STRING
//    {

//    }
//  ;

//opt_force:
//    /*EMPTY*/
//    {

//    }
//  | FORCE
//    {

//    } 
//    ;


//alter_system_actions:
//    alter_system_action
//    {

//    }
//  | alter_system_actions ',' alter_system_action
//    {

//    }
//  ;

//alter_system_action:
//    column_name COMP_EQ expr_const opt_comment opt_config_scope
//    SERVER_TYPE COMP_EQ server_type opt_cluster_or_address
//    {

//    }
//  ;

//opt_comment:
//    COMMENT STRING
//    {  }
//  | /* EMPTY */
//    {  }
//  ;

//opt_config_scope:
//    SCOPE COMP_EQ MEMORY
//    {  }   /* same as ObConfigType */
//  | SCOPE COMP_EQ SPFILE
//    {  }   /* same as ObConfigType */
//  | SCOPE COMP_EQ BOTH
//    {  }   /* same as ObConfigType */
//  | /* EMPTY */
//    {  }   /* same as ObConfigType */
//  ;

//server_type:
//    ROOTSERVER
//    {

//    }
//  | UPDATESERVER
//    {

//    }
//  | CHUNKSERVER
//    {

//    }
//  | MERGESERVER
//    {

//    }
//  ;

//opt_cluster_or_address:
//    CLUSTER COMP_EQ INTNUM
//    {

//    }
//  | SERVER_IP COMP_EQ STRING SERVER_PORT COMP_EQ INTNUM
//    {

//    }
//  | /* EMPTY */
//    {  }
//  ;


/*===========================================================
 *
 *	Name classification
 *
 *===========================================================*/
chain_name:
    CHAIN
    {
        malloc_terminal_node($$, result->malloc_pool_, T_CHAIN);
    }
  | OFFCHAIN
    {
        malloc_terminal_node($$, result->malloc_pool_, T_OFF_CHAIN);
    }
  ;

column_name:
    NAME
    { $$ = $1; }
  | unreserved_keyword
    {
        malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
        $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
        if ($$->str_value_ == NULL)
        {
          yyerror(NULL, result, "No more space for string duplicate");
          YYABORT;
        }
        else
        {
          $$->value_ = strlen($$->str_value_);
        }
    }
  ;

relation_name:
    NAME
    { $$ = $1; }
  |STRING { $$ = $1; }//gyc
  | unreserved_keyword
    {
        malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
        $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
        if ($$->str_value_ == NULL)
        {
          yyerror(NULL, result, "No more space for string duplicate");
          YYABORT;
        }
        else
        {
          $$->value_ = strlen($$->str_value_);
        }
    }
  ;

//contract_function_name:
//    NAME
//    { $$ = $1; }
//  ;

function_name:
    NAME
  ;

contract_name:
    NAME
    { $$ = $1; }
  | unreserved_keyword
    {
        malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
        $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
        if ($$->str_value_ == NULL)
        {
          yyerror(NULL, result, "No more space for string duplicate");
          YYABORT;
        }
        else
        {
          $$->value_ = strlen($$->str_value_);
        }
  }
  ;

mode_name:
    NAME
    { $$ = $1; }
  ;

rules:
    NAME
    { $$ = $1; }
  ;

scan_height:
    SCAN_HEIGHT
    { $$ = $1; }
  ;

column_label:
    NAME
    { printf("column=");}
  | unreserved_keyword
    {
        malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
        $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
        if ($$->str_value_ == NULL)
        {
          yyerror(NULL, result, "No more space for string duplicate");
          YYABORT;
        }
        else
        {
          $$->value_ = strlen($$->str_value_);
        }
    }
  ;

unreserved_keyword:
    AUTO_INCREMENT
  | CHUNKSERVER
  | COMPRESS_METHOD
  | CONSISTENT_MODE
  | EXPIRE_INFO
  | GRANTS
  | JOIN_INFO
  | MERGESERVER
  | REPLICA_NUM
  | ROOTSERVER
  | ROW_COUNT
  | SERVER
  | SERVER_IP
  | SERVER_PORT
  | SERVER_TYPE
  | STATUS
  | TABLET_BLOCK_SIZE
  | TABLE_ID
  | TABLET_MAX_SIZE
  | UNLOCKED
  | UPDATESERVER
  | USE_BLOOM_FILTER
  | VARIABLES
  | VERBOSE
  | WARNINGS
  ;
%%
void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s, ...)
{
    if (p != NULL)
    {
        p->result_tree_ = 0;
        va_list ap;
        va_start(ap, s);
        vsnprintf(p->error_msg_, MAX_ERROR_MSG, s, ap);
        if (yylloc != NULL)
        {
            if (p->input_sql_[yylloc->first_column - 1] != '\'')
                p->start_col_ = yylloc->first_column;
            p->end_col_ = yylloc->last_column;
            p->line_ = yylloc->first_line;
        }
    }
}

int parse_init(ParseResult* p)
{
    int ret = 0;  // can not include C++ file "ob_define.h"
    if (!p || !p->malloc_pool_)
    {
        ret = -1;
        if (p)
        {
            snprintf(p->error_msg_, MAX_ERROR_MSG, "malloc_pool_ must be set");
        }
    }
    if (ret == 0)
    {
        ret = yylex_init_extra(p, &(p->yyscan_info_));
    }
    return ret;
}

int parse_terminate(ParseResult* p)
{
    free(p->tmp_literal_);
    p->tmp_literal_ = NULL;
    return yylex_destroy(p->yyscan_info_);
}
int parse_sql(ParseResult* p, const char* buf, size_t len)
{
    int ret = -1;
    p->result_tree_ = 0;
    p->error_msg_[0] = 0;
    p->input_sql_ = buf;
    p->input_sql_len_ = len;
    p->start_col_ = 1;
    p->end_col_ = 1;
    p->line_ = 1;
    p->yycolumn_ = 1;
    p->yylineno_ = 1;
    p->tmp_literal_ = NULL;

    if (buf == NULL || len <= 0)
    {
        snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be empty");
        return ret;
    }
    while(len > 0 && isspace(buf[len - 1]))
        --len;

    if (len <= 0)
    {
        snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be while space only");
        return ret;
    }
    YY_BUFFER_STATE bp;

    //bp = yy_scan_string(buf, p->yyscan_info_);
    bp = yy_scan_bytes(buf, len, p->yyscan_info_);
    yy_switch_to_buffer(bp, p->yyscan_info_);
    ret = yyparse(p);
    yy_delete_buffer(bp, p->yyscan_info_);

    return ret;
}


