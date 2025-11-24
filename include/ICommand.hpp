#pragma once

#include "irc/IrcMessage.hpp"
#include "irc/IrcMessageTable.hpp"

class Server;
class Client;
class Message;

class ICommand{
  public:
    virtual ~ICommand(){}
    virtual void execute(Server& server, Client& client, const Message& message) = 0;

};
