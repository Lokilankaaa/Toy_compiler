%{ 
#include <string>

/* Implementation of yyFlexScanner */
#include "scanner.h"

#undef  YY_DECL
#define YY_DECL int TOY_COMPILER::Scanner::yylex(TOY_COMPILER::Parser::semantic_type * const lval, TOY_COMPILER::Parser::location_type *loc)

/* typedef to make the returns for the tokens shorter */
using token = TOY_COMPILER::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

/*** Flex Declarations and Options ***/

/* comments scanner */
%x COMMENT

/* enable scanner to generate debug output. disable this for release versions. */
%option debug

/* enable c++ scanner class generation */
%option c++
%option nodefault
%option yyclass="TOY_COMPILER::Scanner"
%option noyywrap

%%
%{
    /** code executed at the beginning of yylex **/
    yylval = lval;
%}
    /* keyword */
and         { return token::AND; }
array       { return token::ARRAY; }
begin       { return token::_BEGIN; }
case        { return token::CASE; }
const       { return token::CONST; }
div         { return token::DIV; }
do          { return token::DO; }
downto      { return token::DOWNTO; }
else        { return token::ELSE; }
end         { return token::_END; }
for         { return token::FOR; }
function    { return token::FUNCTION; }
goto        { return token::GOTO; }
if          { return token::IF; }
mod         { return token::MOD; }
not         { return token::NOT; }
of          { return token::OF; }
or          { return token::OR; }
packed      { return token::PACKED; }
procedure   { return token::PROCEDURE; }
program     { return token::PROGRAM; }
record      { return token::RECORD; }
repeat      { return token::REPEAT; }
then        { return token::THEN; }
to          { return token::TO; }
type        { return token::TYPE; }
until       { return token::UNTIL; }
var         { return token::VAR; }
while       { return token::WHILE; }

    /* system constant*/
false       { yylval->build<bool>(false); return token::BOOL; }
true        { yylval->build<bool>(true); return token::BOOL; }
nil         { yylval->build<int>(0); return token::SYS_CON; }
maxint      { yylval->build<int>(2147483647); return token::SYS_CON; }

    /* system function and procedures */
abs         { yylval->build<int>(0); return token::SYS_FUNCT; }
chr         { yylval->build<int>(1); return token::SYS_FUNCT; }
odd         { yylval->build<int>(2); return token::SYS_FUNCT; }
ord         { yylval->build<int>(3); return token::SYS_FUNCT; }
pred        { yylval->build<int>(4); return token::SYS_FUNCT; }
sqr         { yylval->build<int>(5); return token::SYS_FUNCT; }
sqrt        { yylval->build<int>(6); return token::SYS_FUNCT; }
succ        { yylval->build<int>(7); return token::SYS_FUNCT; }
write       { yylval->build<int>(8); return token::SYS_PROC; }
writeln     { yylval->build<int>(9); return token::SYS_PROC; }
read        { yylval->build<int>(10); return token::READ; }

    /* system type */
boolean     { yylval->build<int>(1); return token::SYS_TYPE; }
char        { yylval->build<int>(2); return token::SYS_TYPE; }
integer     { yylval->build<int>(3); return token::SYS_TYPE; }
real        { yylval->build<int>(4); return token::SYS_TYPE; }

    /* integer */
-?[0-9]+    { yylval->build<int>(atoi(yytext)); return token::INTEGER; }

    /* real */
-?[0-9]+"."[0-9]* |
-?"."[0-9]+	|
-?[0-9]+E[-+]?[0-9]+ |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
-?"."[0-9]*E[-+]?[0-9]+	{ yylval->build<double>(atof(yytext)); return token::REAL; }

    /* character */
'(\\.|''|[^'\n])'       { yylval->build<char>(yytext[1]); return token::CHAR; }


    /* operator */
"+"     { return token::PLUS; }
"-"     { return token::MINUS; }
"*"     { return token::MUL; }
"/"     { return token::DIV; }
">="    { return token::GE; }
">"     { return token::GT; }
"<="    { return token::LE; }
"<"     { return token::LT; }
"="     { return token::EQUAL; }
"<>"    { return token::UNEQUAL; }
"MOD"   { return token::MOD; }
"NOT"   { return token::NOT; }
":="    { return token::ASSIGN; }

    /* delimiter */
"("     { return token::LP; }
")"     { return token::RP; }
"["     { return token::LB; }
"]"     { return token::RB; }
","     { return token::COMMA; }
":"     { return token::COLON; }
".."    { return token::DOTDOT; }
"."     { return token::DOT; }
";"     { return token::SEMI; }

    /* identifier */
[A-Za-z][A-Za-z0-9_]*   { yylval->build<std::string>(yytext); return token::ID; }

    /* comments (C-like) */
"//".*\n                { loc->lines(); }
"/*"                    { BEGIN COMMENT; }
<COMMENT>"*/"           { BEGIN INITIAL; }
<COMMENT>([^*]|\n)+|.   { }

    /* update line number */
\n                      { loc->lines(); }

    /* white space */
[ \t]
.

%%
