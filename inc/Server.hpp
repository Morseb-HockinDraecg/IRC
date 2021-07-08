#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <string.h>
#include <sys/poll.h>


#include<list>

#include "Client.hpp"
#include "Socket.hpp"

class	AMessage;
class	Client;
class	Socket;
// class	Channel;

class Server{

	Socket const 		&sock;
	AMessage			*coReg;
	std::list<Client *>	clients;
	// std::list<Channel>	chan;

public:
	int					nfds;
	struct pollfd		fds[200];
	Server(Socket &b);
	~Server();
	Server (Server const &);
	Server & operator=(Server const &);

	void	addClient(Client *);
	void	delClient(std::string username);

	std::list<Client *>	getClients() const;
	Socket const &		getSocket() const;
};

std::ostream & operator<<(std::ostream &, Server const &);

#endif