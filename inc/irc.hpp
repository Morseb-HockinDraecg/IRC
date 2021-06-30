#ifndef IRC_HPP
#define IRC_HPP


#include <unistd.h> // write


#include <netinet/in.h> // struct sockaddr_in
#include <sys/types.h>	//sockets
#include <sys/socket.h>	//sockets

// class
#include "base.hpp"
#include "exception.hpp"

//	define

#define SUCCESS 0
#define	FAIL 1

//	proto functions
bool init(int ac, char **av, Base &b);
void connectingClient(Base const &b);



#endif