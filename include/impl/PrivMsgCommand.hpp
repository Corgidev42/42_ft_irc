#pragma once

#include "ICommand.hpp"

class PrivMsgCommand : public ICommand {
public:
    PrivMsgCommand();
    ~PrivMsgCommand();

    void execute(Server& server, Client& client, const Message& message);
};
