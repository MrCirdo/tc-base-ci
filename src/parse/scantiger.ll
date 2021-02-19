                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

  // FIXME: Some code was deleted here.

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)


YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
digit			[0-9]
int				{digit}+
letter			[a-zA-Z]
escape			\\[abfnrtv\\"]|\\[0-3][0-7]{2}|\\x[0-9a-fA-F]{2}
EOL				(\r\n?|\n\r?)
whitespace		[ \t]

%%
%{
  // FIXME: Some code was deleted here (Local variables).
  std::string string_content;

  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */

 /* Integer literals */
{int}		{
                int val = atoi(yytext);
                return TOKEN_VAL(INT, val);
			}

 /* String literals FIXME: add escapes */
"\""		{ BEGIN(SC_STRING); }

<SC_STRING>{
	"\""	{
    	BEGIN(INITIAL);
	    return TOKEN_VAL(STRING, string_content);
	}

	.|{escape}		{ string_content.append(yytext); }

  \\.           {
                  tp.error_ << misc::error::error_type::scan
                            << tp.location_
                            << ": invalid escape sequence: "
                            << yytext
                            << "\n";
                }
}

 /* Comments */
<SC_COMMENT,INITIAL>"/*"		{ yy_push_state(SC_COMMENT); }

<SC_COMMENT>{
	"*/"	{ yy_pop_state(); }
	\n		{ tp.location_.lines(yyleng); tp.location_.step(); }
	.		{ }
}

 /* Regular keywords */
"array"		{ return TOKEN(ARRAY); }
"if"		{ return TOKEN(IF); }
"then"		{ return TOKEN(THEN); }
"else"		{ return TOKEN(ELSE); }
"while"		{ return TOKEN(WHILE); }
"for"		{ return TOKEN(FOR); }
"to"		{ return TOKEN(TO); }
"do"		{ return TOKEN(DO); }
"let"		{ return TOKEN(LET); }
"in"		{ return TOKEN(IN); }
"end"		{ return TOKEN(END); }
"of"		{ return TOKEN(OF); }
"break"		{ return TOKEN(BREAK); }
"nil"		{ return TOKEN(NIL); }
"function"	{ return TOKEN(FUNCTION); }
"var"		{ return TOKEN(VAR); }
"type"		{ return TOKEN(TYPE); }
"import"	{ return TOKEN(IMPORT); }
"primitive"	{ return TOKEN(PRIMITIVE); }

 /* Object-oriented extension keywords */
"class"		{ return TOKEN(CLASS); }
"extends"	{ return TOKEN(EXTENDS); }
"method"	{ return TOKEN(METHOD); }
"new"		{ return TOKEN(NEW); }

 /* Symbols */
","			{ return TOKEN(COMMA); }
":"			{ return TOKEN(COLON); }
";"			{ return TOKEN(SEMI); }
"("			{ return TOKEN(LPAREN); }
")"			{ return TOKEN(RPAREN); }
"["			{ return TOKEN(LBRACK); }
"]"			{ return TOKEN(RBRACK); }
"{"			{ return TOKEN(LBRACE); }
"}"			{ return TOKEN(RBRACE); }
"."			{ return TOKEN(DOT); }
"+"			{ return TOKEN(PLUS); }
"-"			{ return TOKEN(MINUS); }
"*"			{ return TOKEN(TIMES); }
"/"			{ return TOKEN(DIVIDE); }
"="			{ return TOKEN(EQ); }
"<>"		{ return TOKEN(NE); }
"<"			{ return TOKEN(LT); }
"<="		{ return TOKEN(LE); }
">"			{ return TOKEN(GT); }
">="		{ return TOKEN(GE); }
"&"			{ return TOKEN(AND); }
"|"			{ return TOKEN(OR); }
":="		{ return TOKEN(ASSIGN); }

 /* Identifiers */
({letter}({letter}|{digit}|"_")|"_main") {
    return TOKEN_VAL(ID, misc::symbol(yytext));
}

{whitespace} { }

{EOL}		{tp.location_.lines(); tp.location_.step(); /* maybe unnecessary */};

<<EOF>> { return TOKEN(EOF); };

. { 
    tp.error_ << misc::error::error_type::scan
              << tp.location_
              << ": Illegal character: "
              << yytext
              <<"\n";
  }

%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
