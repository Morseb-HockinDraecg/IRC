#include "irc.hpp"

int main(int ac, char **av)
{
	Socket b;

	if (!init(ac, av, b))
		return (FAIL);
	pollLoop(b, av[2]);
	close(b.getSockFd());
}

/*		--- TO DO ---

[ok]	Communication between client and server must be done via TCP/IP(v4) or (v6)
[ok]	handling multi client
[ok]	Error handling
[ok]	nc (Use ctrl+d to send parts of the command)
[]	work with an IRC client ---  weechat
[ok]	authenticate
[]		pass message
[ok]	set a nickname
[ok]	username
[ok]	send and receive private messages
[]	join a channel
[]	all messages from one client on a channel are sent to all other clients of the channel.
[]	You must have operators and regular users.
[]	Some operator’s specific actions/commands.

*/