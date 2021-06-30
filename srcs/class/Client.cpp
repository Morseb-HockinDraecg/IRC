#include "Client.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Client::Client() {}
Client::~Client() {}
Client::Client (Client const &rhs){
	*this = rhs;
}


//	---	---	---	Operator --- --- ---

Client & Client::operator=(Client const &rhs){
	id = rhs.getId();
	nickname = rhs.getNickname();
	username = rhs.getUsername();
	return *this;
}
//	---	---	---	Setters --- --- ---

void	Client::setId(int v){
	id = v;
}
void	Client::setNickname(std::string v){
	nickname = v;
}
void	Client::setUsername(std::string v){
	username = v;
}

// --- --- --- Getters --- --- ---

int				Client::getId() const{
	return id;
}
std::string		Client::getNickname() const{
	return nickname;
}
std::string		Client::getUsername() const{
	return username;
}

