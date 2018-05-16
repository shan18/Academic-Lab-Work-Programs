%{
int comment=0;
%}
%%
[/*].*[*/] {comment++;}
.echo ;
%%
int yywrap()
{
return 1;
}
main(int argc,char**argv)
{
yyin=fopen(argv[1],"r");
yyout=fopen(argv[2],"w");
yylex();
printf("no of comment lines %d\n",comment);
}
