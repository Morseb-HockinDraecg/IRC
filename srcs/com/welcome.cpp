#include "irc.hpp"


void	welcomeMsg(int fd, Server &s, Client &c){
	t_data dS;

	dS = s.getData();

	// 001    RPL_WELCOME
    //       "Welcome to the Internet Relay Network
    //        <nick>!<user>@<host>"
	c.getNickname();
    c.getUsername();
	c.getHost();
	// \r\n
	send(fd, "001    RPL_WELCOME", strlen("001    RPL_WELCOME"), 0);
	send(fd, "Welcome to the Internet Relay Network", strlen("Welcome to the Internet Relay Network"), 0);
	send(fd, c.getNickname().c_str(), c.getNickname().length(), 0);
	send(fd, "!", 1, 0);
	send(fd, c.getUsername().c_str(), c.getUsername().length(), 0);
	send(fd, "@", 1, 0);
	send(fd, c.getHost().c_str(), c.getHost().length(), 0);
	send(fd, "\r\n", 2, 0);




	// 002    RPL_YOURHOST
    //        "Your host is <servername>, running version <ver>"
	// dS.name;
	// dS.version;
    // // 003    RPL_CREATED
    // //        "This server was created <date>"
	// dS.dateCreat;
    // // 004    RPL_MYINFO
    // //        "<servername> <version> <available user modes>
    // //         <available channel modes>"
	// dS.name;
	// dS.version;
	// dS.userMode;
	// dS.chanMode;
}