#ifndef NICKNAME_HPP
#define NICKNAME_HPP

#include "AMessage.hpp"

class Nickname : public AMessage{


public:
	Nickname() : AMessage("", "NICK", std::vector<std::string>()) {}

	virtual	void	command() const;

};

#endif