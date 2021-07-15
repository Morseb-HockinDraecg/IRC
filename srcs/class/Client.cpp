#include "Client.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Client::Client() : pass(0), sRegister(false), host ("127.0.0.1"),userRight(false){}
Client::~Client(){
	close(clientSocket);
}
Client::Client(int clientsocket, sockaddr_in addrclient, socklen_t addrclientsize)
: clientSocket(clientsocket), addrClient(addrclient), addrClientSize(addrclientsize), pass(0), sRegister(false), host ("127.0.0.1"),userRight(false){
}
Client::Client (Client const &rhs){
	*this = rhs;
}

//	---	---	---	Operator --- --- ---

Client & Client::operator=(Client const &rhs){
	nickname = rhs.getNickname();
	username = rhs.getUsername();
	return *this;
}
//	---	---	---	Setters --- --- ---

void	Client::setClientSocket(int v){
	clientSocket = v;
}
void	Client::setAddrClient(sockaddr_in v){
	addrClient = v;
}
void	Client::setAddrClientSize(socklen_t v){
	addrClientSize = v;
}

void	Client::setPass(bool v){
	pass = v;
}
void	Client::setRegister(bool v){
	sRegister = v;
}
void	Client::setNickname(std::string v){
	nickname = v;
}
void	Client::setUsername(std::string v){
	username = v;
}
void	Client::setActivChan(std::string v){
	activChan = v;
}
void	Client::setUserRight(bool v){
	userRight = v;
}

// --- --- --- Getters --- --- ---

int				Client::getClientSocket() const{
	return clientSocket;
}
sockaddr_in		Client::getAddrClient() const{
	return addrClient;
}
socklen_t		Client::getAddrClientSize() const{
	return addrClientSize;
}

bool			Client::getPass() const{
	return pass;
}
bool			Client::getRegister() const{
	return sRegister;
}
std::string		Client::getNickname() const{
	return nickname;
}
std::string		Client::getUsername() const{
	return username;
}
std::string		Client::getHost() const{
	return host;
}
std::string		Client::getID() const{
	std::string id;
	
	id = nickname;
	id += "!";
	id += username;
	id += "@";
	id += host;
	return id;
}
std::string		Client::getActivChan() const{
	return activChan;
}
bool			Client::getUserRight() const{
	return userRight;
}
