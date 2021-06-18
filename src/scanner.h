//
// Created by 薛伟 on 2021/5/24.
//

#ifndef TOY_COMPILER_SCANNER_H
#define TOY_COMPILER_SCANNER_H

#if !defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

#include <fstream>
#include <string>
#include "location.hh"
#include "parser.tab.hh"

namespace TOY_COMPILER  {
    class Scanner: public yyFlexLexer {
      public:
    public:
        Scanner(std::istream *in) : yyFlexLexer(in){};

        virtual ~Scanner() = default;

        // get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual int yylex(TOY_COMPILER::Parser::semantic_type * const lval,
                          TOY_COMPILER::Parser::location_type *location);
        // YY_DECL defined in spl_lexer.l
        // Method body created by flex in spl_lexer.yy.cc

    private:
        /* yyval ptr */
        TOY_COMPILER::Parser::semantic_type *yylval = nullptr;
    };
} // namespace yyFlexLexer

#endif // TOY_COMPILER_SCANNER_H
