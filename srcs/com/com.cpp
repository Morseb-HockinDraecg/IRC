#include "irc.hpp"
#include <sys/ioctl.h>

// 4. Message details

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
	std::cout << "Received from fd " << fd << ": " << std::string(buffer, dsize); //Display msg

	std::cout << s.nfds << " nfds\n";
	for (int i = 1; i < s.nfds; i++){
		if (s.fds[i].fd == fd)
			continue ;
		send(s.fds[i].fd, buffer, dsize, 0);
	}
	free(buffer);
	return SUCCESS;
}