#include "irc/IrcReplies.hpp"
#include "irc/IrcNumeric.hpp"

static std::map<int, std::string> initTemplates()
{
    std::map<int, std::string> m;

    // --- Infos 001-005 ---

    m[RPL_WELCOME] = "{server} 001 {nick} :Welcome to the Internet Relay Network {nick}!{user}@{host}";
    m[RPL_YOURHOST] = "{server} 002 {nick} :Your host is {server}, running version {version}";
    m[RPL_CREATED] = "{server} 003 {nick} :This server was created {creation_date}";
    m[RPL_MYINFO] = "{server} 004 {nick} {server} {version} {user_modes} {channel_modes}";
    m[RPL_BOUNCE] = "{server} 005 {nick} {tokens} :are supported by this server";

    // --- RPLS 200–399 ---

    m[RPL_TRACELINK] = "{server} 200 {nick} Link {linkname} {sendq} {sentmsg} {sentbytes} {recvmsg} {recvbytes}";
    m[RPL_TRACECONNECTING] = "{server} 201 {nick} Try. {class} {server}";
    m[RPL_TRACEHANDSHAKE] = "{server} 202 {nick} H.S. {class} {server}";
    m[RPL_TRACEUNKNOWN] = "{server} 203 {nick} ???? {class} {server}";
    m[RPL_TRACEOPERATOR] = "{server} 204 {nick} Oper {class} {nick2}";
    m[RPL_TRACEUSER] = "{server} 205 {nick} User {class} {nick2}";
    m[RPL_TRACESERVER] = "{server} 206 {nick} Serv {class} {server2} {mask} {hopcount}";
    m[RPL_TRACENEWTYPE] = "{server} 208 {nick} {newtype} 0 {clientname}";
    m[RPL_STATSLINKINFO] = "{server} 211 {nick} {linkname} {sendq} {sentmsg} {sentbytes} {recvmsg} {recvbytes}";
    m[RPL_STATSCOMMANDS] = "{server} 212 {nick} {command} {count} {bytecount} {remotecount}";
    m[RPL_STATSCLINE] = "{server} 213 {nick} C {host} * {name}";
    m[RPL_STATSNLINE] = "{server} 214 {nick} N {host} * {name}";
    m[RPL_STATSILINE] = "{server} 215 {nick} I {host} * {name}";
    m[RPL_STATSKLINE] = "{server} 216 {nick} K {host} * {username} {port} {class}";
    m[RPL_STATSYLINE] = "{server} 218 {nick} Y {class} {ping} {connect} {max}";
    m[RPL_ENDOFSTATS] = "{server} 219 {nick} {statschar} :End of STATS report";

    m[RPL_UMODEIS] = "{server} 221 {nick} {modes}";

    m[RPL_STATSLLINE] = "{server} 241 {nick} L {hostmask} * {servername}";
    m[RPL_STATSUPTIME] = "{server} 242 {nick} :Server Up {days} days {hours}:{mins}:{secs}";
    m[RPL_STATSOLINE] = "{server} 243 {nick} O {hostmask} * {name}";
    m[RPL_STATSHLINE] = "{server} 244 {nick} H {hostmask} * {servername}";

    m[RPL_LUSERCLIENT] = "{server} 251 {nick} :There are {users} users and {invisible} invisible on {servers} servers";
    m[RPL_LUSEROP] = "{server} 252 {nick} {ops} :operator(s) online";
    m[RPL_LUSERUNKNOWN] = "{server} 253 {nick} {unknown} :unknown connection(s)";
    m[RPL_LUSERCHANNELS] = "{server} 254 {nick} {channels} :channels formed";
    m[RPL_LUSERME] = "{server} 255 {nick} :I have {clients} clients and {servers} servers";

    m[RPL_ADMINME] = "{server} 256 {nick} :Administrative info about {server2}";
    m[RPL_ADMINLOC1] = "{server} 257 {nick} :{loc1}";
    m[RPL_ADMINLOC2] = "{server} 258 {nick} :{loc2}";
    m[RPL_ADMINEMAIL] = "{server} 259 {nick} :{email}";

    m[RPL_NONE] = "{server} 300 {nick} :None";
    m[RPL_AWAY] = "{server} 301 {nick} {target} :{awaymsg}";
    m[RPL_USERHOST] = "{server} 302 {nick} :{userhost}";
    m[RPL_ISON] = "{server} 303 {nick} :{isonline}";
    m[RPL_UNAWAY] = "{server} 305 {nick} :You are no longer marked as being away";
    m[RPL_NOWAWAY] = "{server} 306 {nick} :You have been marked as being away";

    m[RPL_WHOISUSER] = "{server} 311 {nick} {target} {user} {host} * :{realname}";
    m[RPL_WHOISSERVER] = "{server} 312 {nick} {target} {server2} :{serverinfo}";
    m[RPL_WHOISOPERATOR] = "{server} 313 {nick} {target} :is an IRC operator";
    m[RPL_WHOISIDLE] = "{server} 317 {nick} {target} {idle} {signon} :seconds idle, signon time";
    m[RPL_ENDOFWHOIS] = "{server} 318 {nick} {target} :End of WHOIS list";
    m[RPL_WHOISCHANNELS] = "{server} 319 {nick} {target} :{channels}";

    m[RPL_WHOWASUSER] = "{server} 314 {nick} {target} {user} {host} * :{realname}";
    m[RPL_ENDOFWHOWAS] = "{server} 369 {nick} {target} :End of WHOWAS";

    m[RPL_LISTSTART] = "{server} 321 {nick} Channel :Users Name";
    m[RPL_LIST] = "{server} 322 {nick} {channel} {count} :{topic}";
    m[RPL_LISTEND] = "{server} 323 {nick} :End of LIST";

    m[RPL_CHANNELMODEIS] = "{server} 324 {nick} {channel} {modes}";
    m[RPL_NOTOPIC] = "{server} 331 {nick} {channel} :No topic is set";
    m[RPL_TOPIC] = "{server} 332 {nick} {channel} :{topic}";

    m[RPL_INVITING] = "{server} 341 {nick} {target} {channel}";
    m[RPL_SUMMONING] = "{server} 342 {nick} {user} :Summoning user to IRC";

    m[RPL_VERSION] = "{server} 351 {nick} {version} {debug}";

    m[RPL_WHOREPLY] = "{server} 352 {nick} {channel} {user} {host} {server2} {nick2} {flags} :{hopcount} {realname}";
    m[RPL_ENDOFWHO] = "{server} 315 {nick} {channel} :End of WHO list";

    m[RPL_NAMREPLY] = "{server} 353 {nick} {symbol} {channel} :{names}";
    m[RPL_ENDOFNAMES] = "{server} 366 {nick} {channel} :End of NAMES list";

    m[RPL_LINKS] = "{server} 364 {nick} {server2} {distance} :{info}";
    m[RPL_ENDOFLINKS] = "{server} 365 {nick} {mask} :End of LINKS list";

    m[RPL_BANLIST] = "{server} 367 {nick} {channel} {banmask}";
    m[RPL_ENDOFBANLIST] = "{server} 368 {nick} {channel} :End of channel ban list";

    m[RPL_INFO] = "{server} 371 {nick} :{info}";
    m[RPL_ENDOFINFO] = "{server} 374 {nick} :End of INFO list";

    m[RPL_MOTDSTART] = "{server} 375 {nick} :- {server} Message of the day -";
    m[RPL_MOTD] = "{server} 372 {nick} :- {line}";
    m[RPL_ENDOFMOTD] = "{server} 376 {nick} :End of MOTD command";

    m[RPL_YOUREOPER] = "{server} 381 {nick} :You are now an IRC operator";
    m[RPL_REHASHING] = "{server} 382 {nick} {configfile} :Rehashing";

    m[RPL_TIME] = "{server} 391 {nick} {server2} :{time}";

    m[RPL_USERSSTART] = "{server} 392 {nick} :UserID Terminal Host";
    m[RPL_USERS] = "{server} 393 {nick} :{userentry}";
    m[RPL_ENDOFUSERS] = "{server} 394 {nick} :End of users";
    m[RPL_NOUSERS] = "{server} 395 {nick} :Nobody logged in";


    // --- ERRORS 400–599 ---

    m[ERR_NOSUCHNICK] = "{server} 401 {nick} {target} :No such nick/channel";
    m[ERR_NOSUCHSERVER] = "{server} 402 {nick} {server2} :No such server";
    m[ERR_NOSUCHCHANNEL] = "{server} 403 {nick} {channel} :No such channel";
    m[ERR_CANNOTSENDTOCHAN] = "{server} 404 {nick} {channel} :Cannot send to channel";
    m[ERR_TOOMANYCHANNELS] = "{server} 405 {nick} {channel} :You have joined too many channels";
    m[ERR_WASNOSUCHNICK] = "{server} 406 {nick} {target} :There was no such nickname";
    m[ERR_TOOMANYTARGETS] = "{server} 407 {nick} {target} :Too many recipients";
    m[ERR_NOORIGIN] = "{server} 409 {nick} :No origin specified";

    m[ERR_NORECIPIENT] = "{server} 411 {nick} :No recipient given";
    m[ERR_NOTEXTTOSEND] = "{server} 412 {nick} :No text to send";
    m[ERR_NOTOPLEVEL] = "{server} 413 {nick} {mask} :No toplevel domain specified";
    m[ERR_WILDTOPLEVEL] = "{server} 414 {nick} {mask} :Wildcard in toplevel domain";

    m[ERR_UNKNOWNCOMMAND] = "{server} 421 {nick} {command} :Unknown command";
    m[ERR_NOMOTD] = "{server} 422 {nick} :MOTD File is missing";
    m[ERR_NOADMININFO] = "{server} 423 {nick} {server2} :No administrative info available";
    m[ERR_FILEERROR] = "{server} 424 {nick} :File error doing {fileop} on {file}";

    m[ERR_NONICKNAMEGIVEN] = "{server} 431 {nick} :No nickname given";
    m[ERR_ERRONEUSNICKNAME] = "{server} 432 {nick} {target} :Erroneous nickname";
    m[ERR_NICKNAMEINUSE] = "{server} 433 {nick} {target} :Nickname is already in use";
    m[ERR_NICKCOLLISION] = "{server} 436 {nick} {target} :Nickname collision KILL";

    m[ERR_USERNOTINCHANNEL] = "{server} 441 {nick} {target} {channel} :They aren't on that channel";
    m[ERR_NOTONCHANNEL] = "{server} 442 {nick} {channel} :You're not on that channel";
    m[ERR_USERONCHANNEL] = "{server} 443 {nick} {target} {channel} :is already on channel";

    m[ERR_NOLOGIN] = "{server} 444 {nick} {user} :User not logged in";
    m[ERR_SUMMONDISABLED] = "{server} 445 {nick} :SUMMON has been disabled";
    m[ERR_USERSDISABLED] = "{server} 446 {nick} :USERS has been disabled";

    m[ERR_NOTREGISTERED] = "{server} 451 {nick} :You have not registered";

    m[ERR_NEEDMOREPARAMS] = "{server} 461 {nick} {command} :Not enough parameters";
    m[ERR_ALREADYREGISTRED] = "{server} 462 {nick} :You may not reregister";
    m[ERR_NOPERMFORHOST] = "{server} 463 {nick} :Your host isn't among the privileged";
    m[ERR_PASSWDMISMATCH] = "{server} 464 {nick} :Password incorrect";
    m[ERR_YOUREBANNEDCREEP] = "{server} 465 {nick} :You are banned from this server";

    m[ERR_KEYSET] = "{server} 467 {nick} {channel} :Key already set";

    m[ERR_CHANNELISFULL] = "{server} 471 {nick} {channel} :Channel is full";
    m[ERR_UNKNOWNMODE] = "{server} 472 {nick} {char} :is unknown mode char to me";
    m[ERR_INVITEONLYCHAN] = "{server} 473 {nick} {channel} :Cannot join channel (+i)";
    m[ERR_BANNEDFROMCHAN] = "{server} 474 {nick} {channel} :Cannot join channel (+b)";
    m[ERR_BADCHANNELKEY] = "{server} 475 {nick} {channel} :Cannot join channel (+k)";

    m[ERR_NOPRIVILEGES] = "{server} 481 {nick} :Permission Denied- You're not an IRC operator";
    m[ERR_CHANOPRIVSNEEDED] = "{server} 482 {nick} {channel} :You're not channel operator";
    m[ERR_CANTKILLSERVER] = "{server} 483 {nick} :You can't kill a server!";

    m[ERR_NOOPERHOST] = "{server} 491 {nick} :No O-lines for your host";

    m[ERR_UMODEUNKNOWNFLAG] = "{server} 501 {nick} :Unknown MODE flag";
    m[ERR_USERSDONTMATCH] = "{server} 502 {nick} :Cannot change mode for other users";

    return m;
}

const std::map<int, std::string>& IRCReplies::getTemplates()
{
    static std::map<int, std::string> templates = initTemplates();
    return templates;
}

IRCReplies::IRCReplies() : _ircTemplates(getTemplates()) {}
IRCReplies::~IRCReplies() {}

// @TODO Even checker si global = bon
IRCReplies ircReplies;

std::string IRCReplies::replaceAll(const std::string& input,
                                   const std::string& pattern,
                                   const std::string& replacement)
{
    std::string result = input;
    std::string::size_type pos = 0;

    while ((pos = result.find(pattern, pos)) != std::string::npos)
    {
        result.erase(pos, pattern.length());
        result.insert(pos, replacement);
        pos += replacement.length();
    }

    return result;
}

std::string IRCReplies::formatReply(int code,
                                    const std::map<std::string, std::string>& vars)
{
    const std::map<int, std::string>& templates = getTemplates();

    std::map<int, std::string>::const_iterator it = templates.find(code);
    if (it == templates.end())
        return ""; // Aucun template trouvé

    std::string msg = ":" + it->second;

    for (std::map<std::string, std::string>::const_iterator vit = vars.begin();
         vit != vars.end(); ++vit)
    {
        std::string pattern = "{" + vit->first + "}";
        msg = replaceAll(msg, pattern, vit->second);
    }
    msg += "\r\n";

    return msg;
}