#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

#include<list>

#include "Client.hpp"

class	AMessage;
class	Client;
// class	Channel;

class Server{

	AMessage			*coReg;
	// struct pollfd		fds[200];
	std::list<Client *>	clients;
	// std::list<Channel>	chan;

public:
	Server();
	~Server();
	Server (Server const &);
	Server & operator=(Server const &);

	void	addClient(Client *);
	void	delClient(std::string username);

	std::list<Client *>	getClients() const;
};

std::ostream & operator<<(std::ostream &, Server const &);

#endif