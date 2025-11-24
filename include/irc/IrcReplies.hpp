#ifndef IRC_REPLIES_HPP
#define IRC_REPLIES_HPP

#include <map>
#include <string>

class IRCReplies
{
public:
    // Récupérer la table
    static const std::map<int, std::string>& getTemplates();

    // Remplace {var} dans un template par les valeurs dans vars
    static std::string formatReply(int code,
                                   const std::map<std::string, std::string>& vars);

private:
    static std::string replaceAll(const std::string& input,
                                  const std::string& pattern,
                                  const std::string& replacement);
};

#endif
