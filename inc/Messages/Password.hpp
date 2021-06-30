#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "AMessage.hpp"

class Password: public AMessage{


public:
	Password() : AMessage("", "PASS", std::vector<std::string>()) {}

	virtual	void	command() const;

};

#endif