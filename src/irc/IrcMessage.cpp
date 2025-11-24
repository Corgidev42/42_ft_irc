#include "irc/IrcMessage.hpp"
#include "irc/IrcMessageTable.hpp"
#include "network/Client.hpp"

std::string formatMessage(
    const std::string& fmt,
    const std::map<std::string, std::string>& args)
{
    std::string result = fmt;

    std::map<std::string, std::string>::const_iterator it = args.begin();
    for (; it != args.end(); ++it)
    {
        const std::string key = "{" + it->first + "}";
        size_t pos = result.find(key);

        while (pos != std::string::npos)
        {
            result.replace(pos, key.length(), it->second);
            pos = result.find(key);
        }
    }

    return result + "\r\n";
}

void enqueueMessage(
    Client& client,
    int messageId,
    const std::map<std::string, std::string>& args)
{
    std::map<int, IrcMessageDef>::const_iterator it =
        IRC_MESSAGES.find(messageId);

    if (it == IRC_MESSAGES.end())
        throw std::runtime_error("Unknown IRC message ID");

    const IrcMessageDef& def = it->second;

    std::string msg = formatMessage(def.format, args);

    client.getWriteBuffer() += msg;

    client.enableWriteEvents();
}
