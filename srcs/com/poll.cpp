#include "irc.hpp"

void closeFd_RearrangePoll(int &nfds, pollfd fds[200], int i)
{
	int j;

	close(fds[i].fd);
	fds[i].fd = -1;
	for (i = 0; i < nfds; i++)
	{
		if (fds[i].fd == -1)
		{
			for (j = i; j < nfds; j++)
			{
				fds[j].fd = fds[j + 1].fd;
			}
			i--;
			nfds--;
		}
	}
}

void clearPoll(int nfds, pollfd fds[200])
{
	for (int i = 0; i < nfds; i++)
	{
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}