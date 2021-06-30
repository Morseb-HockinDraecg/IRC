#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

#include <vector>


//	Name COMMAND parameter_list
/*
           1. Pass message
           2. Nick message
           3. User message
*/

typedef	struct s_connectionRegistration{
	std::string					name;
	std::string					cmd;
	std::vector<std::string>	paramList;
}	t_connectionRegistration;

class Server{

	t_connectionRegistration	coReg;

public:
	Server();
	~Server();
	Server (Server const &);
	Server & operator=(Server const &);

	void	setName(std::string v);
	void	setCmd(std::string v);
	void	setParamList(std::vector<std::string> v);

	std::string					getName() const;
	std::string					getCmd() const;
	std::vector<std::string>	getParamList()const;
};

#endif