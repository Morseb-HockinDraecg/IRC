#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

#include<list>

class	AMessage;
class	Channel;

//	Name COMMAND parameter_list
/*
           1. Pass message
           2. Nick message
           3. User message
*/


class Server{

	AMessage			*coReg;
	std::list<Channel>	chan;

public:
	Server();
	~Server();
	Server (Server const &);
	Server & operator=(Server const &);


};

#endif