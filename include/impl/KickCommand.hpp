#pragma once

#include "ICommand.hpp"

class KickCommand : public ICommand {
public:
     KickCommand : public ICommand();
    ~ KickCommand : public ICommand();

    void execute(Server& server, Client& client, const Message& message);

};
