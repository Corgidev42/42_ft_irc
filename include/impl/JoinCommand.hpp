#pragma once

#include "ICommand.hpp"

class JoinCommand : public ICommand{
    public:
        JoinCommand();
        ~JoinCommand();

        void execute(Server& server, Client& client, const Message& message);
};
