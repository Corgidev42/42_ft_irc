#pragma once

#include "Client.hpp"

class Channel {
public:
  Channel();
  Channel(const std::string& name, Client* creator);
  ~Channel();

  string getName() const;
  string getTopic() const;
  string getkey() const;
  size_t getLimit() const;
  size_t getUserCount() const;

  string getModeStr() const;

  void setTopic(const string& topic);
  void setKey(const string& key);
  void setLimit(size_t limit);
  void setMode(char mode, bool active); // active / desactive un mode

  void addClient(Client* client);
  void removeClient(Client* client);
  bool hasClient(Client* client);

  Client* getClientByNick(const string& nick);

  void addOperator(Client* client);
  void removeOperator(Client* client);
  bool isOperator(Client* client);

  void addInvited(Client* client);
  void removeInvited(Client* client);
  bool hasMode(char mode) const;

  void broadcast(const string& msg);
  void broadcastExcept(const string& msg, Client* sender);


private:
  string _name;
  string _topic;
  string _key; // pour le mode k
  size_t limit; //pour le mode l

  bool _isInviteOnly // +i
  bool _isTopicRestricted // +t
  bool _isKeyMode // +k
  bool _isLimitMode // +l

  map<string, Client *> _clients;
  vector<Client *> _admins;
  vector<Client *> _invited;


};
