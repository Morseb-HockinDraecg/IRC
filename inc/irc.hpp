#ifndef IRC_HPP
#define IRC_HPP


#include <unistd.h> // write


#include <netinet/in.h> // struct sockaddr_in
#include <sys/types.h>	//sockets
#include <sys/socket.h>	//sockets

// class
#include "base.hpp"
#include "exception.hpp"

// class Base;
void init(char **av, Base &b);

void	printForTest(void);

#endif