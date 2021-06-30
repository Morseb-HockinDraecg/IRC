#include "irc.hpp"

static void 	test(){
	AMessage *t = new Password();
	Password	p;

	t->command();
	p.command();
}




int main (int ac, char **av){
	Base b;


test();
return 1;
	if (!init(ac, av, b))
		return (FAIL);

	for(;;) {
		try {
			connectingClient(b);
		} catch (const MyException &e) {
			std::cout << e.what();
			break;
		}
	}
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