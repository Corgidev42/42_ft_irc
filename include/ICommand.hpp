#pragma once

#include "Message.hpp"
#include "irc/IrcNumeric.hpp"
#include "irc/IrcMakeVars.hpp"
#include "irc/IrcReplies.hpp"

class Server;
class Client;

class ICommand{
  public:
    virtual ~ICommand(){}
    virtual void execute(Server& server, Client& client, const Message& message) = 0;

};
