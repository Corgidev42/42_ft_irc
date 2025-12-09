#include "common.hpp"
#include "network/Server.hpp"
#include "spdlog/spdlog.h"

struct ParserIRC parserIRC;

void initParserIRC() {
    parserIRC.grammar.addRule("<letter> ::= 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z'");
    parserIRC.grammar.addRule("<number> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'");
    parserIRC.grammar.addRule("<special> ::= '-' | '[' | ']' | '\\\\' | '`' | '^' | '{' | '}'");

    parserIRC.grammar.addRule("<nospace> ::= '!' | '\"' | '#' | '$' | '%' | '&' | ''' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | ':' | ';' | '<' | '=' | '>' | '?' | '@' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '[' | '\' | ']' | '^' | '_' | '`' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | '{' | '|' | '} | '~'");
    parserIRC.grammar.addRule("<safechar> ::= ' ' | '!' | '\"' | '#' | '$' | '%' | '&' | ''' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | ':' | ';' | '<' | '=' | '>' | '?' | '@' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '[' | '\' | ']' | '^' | '_' | '`' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | '{' | '|' | '}' | '~'");
    parserIRC.grammar.addRule("<nospecial> ::= '!' | '\"' | '#' | '$' | '%' | '&' | ''' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | ';' | '<' | '=' | '>' | '?' | '@' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '[' | '\' | ']' | '^' | '_' | '`' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | '{' | '|' | '}' | '~'");
    parserIRC.grammar.addRule("<nonwhite> ::= <nospace>");

    parserIRC.grammar.addRule("<SPACE> ::= ' ' { ' ' }");
    parserIRC.grammar.addRule("<crlf> ::= '\r' '\n'");

    parserIRC.grammar.addRule("<middle> ::= <nospecial> { <nospace> }");
    parserIRC.grammar.addRule("<trailing> ::= { <safechar> }");

    parserIRC.grammar.addRule("<params> ::= <SPACE> [ ':' <trailing> | <middle> [ <params> ] ]");
    parserIRC.grammar.addRule("<command> ::= <letter> { <letter> } | <number> <number> <number>");

    parserIRC.grammar.addRule("<nick> ::= <letter> { <letter> | <number> | <special> }");
    parserIRC.grammar.addRule("<user> ::= <nonwhite> { <nonwhite> }");

    parserIRC.grammar.addRule("<hostname-char> ::= <letter> | <number> | '-'");
    parserIRC.grammar.addRule("<hostname-end> ::= <letter> | <number>");
    parserIRC.grammar.addRule("<servername> ::= <letter> { <hostname-char> } <hostname-end>");

    parserIRC.grammar.addRule("<prefix> ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]");
    parserIRC.grammar.addRule("<message> ::= [ ':' <prefix> <SPACE> ] <command> <params> <crlf>");
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    // Tester la commande "./ircserv <port> <password>"

	spdlog::info("Welcome to spdlog!");

    initParserIRC();

    string port = argv[1];
    string password = argv[2];

    // Server initialisation
    Server server(port, password);

    // Server run
    // try {
        server.run();
    // } catch (exception& e) {
    //     cout << e.what() << endl;
    // }

    //Server close
    server.sclose();

    return (1);
}
