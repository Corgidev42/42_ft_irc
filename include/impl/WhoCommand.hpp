#pragma once

#include "ICommand.hpp"

class WhoCommand : public ICommand {
    public:
        WhoCommand();
        ~WhoCommand();

        void execute(Server& server, Client& client, const Message& message);
};
