#include "irc.hpp"
#include <sys/ioctl.h>

void	nick(Server &s, int fd, std::string nick){
	Client *cl;

	cl = s.getClients(fd);
	if (cl)
		cl->setNickname(nick.substr(0, nick.find("\n")));
}

void	user(Server &s, int fd, std::string user){
	Client *cl;

	cl = s.getClients(fd);
	if (cl){
		if (cl->getNickname().empty()){
			send(fd, ERR_NONICKNAMEGIVEN, sizeof(ERR_NONICKNAMEGIVEN), 0);
			return;
		}
		cl->setUsername(user.substr(0, user.find("\n")));
		if (!cl->getRegister()){
			welcomeMsg(fd, s, *cl);
			cl->setRegister(true);
		}
	}
}

void	pong(int fd){
	send(fd, "PONG 127.0.0.1", strlen("PONG 127.0.0.1"), 0);
	std::cout << "*-*" << std::endl;
	std::cout << "PONG" << std::endl;
	std::cout << "*-*" << std::endl;
}

void	manageCmd(std::string input, Server &s, int fd){
	std::string firstWord;

	firstWord = input.substr(0, input.find("\n"));
	firstWord = input.substr(0, input.find("\r"));
	firstWord = input.substr(0, input.find(" "));
	if (firstWord == "NICK")
		nick(s, fd, input.substr(5, 200));
	else if (firstWord == "USER")
		user(s, fd, input.substr(5, 200));
	else if (firstWord == "PING")
		pong(fd);
}

int msg(int fd, Server &s)
{
	unsigned long dsize = 0;
	int rc;

	rc =ioctl(fd, FIONREAD, &dsize);
	if (rc == ERROR)
	{
		perror("\e[31mioctl failed \e[0m ");
		return (-1);
	}
	char* buffer = (char*)malloc(sizeof(char) * dsize);
	if (recv(fd, buffer, dsize, 0) == ERROR)
	{
		perror("\e[31mconnection issue\e[0m ");
		return FAIL;
	}
	std::string input = std::string(buffer, dsize);
	std::cout << "Received from fd " << fd << ": " << input; //Display msg
	manageCmd(input, s, fd);
	// for (int i = 1; i < s.nfds; i++){
	// 	if (s.fds[i].fd == fd)
	// 		continue ;
	// 	send(s.fds[i].fd, buffer, dsize, 0);
	// }
	free(buffer);
	return SUCCESS;
}