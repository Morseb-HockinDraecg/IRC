#include "irc.hpp"

int main (int ac, char **av){

(void)ac;
if (ac != 2){
	std::cout << "need a number as arg\n";
	return -1;
}


	// ---  struct needed 4 bind ---
    struct sockaddr_in addr;
	uint16_t port = atoi(av[1]);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;		//	AF_INET = Address Family, Internet = IP Addresses //	PF_INET = Protocol Family, Internet = IP, TCP/IP or UDP/IP
	addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	addr.sin_port = htons(port);

	// ---  init socket  ---
	int sockfd;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		std::cout << "Socket creation failed\n";
		return (-1);
	} else
	std::cout << "Socket created successfully !\n";
	
	// ---  bind the socket to a name  ---

	// int bindsock = bind(sockfd, static_cast<const struct sockaddr *>(&addr), sizeof(addr));
	int bindsock = bind(sockfd, (const struct sockaddr *)(&addr), sizeof(addr));	//cast en c++ ?
	if (bindsock == -1){
		std::cout << "Bind failed\n";
		return (-1);
	} else
	std::cout << "Bind succeed !\n";

	// wait for connection
	int	listensock;
	listensock = listen(sockfd, 0);
	if (listensock == -1){
		std::cout << "listen failed\n";
	} else
		std::cout << "listen succeed !\n";

}