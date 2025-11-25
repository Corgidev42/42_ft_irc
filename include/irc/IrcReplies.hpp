#ifndef IRC_REPLIES_HPP
#define IRC_REPLIES_HPP

#include "network/Server.hpp"
#include "network/Client.hpp"

#include <map>
#include <string>

class IRCReplies
{
public:
    IRCReplies();
    ~IRCReplies();

    // Remplace {var} dans un template par les valeurs dans vars
    std::string formatReply(int code,
                                   const std::map<std::string, std::string>& vars);

private:
    const std::map<int, std::string>& _ircTemplates;

    // Récupérer la table
    const std::map<int, std::string>& getTemplates();

    std::string replaceAll(const std::string& input,
                            const std::string& pattern,
                            const std::string& replacement);

};

extern IRCReplies ircReplies;

#endif
