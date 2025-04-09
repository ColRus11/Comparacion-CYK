%{
#include "parser.tab.h"
%}

%%

a   return A;
b   return B;
.   return -1;

%%

