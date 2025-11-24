// #include "PingCommand.hpp"

// PingCommand::PingCommand(){};
// PingCommand::~PingCommand(){};

// void PingCommand::execute(Server& server, Client& client, const Message& message){
//     if (message.params.empty()){
//         client.reply(ERR_NOORIGIN);
//         return ;
//     }

//     std::string token = message.params[0];
//     std::string pong = "PONG" + token;

//     client.reply(pong);

//     }
// }
