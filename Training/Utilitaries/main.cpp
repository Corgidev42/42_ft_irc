#include <iostream>
#include <csignal>
#include <unistd.h>

void handler(int sig) {
    std::cout << "\nReçu signal " << sig << " via sigaction\n";
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);     // AUCUN signal bloqué pendant le handler
    sa.sa_flags = SA_RESTART;     // Relance les appels bloquants (read, accept...)

    sigaction(SIGINT, &sa, NULL);

    std::cout << "Appuie sur CTRL-C...\n";

    while (true) {
        std::cout << "Travail...\n";
        sleep(1);
    }
}