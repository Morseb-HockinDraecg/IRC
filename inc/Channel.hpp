#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>

class Channel{

	std::string				name;
	std::string				password;
	unsigned int			currentUsers;
	const unsigned int	maxNbUsers;

	Channel(); // need a name at least
public:
	Channel(std::string name);
	Channel(std::string name, unsigned int maxNbUser);
	~Channel();
	Channel (Channel const &);
	Channel & operator=(Channel const &);

	void	setName(std::string v);
	void	setPassword(std::string v);
	void	setCurrentUsers(unsigned int v);

	std::string				getName() const;
	std::string				getPassword() const;
	unsigned int			getCurrentUsers() const;
};

#endif