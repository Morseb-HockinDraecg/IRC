#include "irc.hpp"

int main (int ac, char **av){

	(void)ac;
	if (ac != 2){
		std::cout << "need a number as arg\n";
		return -1;
	}

	Base b;

	init(av, b);


	int sockfd = b.getSockFd();

	// ---	accept a connexion --
    struct sockaddr_in addrClient;
    // sockaddr_in addrClient;
	int acc;
	socklen_t len;
	// addrClient = 0;
	len = sizeof(addrClient);
	acc = accept(sockfd, (struct sockaddr *)&addrClient, &len);
	if (acc == -1){
		std::cout << "\e[31mfailed to connect a new client\n\e[0m";
	} else
		std::cout << "\e[32mnew client !\n\e[0m";

}