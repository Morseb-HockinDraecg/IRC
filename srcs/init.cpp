#include "irc.hpp"

static void	init_struct(char **av, Base & b);	// ---  struct needed 4 bind ---
static void	initSocket(Base &b);				// ---  init socket  ---
static void	initBind(Base &b);					// ---  bind the socket to a name  ---
static void	initListen(Base &b);				// ---  waiting for a connection to the socket ---

bool init(int ac, char **av, Base &b){
	if (ac != 2){
		std::cout << "need a number as arg\n";
		return false;
	}
	try {
		init_struct(av, b);
		initSocket(b);
		initBind(b);
		initListen(b);
	} catch (const MyException &e){
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

//
//	--- --- statics functions --- ---
//

static void	init_struct(char **av, Base & b){
    struct sockaddr_in addr;
	uint16_t port = atoi(av[1]);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;		//	AF_INET = Address Family, Internet = IP Addresses //	PF_INET = Protocol Family, Internet = IP, TCP/IP or UDP/IP
	addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	addr.sin_port = htons(port);
	b.setAddr(addr);
}

static void	initSocket(Base &b){
	int sockfd;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);	//PF_INET => IPv4  || PF_INET6 => IPv6
	if (sockfd == -1){
		std::cout << "\e[31mSocket creation failed\n\e[0m";
		throw MyException();
	} else
	std::cout << "\e[32mSocket created successfully !\n\e[0m";
	b.setSockFd(sockfd);
}

static void	initBind(Base &b){
	struct sockaddr_in addr = b.getAddr();
	int sockfd = b.getSockFd();

	int bindsock = bind(sockfd, (const struct sockaddr *)(&addr), sizeof(addr));	//cast en c++ ?
	if (bindsock == -1){
		std::cout << "\e[31mBind failed\n\e[0m";
		throw MyException();
	} else
	std::cout << "\e[32mBind succeed !\n\e[0m";
}

static void	initListen(Base &b){
	int sockfd = b.getSockFd();

	int	listensock;
	listensock = listen(sockfd, 0);
	if (listensock == -1){
		std::cout << "\e[31mlisten failed\n\e[0m";
		throw MyException();
	} else
		std::cout << "\e[32mlisten succeed !\n\e[0m";
}

