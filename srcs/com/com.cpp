#include "irc.hpp"
#include <sys/ioctl.h>

// 4. Message details

int msg(int fd)
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
	std::cout << "Received: " << std::string(buffer, dsize) << std::endl; //Display msg
	send(fd, buffer, dsize, 0);
	free(buffer);
	return SUCCESS;
}