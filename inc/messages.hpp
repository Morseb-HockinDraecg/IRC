#pragma once

// include needed for header
class Server;
#include <string>

enum e_messages{
	E_PASS,
	E_NICK,
	E_USER,
	E_PRIVMSG,
};

// Connection registration
void	pass(Server &s, int fd, std::string pwd);
void	nick(Server &s, int fd, std::string nick);
void	user(Server &s, int fd, std::string user);
	// Server message
	// Operator message
	// Quit message
	// Server Quit message

// Channel operations
	//Join message
	//Part message
	//Mode message
	//   Channel modes
	//   User modes
	// Topic messag
	// Names message
	// List message
	// Invite message
	// Kick message

//Server queries and command
	//Version message
	//Stats message
	//Links message
	//Time message
	//Connect message
	//Trace message
	//Admin message
	//Info messag

//Sending messages
	//Private messages
void	privmsg(Server &s, int fd, std::string targetAndText);
	//Notice messages

//User-based queries
	//Who query
	//Whois query
	//Whowas message

//Miscellaneous messages
	//Kill message
	//Ping message
	//Pong message
	//Error message