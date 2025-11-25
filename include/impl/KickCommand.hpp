#pragma once

#include "ICommand.hpp"

class KickCommand : public ICommand {
public:
    KickCommand();
    ~KickCommand();

    void execute(Server& server, Client& client, const Message& message);

    
};
