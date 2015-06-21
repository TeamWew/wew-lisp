#include "mpc.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>
static char buffer[2048];

char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* copy = malloc(strlen(buffer)+1);
    strcpy(copy, buffer)
    copy[strlen(copy)-1] = '\0';
    return cpy;
}

char* add_history(char* _) {}
#endif

#ifdef __APPLE__
#include <editline/readline.h>
#endif

#ifdef __linux
#include <editline/readline.h>
#include <editline/history.h>
#endif


long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  return 0;
}

long eval(mpc_ast_t* t) {
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  char* op = t->children[1]->contents;
  long x = eval(t->children[2]);
  int i = 3;

  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}


int main(int argc, char** argv) {

  /* Create Some Parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Wewlisp    = mpc_new("wewlisp");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      wewlisp  : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Wewlisp);

    puts("wewlisp version 0.0.2");
    puts("Press Ctrl+c to exit");

    while(1) {
        char* input = readline("wewlisp> ");

        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Wewlisp, &r)) {
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        }
        else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, Wewlisp);

    return 0;
}
