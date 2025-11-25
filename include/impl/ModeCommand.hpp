#pragma once

#include "ICommand.hpp"

class ModeCommand : public ICommand{
    public:
        ModeCommand();
        ~ModeCommand();

        void execute(Server& server, Client& client, const Message& message);
};
