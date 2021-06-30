#include "irc.hpp"

void connectingClient(Base const &b){	// ---	accept a connexion --
	int sockfd = b.getSockFd();

    struct sockaddr_in addrClient;
    // sockaddr_in addrClient;
	int acc;
	socklen_t len;
	len = sizeof(addrClient);
	acc = accept(sockfd, (struct sockaddr *)&addrClient, &len);
	if (acc == -1){
		std::cout << "\e[31mfailed to connect a new client\n\e[0m";
		throw MyException();
	} else {
		std::cout << "\e[36mnew client !\n\e[0m";

	}
}