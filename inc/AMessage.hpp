#ifndef AMESSAGE_HPP
#define AMESSAGE_HPP

#include <iostream>
#include <string>

#include <vector> 

class AMessage{

protected:
	std::string					name;
	std::string					cmd;
	std::vector<std::string>	paramList;

public:
	AMessage();
	AMessage(std::string n, std::string c, std::vector<std::string> p);
	virtual ~AMessage();
	AMessage (AMessage const &);
	AMessage & operator=(AMessage const &);

	virtual	void	command() const = 0;

	void	setName(std::string v);
	void	setParamList(std::vector<std::string> v);

	std::string					getName() const;
	std::string					getCmd() const;
	std::vector<std::string>	getParamList()const;
};

#endif