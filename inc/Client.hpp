#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

class Client{

	int			id;
	std::string	nickname;
	std::string	username;

public:
	Client();
	~Client();
	Client (Client const &);
	Client & operator=(Client const &);

	void	setId(int v);
	void	setNickname(std::string v);
	void	setUsername(std::string v);

	int				getId() const;
	std::string		getNickname() const;
	std::string		getUsername() const;
};

#endif