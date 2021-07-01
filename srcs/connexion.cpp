#include "irc.hpp"

Client *connectingClient(Socket const &b){	// ---	accept a connexion --
	Client	*cl = new Client;
	int sockfd = b.getSockFd();

    sockaddr_in addrClient;
	socklen_t addrClientSize;
	int acc;
	addrClientSize = sizeof(addrClient);
	acc = accept(sockfd, (struct sockaddr *)&addrClient, &addrClientSize);
	if (acc == ERROR){
		if (errno != EWOULDBLOCK)
			perror("  accept() failed");
		std::cerr << "\e[31mfailed to connect a new client\n\e[0m";
		throw MyException();
	} else {
		std::cout << "\e[36mnew client !\n\e[0m";
	}
	cl->setClientSocket(acc);
	cl->setAddrClient(addrClient);
	cl->setAddrClientSize(addrClientSize);
	return cl;
}