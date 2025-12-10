#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <map>

using namespace std;

#include "bnfparser/DataExtractor.hpp"
#include "bnfparser/Grammar.hpp"
#include "bnfparser/BNFParser.hpp"
#include "bnfparser/Debug.hpp"

#include "spdlog/spdlog.h"

struct ParserIRC {
    Grammar grammar;
    BNFParser parser;
    ASTNode* ast;
    size_t consumed;

    ParserIRC() : grammar(), parser(grammar), ast(NULL), consumed(0) {}
};

extern ParserIRC parserIRC;