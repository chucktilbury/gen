
#include "fileio.h"
#include "scanner.h"
#include "tokens.h"

void print_token(token_t* tok) {

    printf("%15s:%3d:%2d ->\t\"%s\"\t%s\n", tok->fname->buffer,
            tok->line_no, tok->col_no, tok->raw->buffer, token_type_to_str(tok->type));
}

// gcc -g -o tp test_scanner.c ../common/alloc.c ../common/queue.c ../common/string_buf.c scanner.c tokens.c -I ../common
int main(void) {

    token_t* tok;

    init_token_queue("generic.toy");

    void* post = post_token_queue();

    for(int i = 0; i < 5; i++) {
        tok = get_token();
        print_token(tok);
        advance_token();
    }

    reset_token_queue(post);

    for(int i = 0; i < 5; i++) {
        tok = get_token();
        print_token(tok);
        advance_token();
    }

    consume_token_queue();

    while(NULL != (tok = get_token())) {
        print_token(tok);
        advance_token();
        if(tok->type == TOK_END_OF_INPUT)
            break;
    }

    return 0;
}