#pragma once

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#include "bnfparser/DataExtractor.hpp"
#include "bnfparser/Grammar.hpp"
#include "bnfparser/BNFParser.hpp"
#include "bnfparser/Debug.hpp"

struct ParserIRC {
    Grammar grammar;
    BNFParser parser;
    ASTNode* ast;
    size_t consumed;

    ParserIRC() : grammar(), parser(grammar), ast(NULL), consumed(0) {}
};

extern ParserIRC parserIRC;