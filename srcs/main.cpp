#include "irc.hpp"


int main(int ac, char **av)
{
	Socket b;
	Client *c = NULL;
	Server s;

	if (!init(ac, av, b))
		return (FAIL);

	pollLoop(b, c);
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