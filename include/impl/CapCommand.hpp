#pragma once

#include "ICommand.hpp"

class CapCommand : public ICommand {

    public:
        CapCommand();
        ~CapCommand();

        void execute(Server& server, Client& client, const Message& message);
};
