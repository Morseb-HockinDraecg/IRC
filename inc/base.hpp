#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <string>

#include <netinet/in.h> // struct sockaddr_in
#include <sys/types.h>	//sockets
#include <sys/socket.h>	//sockets

class Base{

	struct sockaddr_in	addr;
	int					sockFd;

public:
	Base();
	~Base();
	Base (Base const &);
	Base & operator=(Base const &);

	void	setAddr(struct sockaddr_in v);
	void	setSockFd(int v);

	struct sockaddr_in	getAddr() const;
	int					getSockFd() const;
};

#endif