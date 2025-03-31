/**
 *
 * @file scanner.l
 *
 * @brief Scanner template.
 * This file was generated on Mon Mar 31 11:23:05 2025.
 *
 */

%{
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "errors.h"
#include "tokens.h"
#include "alloc.h"

int yycolumn = 1;

typedef struct _file_info_t_ {
    const char* fname;
    FILE* fp;
    size_t line_no;
    size_t col_no;
    YY_BUFFER_STATE buffer;
    struct _file_info_t_* next;
} file_info_t;

static file_info_t* file_stack = NULL;
static file_info_t* end_file = NULL;

#define YY_USER_ACTION \
  file_stack->col_no = yycolumn; \
  file_stack->line_no = yylineno; \
  if (yylineno == prev_yylineno) \
    yycolumn += yyleng; \
  else { \
    for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} \
    prev_yylineno = yylineno; \
  }

%}

%option yylineno
%option noinput
%option nounput
%option noyywrap
%option header-file="scanner.h"
%option outfile="scanner.c"

%%

   // int start_line, start_column;
   int prev_yylineno = yylineno;

"start" {
    add_token_queue(create_token(yytext, TOK_START));
    return TOK_START;
}

"import" {
    add_token_queue(create_token(yytext, TOK_IMPORT));
    return TOK_IMPORT;
}

"as" {
    add_token_queue(create_token(yytext, TOK_AS));
    return TOK_AS;
}

"include" {
    add_token_queue(create_token(yytext, TOK_INCLUDE));
    return TOK_INCLUDE;
}

"private" {
    add_token_queue(create_token(yytext, TOK_PRIVATE));
    return TOK_PRIVATE;
}

"public" {
    add_token_queue(create_token(yytext, TOK_PUBLIC));
    return TOK_PUBLIC;
}

"protected" {
    add_token_queue(create_token(yytext, TOK_PROTECTED));
    return TOK_PROTECTED;
}

"float" {
    add_token_queue(create_token(yytext, TOK_FLOAT));
    return TOK_FLOAT;
}

"integer" {
    add_token_queue(create_token(yytext, TOK_INTEGER));
    return TOK_INTEGER;
}

"string" {
    add_token_queue(create_token(yytext, TOK_STRING));
    return TOK_STRING;
}

"boolean" {
    add_token_queue(create_token(yytext, TOK_BOOLEAN));
    return TOK_BOOLEAN;
}

"nothing" {
    add_token_queue(create_token(yytext, TOK_NOTHING));
    return TOK_NOTHING;
}

"list" {
    add_token_queue(create_token(yytext, TOK_LIST));
    return TOK_LIST;
}

"dict" {
    add_token_queue(create_token(yytext, TOK_DICT));
    return TOK_DICT;
}

"(" {
    add_token_queue(create_token(yytext, TOK_OPAREN));
    return TOK_OPAREN;
}

"," {
    add_token_queue(create_token(yytext, TOK_COMMA));
    return TOK_COMMA;
}

")" {
    add_token_queue(create_token(yytext, TOK_CPAREN));
    return TOK_CPAREN;
}

"const" {
    add_token_queue(create_token(yytext, TOK_CONST));
    return TOK_CONST;
}

"=" {
    add_token_queue(create_token(yytext, TOK_EQUAL));
    return TOK_EQUAL;
}

":" {
    add_token_queue(create_token(yytext, TOK_COLON));
    return TOK_COLON;
}

"[" {
    add_token_queue(create_token(yytext, TOK_OSBRACE));
    return TOK_OSBRACE;
}

"]" {
    add_token_queue(create_token(yytext, TOK_CSBRACE));
    return TOK_CSBRACE;
}

"." {
    add_token_queue(create_token(yytext, TOK_DOT));
    return TOK_DOT;
}

"create" {
    add_token_queue(create_token(yytext, TOK_CREATE));
    return TOK_CREATE;
}

"destroy" {
    add_token_queue(create_token(yytext, TOK_DESTROY));
    return TOK_DESTROY;
}

"+" {
    add_token_queue(create_token(yytext, TOK_PLUS));
    return TOK_PLUS;
}

"-" {
    add_token_queue(create_token(yytext, TOK_MINUS));
    return TOK_MINUS;
}

"*" {
    add_token_queue(create_token(yytext, TOK_STAR));
    return TOK_STAR;
}

"/" {
    add_token_queue(create_token(yytext, TOK_SLASH));
    return TOK_SLASH;
}

"%" {
    add_token_queue(create_token(yytext, TOK_PERCENT));
    return TOK_PERCENT;
}

"namespace" {
    add_token_queue(create_token(yytext, TOK_NAMESPACE));
    return TOK_NAMESPACE;
}

"{" {
    add_token_queue(create_token(yytext, TOK_OCBRACE));
    return TOK_OCBRACE;
}

"}" {
    add_token_queue(create_token(yytext, TOK_CCBRACE));
    return TOK_CCBRACE;
}

"class" {
    add_token_queue(create_token(yytext, TOK_CLASS));
    return TOK_CLASS;
}

"+=" {
    add_token_queue(create_token(yytext, TOK_PLUS_EQUAL));
    return TOK_PLUS_EQUAL;
}

"-=" {
    add_token_queue(create_token(yytext, TOK_MINUS_EQUAL));
    return TOK_MINUS_EQUAL;
}

"*=" {
    add_token_queue(create_token(yytext, TOK_STAR_EQUAL));
    return TOK_STAR_EQUAL;
}

"/=" {
    add_token_queue(create_token(yytext, TOK_SLASH_EQUAL));
    return TOK_SLASH_EQUAL;
}

"%=" {
    add_token_queue(create_token(yytext, TOK_PERCENT_EQUAL));
    return TOK_PERCENT_EQUAL;
}

"break" {
    add_token_queue(create_token(yytext, TOK_BREAK));
    return TOK_BREAK;
}

"continue" {
    add_token_queue(create_token(yytext, TOK_CONTINUE));
    return TOK_CONTINUE;
}

"yield" {
    add_token_queue(create_token(yytext, TOK_YIELD));
    return TOK_YIELD;
}

"type" {
    add_token_queue(create_token(yytext, TOK_TYPE));
    return TOK_TYPE;
}

"return" {
    add_token_queue(create_token(yytext, TOK_RETURN));
    return TOK_RETURN;
}

"raise" {
    add_token_queue(create_token(yytext, TOK_RAISE));
    return TOK_RAISE;
}

"trace" {
    add_token_queue(create_token(yytext, TOK_TRACE));
    return TOK_TRACE;
}

"print" {
    add_token_queue(create_token(yytext, TOK_PRINT));
    return TOK_PRINT;
}

"exit" {
    add_token_queue(create_token(yytext, TOK_EXIT));
    return TOK_EXIT;
}

"while" {
    add_token_queue(create_token(yytext, TOK_WHILE));
    return TOK_WHILE;
}

"do" {
    add_token_queue(create_token(yytext, TOK_DO));
    return TOK_DO;
}

"for" {
    add_token_queue(create_token(yytext, TOK_FOR));
    return TOK_FOR;
}

"if" {
    add_token_queue(create_token(yytext, TOK_IF));
    return TOK_IF;
}

"else" {
    add_token_queue(create_token(yytext, TOK_ELSE));
    return TOK_ELSE;
}

"try" {
    add_token_queue(create_token(yytext, TOK_TRY));
    return TOK_TRY;
}

"except" {
    add_token_queue(create_token(yytext, TOK_EXCEPT));
    return TOK_EXCEPT;
}

"final" {
    add_token_queue(create_token(yytext, TOK_FINAL));
    return TOK_FINAL;
}

"|"|"or" {
    add_token_queue(create_token(yytext, TOK_OR_OPER));
    return TOK_OR_OPER;
}

"&"|"and" {
    add_token_queue(create_token(yytext, TOK_AND_OPER));
    return TOK_AND_OPER;
}

"=="|"equ" {
    add_token_queue(create_token(yytext, TOK_EQU_OPER));
    return TOK_EQU_OPER;
}

"!="|"nequ" {
    add_token_queue(create_token(yytext, TOK_NEQU_OPER));
    return TOK_NEQU_OPER;
}

"<"|"lt" {
    add_token_queue(create_token(yytext, TOK_LT_OPER));
    return TOK_LT_OPER;
}

">"|"gt" {
    add_token_queue(create_token(yytext, TOK_GT_OPER));
    return TOK_GT_OPER;
}

"<="|"lte" {
    add_token_queue(create_token(yytext, TOK_LTE_OPER));
    return TOK_LTE_OPER;
}

">="|"gte" {
    add_token_queue(create_token(yytext, TOK_GTE_OPER));
    return TOK_GTE_OPER;
}

"true"|"false" {
    add_token_queue(create_token(yytext, TOK_LITERAL_BOOL));
    return TOK_LITERAL_BOOL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    add_token_queue(create_token(yytext, TOK_IDENTIFIER));
    return TOK_IDENTIFIER;
}

\"[^\"\n]*\"|\'[^\'\n]*\' {
    add_token_queue(create_token(yytext, TOK_LITERAL_STRING));
    return TOK_LITERAL_STRING;
}

(([1-9][0-9]*)|0)?\.[0-9]*([eE][-+]?[0-9]+)? {
    add_token_queue(create_token(yytext, TOK_LITERAL_FLOAT));
    return TOK_LITERAL_FLOAT;
}

([1-9][0-9]*)|0 {
    add_token_queue(create_token(yytext, TOK_LITERAL_INTEGER));
    return TOK_LITERAL_INTEGER;
}

;[^\n]*\n|#[^\n]*\n {
    add_token_queue(create_token(yytext, TOK_COMMENT));
    return TOK_COMMENT;
}


[ \t\r\n\v\f]+ { /* ignore spaces */ }

. { return yytext[0]; }

<<EOF>> {

    if(file_stack == NULL) {
        yyterminate();
        return 0;
    }

    file_info_t* fs = file_stack;
    yy_delete_buffer(fs->buffer);
    file_stack = file_stack->next;

    fclose(fs->fp);

    if(file_stack != NULL) {
        yy_switch_to_buffer(file_stack->buffer);
        _FREE(fs->fname);
        _FREE(fs);
    }
    else {
        end_file = fs;
        yyterminate();
    }
}

%%

void open_file(const char* fn) {

    const char *fname = fn; //find_file(fn);
    yyin = fopen(fname, "r");
    if(yyin == NULL)
        FATAL("cannot open input file: \"%s\": %s\n", fname, strerror(errno));

    file_info_t* fs = _ALLOC_TYPE(file_info_t);
    fs->fname = fname;
    fs->next = NULL;
    fs->line_no = 1;
    fs->col_no = 1;

    fs->fp = yyin;
    fs->buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
    yy_switch_to_buffer(fs->buffer);

    if(file_stack != NULL) {
        fs->next = file_stack;
        file_stack = fs;
    }
    else
        file_stack = fs;

}

int get_line_no(void) {

    if(file_stack != NULL)
        return file_stack->line_no;
    else if(end_file != NULL)
        return end_file->line_no;
    else
        return -1; // no file has ever been open
}

int get_col_no(void) {

    if(file_stack != NULL)
        return file_stack->col_no;
    else if(end_file != NULL)
        return end_file->col_no;
    else
        return -1;
}

const char* get_file_name(void) {

    if(file_stack != NULL)
        return file_stack->fname;
    else if(end_file != NULL)
        return end_file->fname;
    else
        return NULL;
}

