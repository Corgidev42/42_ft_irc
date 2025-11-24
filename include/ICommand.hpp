#pragma once

class Server;
class Client;

class ICommand{
  public:
    virtual ~ICommand(){}
    virtual void execute(Server& server, Client& client, const Message& message) = 0;

};
