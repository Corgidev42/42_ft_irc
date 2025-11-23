#include "Grammar.hpp"
#include "BNFParser.hpp"
#include "DataExtractor.hpp"

int main() {
    // 1. Create and configure grammar
    Grammar grammar;
    grammar.addRule("<letter> ::= 'a' | 'b' | 'c'");
    grammar.addRule("<word> ::= <letter> { <letter> }");
    grammar.addRule("<message> ::= <word> ' ' <word>");

    // 2. Create parser
    BNFParser parser(grammar);
    
    // 3. Parse input text
    std::string input = "hello world";
    size_t consumed = 0;
    ASTNode* ast = parser.parse("<message>", input, consumed);
    
    if (ast && consumed == input.length()) {
        std::cout << "Parsing successful!" << std::endl;
        std::cout << "Matched: " << ast->matched << std::endl;
        
        // 4. Extract structured data from AST
        DataExtractor extractor;
        ExtractedData data = extractor.extract(ast);
        
        // 5. Query extracted data
        if (data.has("<word>")) {
            std::vector<std::string> words = data.all("<word>");
            std::cout << "Found " << words.size() << " words:" << std::endl;
            for (size_t i = 0; i < words.size(); ++i) {
                std::cout << "  - " << words[i] << std::endl;
            }
        }
        
        delete ast;
    } else {
        std::cout << "Parsing failed" << std::endl;
    }
    
    return 0;
}