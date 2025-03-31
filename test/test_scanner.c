
#include "../common/fileio.h"
#include "scanner.h"

int main(void) {

    open_file("generic.toy");

    while(yylex() != 0) ;

    return 0;
}