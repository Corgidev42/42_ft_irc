#include "common.hpp"
#include "Server.hpp"

int main(int argc, char *argv[])
{
    // Tester la commande "./ircserv <port> <password>"

    string port = argv[1];
    string password = argv[2];

    // Server initialisation
    Server server(port, password);

    // Server run
    // try {
        server.run();
    // } catch (exception& e) {
    //     cout << e.what() << endl;
    // }

    //Server close
    server.sclose();

    return (1);
}















// #include <iostream>
// #include <cstring>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #include <sys/select.h>
// #include <string>

// using namespace std;

// int main() {
//     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serverSocket < 0) { cerr << "Erreur socket\n"; return 1; }

//     int opt = 1;
//     if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
//         cerr << "Erreur setsockopt\n"; return 1;
//     }

//     sockaddr_in serverAddress;
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_port = htons(6667); // port IRC
//     serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

//     if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
//         cerr << "Erreur bind\n"; return 1;
//     }

//     if (listen(serverSocket, 1) < 0) { cerr << "Erreur listen\n"; return 1; }

//     cout << "Serveur en attente de connexion...\n";
//     int clientSocket = accept(serverSocket, NULL, NULL);
//     if (clientSocket < 0) { cerr << "Erreur accept\n"; return 1; }

//     string clientNick = "Client"; // pseudo par défaut
//     string serverNick = "Server"; // pseudo serveur

//     string rpl_welcome = ":" + serverNick + " 001 " + clientNick + " :Bienvenue sur ce mini serveur IRC\r\n";
//     send(clientSocket, rpl_welcome.c_str(), rpl_welcome.size(), 0);

//     cout << "Client connecté !\n";

//     fd_set readfds;
//     char buffer[1024];
//     string message;

//     while (true) {
//         FD_ZERO(&readfds);
//         FD_SET(clientSocket, &readfds);
//         FD_SET(STDIN_FILENO, &readfds);

//         int maxfd = clientSocket > STDIN_FILENO ? clientSocket : STDIN_FILENO;
//         int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);
//         if (activity < 0) { cerr << "Erreur select\n"; break; }

//         // recevoir message du client
//         if (FD_ISSET(clientSocket, &readfds)) {
//             memset(buffer, 0, sizeof(buffer));
//             int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
//             if (bytesReceived <= 0) {
//                 cout << "Client déconnecté.\n";
//                 break;
//             }
//             buffer[bytesReceived] = '\0';
//             cout << clientNick << ": " << buffer << endl;

//             // si client envoie NICK, on l'enregistre
//             string received(buffer);
//             if (received.find("NICK ") == 0) {
//                 clientNick = received.substr(5);
//                 if (!clientNick.empty() && (clientNick.back() == '\n' || clientNick.back() == '\r'))
//                     clientNick.erase(clientNick.size() - 1);
//                 if (!clientNick.empty() && (clientNick.back() == '\n' || clientNick.back() == '\r'))
//                     clientNick.erase(clientNick.size() - 1);
//                 cout << "Client Nick enregistré: " << clientNick << endl;
//             }

//             if (received.rfind("PING", 0) == 0) {
//                 string pong = "PONG " + received.substr(5) + "\r\n";
//                 send(clientSocket, pong.c_str(), pong.size(), 0);
//                 continue;
//             }
//         }

//         // envoyer message depuis serveur
//         if (FD_ISSET(STDIN_FILENO, &readfds)) {
//             getline(cin, message);
//             if (message == "exit") break;

//             string ircMessage = ":" + serverNick + " PRIVMSG " + clientNick + " :" + message + "\r\n";
//             send(clientSocket, ircMessage.c_str(), ircMessage.size(), 0);
//         }
//     }

//     close(clientSocket);
//     close(serverSocket);
//     return 0;
// }