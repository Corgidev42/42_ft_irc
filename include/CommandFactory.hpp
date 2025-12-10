#pragma once

#include <map>
#include <string>
#include "ICommand.hpp"

#include "impl/CapCommand.hpp"
#include "impl/InviteCommand.hpp"
#include "impl/JoinCommand.hpp"
#include "impl/KickCommand.hpp"
#include "impl/ModeCommand.hpp"
#include "impl/NickCommand.hpp"
#include "impl/PingCommand.hpp"
#include "impl/TopicCommand.hpp"
#include "impl/UserCommand.hpp"
#include "impl/PrivMsgCommand.hpp"
#include "impl/WhoCommand.hpp"

class CommandFactory{
  private:
    std::map<std::string, ICommand*> _commands;
    std::string _toUpper(const std::string& str);
  public:
    CommandFactory();
    ~CommandFactory();

    ICommand* getCommand(const std::string& commandName);
};