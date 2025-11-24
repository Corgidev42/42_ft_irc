#pragma once

#include "ICommand.hpp"

class PingCommand : public ICommand{
    public:
        PingCommand();
        ~PingCommand();

        void execute(Server& server, Client& client, const Message& message);
};
