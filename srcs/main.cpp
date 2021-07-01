#include "irc.hpp"
#define FALSE 0
#define TRUE 1

void pollT(Socket &b, Client *c)
{
	(void)c;
	int rc;
	int listen_sd = -1, new_sd = -1;
	int end_server = FALSE;
	// int close_conn;
	int timeout;
	int nfds = 1, current_size = 0, i;
	struct pollfd fds[200];
	Server s;

	listen_sd = b.getSockFd();
	memset(fds, 0, sizeof(fds));
	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;
	timeout = (5 * 60 * 1000);
	while (end_server == FALSE)
	{
		// rc = poll(fds, nfds, timeout);
		rc = poll(fds, nfds, -1);
		if (rc < 0)
		{
			perror("poll function failed ");
			break;
		}
		current_size = nfds;
		for (i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].fd == listen_sd)
			{
				do
				{
					// new_sd = accept(listen_sd, NULL, NULL);
					// if (new_sd < 0)
					// {
					// 	if (errno != EWOULDBLOCK)
					// 	{
					// 		perror("  accept() failed");
					// 		end_server = TRUE;
					// 	}
					// 	break;
					// }

					try
					{
						c = connectingClient(b);
						s.addClient(c);
						new_sd = c->getClientSocket();
						printf("  New incoming connection - %d\n", new_sd);
						fds[nfds].fd = new_sd;
						fds[nfds].events = POLLIN;
						nfds++;
						std::cout << nfds << std::endl;
					}
					catch (const MyException &e)
					{
						std::cout << e.what();
						break;
					}
					catch (const std::exception &e)
					{
						;
					}

				} while (new_sd != ERROR);
			}
			else
			{
				if (fds[i].revents & POLLHUP || fds[i].revents & POLLERR || fds[i].revents & POLLNVAL)
				{
					std::cout << "\e[33mThe client was disconnected\n\e[0m";
					closeFd_RearrangePoll(nfds, fds, i);
				}
				else if (fds[i].revents & POLLIN)
				{
					msg(fds[i].fd);
				}
			}
		}
	}
	clearPoll(nfds, fds);
}

int main(int ac, char **av)
{
	Socket b;
	Client *c = NULL;
	Server s;

	if (!init(ac, av, b))
		return (FAIL);

	// for(;;) {

	pollT(b, c);
	// try {
	// 	c = connectingClient(b);
	// } catch (const MyException &e) {
	// 	std::cout << e.what();
	// 	break;
	// }

	// s.addClient(c);
	// std::cout << "clients list : "<<  c << std::endl;
	// char	host[NI_MAXHOST];
	// char	serv[NI_MAXSERV];

	// memset(host, 0, NI_MAXHOST);
	// memset(serv, 0, NI_MAXSERV);
	// msg();

	// }
	close(b.getSockFd());
}

/*		--- TO DO ---

[ok]	Communication between client and server must be done via TCP/IP(v4) or (v6)
[]	Format exec : ./ircserv [host:port_network:password_network] <port> <password>
[]	handling multi client
[]	Error handling
[]	nc (Use ctrl+d to send parts of the command)
[]	work with an IRC client ---  weechat
[]	authenticate
[]	set a nickname
[]	username
[]	join a channel
[]	send and receive private messages
[]	all messages from one client on a channel are sent to all other clients of the channel.
[]	You must have operators and regular users.
[]	Some operator’s specific actions/commands.

*/