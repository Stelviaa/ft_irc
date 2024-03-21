
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "includes/Server.hpp"
#include "includes/User.hpp"

int main(int argc, char **argv) {

    Server server(std::atoi(argv[0]));
    std::vector<User> user;
    (void) argc;
    while (true) {
        // Acceptation des connexions entrantes
        
        if ((user[0].setFd(accept(server.getFd(), (struct sockaddr *)server.getAddress(), (socklen_t*)server.getLenAddress()))) < 0) {
            //perror("Erreur lors de l'acceptation de la connexion");
            exit(EXIT_FAILURE);
        }

        std::cout << "Connexion acceptée" << std::endl;

        // Lecture et écriture de données sur le socket
        char buffer[1024] = {0};
        std::string welcome_message = "ff\r\n";

        send(user[0].getFd(), welcome_message.c_str(), welcome_message.length(), 0);
        

        recv(user[0].getFd(), buffer, 1024, 0);
        std::cout << "Message du client : " << buffer << std::endl;

        if (std::string(buffer).find("JOIN") != std::string::npos) {
            // Exemple de réponse au client pour rejoindre un canal
            std::string join_response = ":sforesti JOIN #blabla : Welcome to #channel\r\n";
            send(user[0].getFd(), join_response.c_str(), join_response.length(), 0);
        }

        //send(server_fd, buffer, valread, 0);
    }
    close(server.getFd());
    return 0;
}