#include "irc.hpp"

void	showMessage(){
	std::cout << "Message than can be send : "<< std::endl;
	std::cout << "PASS <password>"<< std::endl;
	std::cout << "NICK <nickname>"<< std::endl;
	std::cout << "USER <username>"<< std::endl;
	std::cout << ""<< std::endl;
	std::cout << "/JOIN #<chanName>"<< std::endl;
	std::cout << "PRIVMSG <dest> <msg>"<< std::endl;
}