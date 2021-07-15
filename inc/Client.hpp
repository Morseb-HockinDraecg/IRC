#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <netinet/in.h> // struct sockaddr_in
#include <unistd.h>		//close

class Client{

	int			clientSocket;	//ret of accept
    sockaddr_in	addrClient;		//needed for accept
	socklen_t	addrClientSize;	//neede for accept

	bool		pass;			// 0 need the correct password ; 1 ok, can register
	bool		sRegister;		// NICK USER cmd needed for the server
	std::string	nickname;
	std::string	username;
	std::string	host;
	std::string	idFormMsg;
	std::string	activChan;
	bool		userRight;		//0 classic user - 1 operator user

public:
	Client();
	Client(int clientSocket, sockaddr_in addrClient, socklen_t addrClientSize);
	~Client();
	Client (Client const &);
	Client & operator=(Client const &);

	//setters
	void	setClientSocket(int v);
	void	setAddrClient(sockaddr_in v);
	void	setAddrClientSize(socklen_t v);

	void	setPass(bool v);
	void	setRegister(bool v);
	void	setNickname(std::string v);
	void	setUsername(std::string v);
	void	setActivChan(std::string v);
	void	setUserRight(bool v);

	// getters
	int				getClientSocket() const;
	sockaddr_in		getAddrClient() const;
	socklen_t		getAddrClientSize() const;

	bool			getPass() const;
	bool			getRegister() const;
	std::string		getNickname() const;
	std::string		getUsername() const;
	std::string		getHost() const;
	std::string		getID() const;
	std::string		getActivChan() const;
	bool			getUserRight() const;
};

#endif