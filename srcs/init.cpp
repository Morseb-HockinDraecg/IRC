#include "irc.hpp"

static void	init_struct(char **av, Socket & b);	// ---  struct needed 4 bind ---
static void	initSocket(Socket &b);				// ---  init socket + allow socket descriptor to be reuseable  ---   
static void	initBind(Socket &b);					// ---  bind the socket to a name  ---
static void	initListen(Socket &b);				// ---  waiting for a connection to the socket ---

bool init(int ac, char **av, Socket &b){
	if (ac != 2){
		std::cerr << "need a number as arg\n";
		return false;
	}
	try {
		init_struct(av, b);
		initSocket(b);
		initBind(b);
		initListen(b);
	} catch (const MyException &e){
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

//	
//	--- --- statics functions --- ---
//

static void	init_struct(char **av, Socket & b){
    struct sockaddr_in addr;
	uint16_t port = atoi(av[1]);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;		//	AF_INET = Address Family, Internet = IP Addresses //	PF_INET = Protocol Family, Internet = IP, TCP/IP or UDP/IP
	addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	addr.sin_port = htons(port);
	b.setAddr(addr);
}

static void	initSocket(Socket &b){
	int sockfd;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);	//PF_INET => IPv4  || PF_INET6 => IPv6
	if (sockfd == ERROR){
		perror("\e[31mSocket creation failed \e[0m");
		throw MyException();
	} else
	std::cout << "\e[32mSocket created successfully !\n\e[0m";

	int rc, on;	// Put the socket on reusable 
	rc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (rc == ERROR) {
		perror("Set option on socket failed");
		close(sockfd);
		exit(-1);
	}
	rc = fcntl(sockfd, F_SETFL, O_NONBLOCK);
	if (rc == ERROR) {
		perror("Fd non block failed");
		close(sockfd);
		exit(-1);
	}
	b.setSockFd(sockfd);
}

static void	initBind(Socket &b){
	struct sockaddr_in addr = b.getAddr();
	int sockfd = b.getSockFd();

	int rc;
	rc = bind(sockfd, (const struct sockaddr *)(&addr), sizeof(addr));
	if (rc == ERROR){
		perror("\e[31mBind failed \e[0m");
		throw MyException();
	} else
	std::cout << "\e[32mBind succeed !\n\e[0m";
}

static void	initListen(Socket &b){
	int sockfd = b.getSockFd();

	int	rc;
	rc = listen(sockfd, SOMAXCONN);
	if (rc == ERROR){
		perror("\e[31mListen failed \e[0m");
		throw MyException();
	} else
		std::cout << "\e[32mlisten succeed !\n\e[0m";
}

