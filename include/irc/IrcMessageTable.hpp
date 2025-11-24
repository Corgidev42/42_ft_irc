#pragma once

#include <map>
#include <string>

enum IrcMessageId {
    RPL_WELCOME,
    RPL_YOURHOST,
    RPL_NAMREPLY,
    RPL_ENDOFNAMES,
    CMD_JOIN,
    CMD_PART,
    CMD_PRIVMSG,
    CMD_INVITE,
    CMD_KICK,
    CMD_MODE,
    CMD_NICK,
    CMD_PING,
    CMD_TOPIC,
    CMD_USER
};

struct IrcMessageDef
{
    std::string code;
    std::string format;

    IrcMessageDef() {}
    IrcMessageDef(const std::string& c, const std::string& f)
        : code(c), format(f) {}
};

extern const std::map<int, IrcMessageDef> IRC_MESSAGES;

const std::map<int, IrcMessageDef> initMessageTable();
