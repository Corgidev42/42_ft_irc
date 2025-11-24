#pragma once

#include "ICommand.hpp"

class InviteCommand : public ICommand {
public:
    InviteCommand();
    ~InviteCommand();

    void execute(Server& server, Client& client, const Message& message);
};
