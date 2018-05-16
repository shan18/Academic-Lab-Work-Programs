%{
int lines=0,words=0,chars=0,blanks=0;
%}
%%
[\t] blanks++;
[\n] lines++;
[^ \t\n]+ {words++;chars+=yyleng;}
%%
yywrap()
{
printf("charcter=%d,lines=%d,blanks=%d,words=%d\n",chars,lines,blanks,words);
}
int main(int argc,char*argv[])
{
yyin=fopen(argv[1],"r");
yylex();
return 0;
}
