#ifndef IRC_HPP
#define IRC_HPP

//	defines

#define SUCCESS 0
#define	FAIL 1
#define	ERROR -1

#define FALSE 0
#define TRUE 1

// includes

#include <unistd.h> //	write
#include <stdlib.h>	//	exit
#include <cerrno>	//	errno

#include <cstdio>		// perror
#include <netinet/in.h> // struct sockaddr_in
#include <sys/types.h>	// sockets
#include <sys/socket.h>	// sockets
#include <netdb.h>		// gethostbyname
#include <string.h>		// memset
#include <sys/poll.h>	// epoll not available on our machine - pref poll than select
#include <fcntl.h>		// fcntl

#include <sys/types.h>	//revc

// class
#include "Socket.hpp"
#include "exception.hpp"
#include "Server.hpp"
// class msg
#include "Password.hpp"



//	proto functions
bool init(int ac, char **av, Socket &b);
Client *connectingClient(Socket const &b);
int	msg(int fd, Server &s);


void pollLoop(Socket &b);


#endif
