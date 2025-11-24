#include "irc/IrcMessageTable.hpp"

const std::map<int, IrcMessageDef> initMessageTable()
{
    std::map<int, IrcMessageDef> m;

    m.insert(std::make_pair(RPL_WELCOME,
        IrcMessageDef("001", ":{server} 001 {nick} :Welcome to IRC!")));

    m.insert(std::make_pair(RPL_YOURHOST,
        IrcMessageDef("002", ":{server} 002 {nick} :Your host is {server}")));

    m.insert(std::make_pair(RPL_NAMREPLY,
        IrcMessageDef("353", ":{server} 353 {nick} = {channel} :{names}")));

    m.insert(std::make_pair(RPL_ENDOFNAMES,
        IrcMessageDef("366", ":{server} 366 {nick} {channel} :End of /NAMES list.")));

    m.insert(std::make_pair(CMD_JOIN,
        IrcMessageDef("JOIN", ":{nick} JOIN {channel}")));

    m.insert(std::make_pair(CMD_PRIVMSG,
        IrcMessageDef("PRIVMSG", ":{nick} PRIVMSG {target} :{text}")));

    m.insert(std::make_pair(CMD_INVITE,
        IrcMessageDef("INVITE", ":{nick} INVITE {target} :{channel}")));

    m.insert(std::make_pair(CMD_KICK,
        IrcMessageDef("KICK", ":{nick} KICK {channel} {target} :{reason}")));

    m.insert(std::make_pair(CMD_MODE,
        IrcMessageDef("MODE", ":{nick} MODE {target} :{modes}")));

    m.insert(std::make_pair(CMD_NICK,
        IrcMessageDef("NICK", ":{nick} NICK {newnick}")));

    m.insert(std::make_pair(CMD_PING,
        IrcMessageDef("PING", "PING :{server}")));

    m.insert(std::make_pair(CMD_TOPIC,
        IrcMessageDef("TOPIC", ":{nick} TOPIC {channel} :{topic}")));

    m.insert(std::make_pair(CMD_USER,
        IrcMessageDef("USER", "USER {username} 0 * :{realname}")));

    return m;
}

const std::map<int, IrcMessageDef> IRC_MESSAGES = initMessageTable();
