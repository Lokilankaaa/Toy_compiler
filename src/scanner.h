//
// Created by 薛伟 on 2021/5/24.
//

#ifndef TOY_COMPILER_SCANNER_H
#define TOY_COMPILER_SCANNER_H

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Toy_FlexLexer
#include <FlexLexer.h>
#endif
#undef YY_DECL
#define YY_DECL

#include <fstream>
#include <string>

namespace TOY_COMPILER  {
    class Scanner: public yyFlexLexer {
      public:
        Scanner(const std::fstream &fin);
//        Scanner(Marker::Driver &driver) : m_driver(driver) {}

//        virtual int TOY_COMPILER::Scanner::yylex(
//            TOY_COMPILER::Parser::semantic_type *const lval,
//            TOY_COMPILER::location_type *loc);

//        virtual TOY_COMPILER::Parser::semantic_type get_next_token();
    };
} // namespace yyFlexLexer

#endif // TOY_COMPILER_SCANNER_H
