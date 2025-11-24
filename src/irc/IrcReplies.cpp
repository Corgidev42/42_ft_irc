#include "irc/IrcReplies.hpp"

static std::map<int, std::string> initTemplates()
{
    std::map<int, std::string> m;

    // --- RPLS 200–399 ---

    m[200] = "{server} 200 {nick} Link {linkname} {sendq} {sentmsg} {sentbytes} {recvmsg} {recvbytes}";
    m[201] = "{server} 201 {nick} Try. {class} {server}";
    m[202] = "{server} 202 {nick} H.S. {class} {server}";
    m[203] = "{server} 203 {nick} ???? {class} {server}";
    m[204] = "{server} 204 {nick} Oper {class} {nick2}";
    m[205] = "{server} 205 {nick} User {class} {nick2}";
    m[206] = "{server} 206 {nick} Serv {class} {server2} {mask} {hopcount}";
    m[208] = "{server} 208 {nick} {newtype} 0 {clientname}";
    m[211] = "{server} 211 {nick} {linkname} {sendq} {sentmsg} {sentbytes} {recvmsg} {recvbytes}";
    m[212] = "{server} 212 {nick} {command} {count} {bytecount} {remotecount}";
    m[213] = "{server} 213 {nick} C {host} * {name}";
    m[214] = "{server} 214 {nick} N {host} * {name}";
    m[215] = "{server} 215 {nick} I {host} * {name}";
    m[216] = "{server} 216 {nick} K {host} * {username} {port} {class}";
    m[218] = "{server} 218 {nick} Y {class} {ping} {connect} {max}";
    m[219] = "{server} 219 {nick} {statschar} :End of STATS report";

    m[221] = "{server} 221 {nick} {modes}";

    m[241] = "{server} 241 {nick} L {hostmask} * {servername}";
    m[242] = "{server} 242 {nick} :Server Up {days} days {hours}:{mins}:{secs}";
    m[243] = "{server} 243 {nick} O {hostmask} * {name}";
    m[244] = "{server} 244 {nick} H {hostmask} * {servername}";

    m[251] = "{server} 251 {nick} :There are {users} users and {invisible} invisible on {servers} servers";
    m[252] = "{server} 252 {nick} {ops} :operator(s) online";
    m[253] = "{server} 253 {nick} {unknown} :unknown connection(s)";
    m[254] = "{server} 254 {nick} {channels} :channels formed";
    m[255] = "{server} 255 {nick} :I have {clients} clients and {servers} servers";

    m[256] = "{server} 256 {nick} :Administrative info about {server2}";
    m[257] = "{server} 257 {nick} :{loc1}";
    m[258] = "{server} 258 {nick} :{loc2}";
    m[259] = "{server} 259 {nick} :{email}";

    m[300] = "{server} 300 {nick} :None";
    m[301] = "{server} 301 {nick} {target} :{awaymsg}";
    m[302] = "{server} 302 {nick} :{userhost}";
    m[303] = "{server} 303 {nick} :{isonline}";
    m[305] = "{server} 305 {nick} :You are no longer marked as being away";
    m[306] = "{server} 306 {nick} :You have been marked as being away";

    m[311] = "{server} 311 {nick} {target} {user} {host} * :{realname}";
    m[312] = "{server} 312 {nick} {target} {server2} :{serverinfo}";
    m[313] = "{server} 313 {nick} {target} :is an IRC operator";
    m[317] = "{server} 317 {nick} {target} {idle} {signon} :seconds idle, signon time";
    m[318] = "{server} 318 {nick} {target} :End of WHOIS list";
    m[319] = "{server} 319 {nick} {target} :{channels}";

    m[314] = "{server} 314 {nick} {target} {user} {host} * :{realname}";
    m[369] = "{server} 369 {nick} {target} :End of WHOWAS";

    m[321] = "{server} 321 {nick} Channel :Users Name";
    m[322] = "{server} 322 {nick} {channel} {count} :{topic}";
    m[323] = "{server} 323 {nick} :End of LIST";

    m[324] = "{server} 324 {nick} {channel} {modes}";
    m[331] = "{server} 331 {nick} {channel} :No topic is set";
    m[332] = "{server} 332 {nick} {channel} :{topic}";

    m[341] = "{server} 341 {nick} {target} {channel}";
    m[342] = "{server} 342 {nick} {user} :Summoning user to IRC";

    m[351] = "{server} 351 {nick} {version} {debug}";

    m[352] = "{server} 352 {nick} {channel} {user} {host} {server2} {nick2} {flags} :{hopcount} {realname}";
    m[315] = "{server} 315 {nick} {channel} :End of WHO list";

    m[353] = "{server} 353 {nick} {symbol} {channel} :{names}";
    m[366] = "{server} 366 {nick} {channel} :End of NAMES list";

    m[364] = "{server} 364 {nick} {server2} {distance} :{info}";
    m[365] = "{server} 365 {nick} {mask} :End of LINKS list";

    m[367] = "{server} 367 {nick} {channel} {banmask}";
    m[368] = "{server} 368 {nick} {channel} :End of channel ban list";

    m[371] = "{server} 371 {nick} :{info}";
    m[374] = "{server} 374 {nick} :End of INFO list";

    m[375] = "{server} 375 {nick} :- {server} Message of the day -";
    m[372] = "{server} 372 {nick} :- {line}";
    m[376] = "{server} 376 {nick} :End of MOTD command";

    m[381] = "{server} 381 {nick} :You are now an IRC operator";
    m[382] = "{server} 382 {nick} {configfile} :Rehashing";

    m[391] = "{server} 391 {nick} {server2} :{time}";

    m[392] = "{server} 392 {nick} :UserID Terminal Host";
    m[393] = "{server} 393 {nick} :{userentry}";
    m[394] = "{server} 394 {nick} :End of users";
    m[395] = "{server} 395 {nick} :Nobody logged in";


    // --- ERRORS 400–599 ---

    m[401] = "{server} 401 {nick} {target} :No such nick/channel";
    m[402] = "{server} 402 {nick} {server2} :No such server";
    m[403] = "{server} 403 {nick} {channel} :No such channel";
    m[404] = "{server} 404 {nick} {channel} :Cannot send to channel";
    m[405] = "{server} 405 {nick} {channel} :You have joined too many channels";
    m[406] = "{server} 406 {nick} {target} :There was no such nickname";
    m[407] = "{server} 407 {nick} {target} :Too many recipients";
    m[409] = "{server} 409 {nick} :No origin specified";

    m[411] = "{server} 411 {nick} :No recipient given";
    m[412] = "{server} 412 {nick} :No text to send";
    m[413] = "{server} 413 {nick} {mask} :No toplevel domain specified";
    m[414] = "{server} 414 {nick} {mask} :Wildcard in toplevel domain";

    m[421] = "{server} 421 {nick} {command} :Unknown command";
    m[422] = "{server} 422 {nick} :MOTD File is missing";
    m[423] = "{server} 423 {nick} {server2} :No administrative info available";
    m[424] = "{server} 424 {nick} :File error doing {fileop} on {file}";

    m[431] = "{server} 431 {nick} :No nickname given";
    m[432] = "{server} 432 {nick} {target} :Erroneous nickname";
    m[433] = "{server} 433 {nick} {target} :Nickname is already in use";
    m[436] = "{server} 436 {nick} {target} :Nickname collision KILL";

    m[441] = "{server} 441 {nick} {target} {channel} :They aren't on that channel";
    m[442] = "{server} 442 {nick} {channel} :You're not on that channel";
    m[443] = "{server} 443 {nick} {target} {channel} :is already on channel";

    m[444] = "{server} 444 {nick} {user} :User not logged in";
    m[445] = "{server} 445 {nick} :SUMMON has been disabled";
    m[446] = "{server} 446 {nick} :USERS has been disabled";

    m[451] = "{server} 451 {nick} :You have not registered";

    m[461] = "{server} 461 {nick} {command} :Not enough parameters";
    m[462] = "{server} 462 {nick} :You may not reregister";
    m[463] = "{server} 463 {nick} :Your host isn't among the privileged";
    m[464] = "{server} 464 {nick} :Password incorrect";
    m[465] = "{server} 465 {nick} :You are banned from this server";

    m[467] = "{server} 467 {nick} {channel} :Key already set";

    m[471] = "{server} 471 {nick} {channel} :Channel is full";
    m[472] = "{server} 472 {nick} {char} :is unknown mode char to me";
    m[473] = "{server} 473 {nick} {channel} :Cannot join channel (+i)";
    m[474] = "{server} 474 {nick} {channel} :Cannot join channel (+b)";
    m[475] = "{server} 475 {nick} {channel} :Cannot join channel (+k)";

    m[481] = "{server} 481 {nick} :Permission Denied- You're not an IRC operator";
    m[482] = "{server} 482 {nick} {channel} :You're not channel operator";
    m[483] = "{server} 483 {nick} :You can't kill a server!";

    m[491] = "{server} 491 {nick} :No O-lines for your host";

    m[501] = "{server} 501 {nick} :Unknown MODE flag";
    m[502] = "{server} 502 {nick} :Cannot change mode for other users";

    return m;
}

const std::map<int, std::string>& IRCReplies::getTemplates()
{
    static std::map<int, std::string> templates = initTemplates();
    return templates;
}

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

    std::string msg = it->second;

    for (std::map<std::string, std::string>::const_iterator vit = vars.begin();
         vit != vars.end(); ++vit)
    {
        std::string pattern = "{" + vit->first + "}";
        msg = replaceAll(msg, pattern, vit->second);
    }

    return msg;
}