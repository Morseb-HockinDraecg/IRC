#include "irc.hpp"
#include <sys/ioctl.h>

static int	checkRegister(int fd, int msg, Server &s);
static void	init_arr_funct(void (*arr[8])(Server &s, int fd, std::string str)); // init array for messages
static void	manageMsg(std::string input, Server &s, int fd);

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
	manageMsg(input, s, fd);
	// for (int i = 1; i < s.nfds; i++){
	// 	if (s.fds[i].fd == fd)
	// 		continue ;
	// 	send(s.fds[i].fd, buffer, dsize, 0);
	// }
	free(buffer);
	return SUCCESS;
}


//	
//	--- --- statics functions --- ---
//

static void	manageMsg(std::string input, Server &s, int fd){
	void		(*arr[8])(Server &s, int fd, std::string str);
	std::string	firstWord;
	const int	msgsNb = 7;
	int			msg;
	std::string msgs[msgsNb] = {"PASS", "NICK", "USER", "JOIN", "NAMES", "LIST", "PRIVMSG"};

	input = input.substr(0, input.find("\n")).substr(0, input.find("\r"));
	firstWord = input.substr(0, input.find(" "));
	init_arr_funct(arr);
	for(msg = 0; msg < msgsNb; msg++){
		if (msgs[msg] == firstWord)
			break ;
	}
	if ( checkRegister(fd, msg, s) && msg != msgsNb)
		arr[msg](s, fd, input.substr(msgs[msg].length(), 201));
}

static void	init_arr_funct(void (*arr[8])(Server &s, int fd, std::string str)){
	arr[E_PASS] = pass;
	arr[E_NICK] = nick;
	arr[E_USER] = user;
	arr[E_JOIN] = join;
	arr[E_NAMES] = names;
	arr[E_LIST] = list;
	arr[E_PRIVMSG] = privmsg;
	
}

static int	checkRegister(int fd, int msg, Server &s){
	if (msg == E_PASS || msg == E_NICK || msg == E_USER)
		return 1;
	if (!s.getClients(fd)->getRegister()){
		send(fd, ERR_NOTREGISTERED, sizeof(ERR_NOTREGISTERED), 0);
		return 0;
	}
	return 1;
}
