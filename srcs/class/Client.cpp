#include "Client.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Client::Client() : userRight(0){}
Client::~Client(){
	close(clientSocket);
}
Client::Client(int clientsocket, sockaddr_in addrclient, socklen_t addrclientsize)
: clientSocket(clientsocket), addrClient(addrclient), addrClientSize(addrclientsize){
}

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

void	Client::setClientSocket(int v){
	clientSocket = v;
}
void	Client::setId(int v){
	id = v;
}
void	Client::setNickname(std::string v){
	nickname = v;
}
void	Client::setUsername(std::string v){
	username = v;
}
void	Client::setAddrClient(sockaddr_in v){
	addrClient = v;
}
void	Client::setAddrClientSize(socklen_t v){
	addrClientSize = v;
}
void	Client::setUserRight(bool v){
	userRight = v;
}

// --- --- --- Getters --- --- ---

int				Client::getClientSocket() const{
	return clientSocket;
}
int				Client::getId() const{
	return id;
}
std::string		Client::getNickname() const{
	return nickname;
}
std::string		Client::getUsername() const{
	return username;
}
sockaddr_in		Client::getAddrClient() const{
	return addrClient;
}
socklen_t		Client::getAddrClientSize() const{
	return addrClientSize;
}
bool			Client::getUserRight() const{
	return userRight;
}
