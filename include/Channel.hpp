#pragma once

#include "network/Client.hpp"
#include "network/Server.hpp"

class Server;

class Channel {
public:
  Channel();
  Channel(const std::string& name, Client* client);
  ~Channel();

  string getName() const;
  string getTopic() const;
  string getKey() const;
  size_t getLimit() const;
  size_t getUserCount() const;

  string getModeStr() const;

  Channel& setTopic(const string& topic);
  Channel& setKey(const string& key);
  Channel& setLimit(size_t limit);
  Channel& setMode(char mode, bool active); // active / desactive un mode

  void addClient(Client* client);
  void removeClient(Client* client);
  bool hasClient(Client* client);

  Client* getClientByNick(const string& nick);

  void addOperator(Client* client);
  void removeOperator(Client* client);
  bool isOperator(Client* client);

  void addInvited(Client* client);
  void removeInvited(Client* client);
  bool isInvited(Client* client);

  bool hasMode(char mode) const;

  void broadcast(const string& msg, Server& server);
  void broadcastExcept(const string& msg, Server& server, Client* sender);

  string buildNamesList();


private:
  string _name;
  string _topic;
  string _key; // pour le mode k
  size_t _limit; //pour le mode l

  bool _isInviteOnly; // +i
  bool _isTopicRestricted; // +t
  bool _isKeyMode; // +k
  bool _isLimitMode; // +l

  map<string, Client *> _clients;
  vector<Client *> _operators;
  vector<Client *> _invited;
};
