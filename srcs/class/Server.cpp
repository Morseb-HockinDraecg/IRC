#include "Server.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Server::Server(Socket &s, std::string pwd) : sock(s), password(pwd), nfds(1) {
	d.name = "server";
	d.version = "0.042";
	d.dateCreat = "13/07/2021";
	d.userMode = "none";
	d.chanMode = "none";
	memset(fds, 0, sizeof(fds));
	fds[0].fd = s.getSockFd();
	fds[0].events = POLLIN;
}
Server::~Server() {
	for (int i = 0; i < nfds; i++){
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
	while (!this->clientList.empty()){
		std::map<int, Client*>::iterator it = clientList.begin();
		delete it->second;
		clientList.erase(it);
	}
}

//	---	---	---	Operators --- --- ---

std::ostream & operator<<(std::ostream & o, Server const &rhs){
	rhs.displayClients();
	o << std::endl;
	return o;
}


//	---	---	---	Functions --- --- ---
void	Server::addClient(int fd, Client * c){
	clientList.insert(std::pair<int, Client*>(fd, c));
}
void	Server::delClient(std::string username){
	std::map<int, Client*>::iterator it;
	std::cout << "Client List on the server:\n";
	for (it = clientList.begin(); it != clientList.end(); ++it)
		if (it->second->getUsername() == username){
			delete it->second;
			clientList.erase(it);
			std::cout << "Client erase with success.";
		}
}
void	Server::displayClients() const{
	std::map<int, Client*>::const_iterator it;
	std::cout << "Client List on the server:\n";
	for (it = clientList.begin(); it != clientList.end(); ++it)
		std::cout << it->first << "=>" << it->second << std::endl;
}
//	---	---	---	Setters --- --- ---

// --- --- --- Getters --- --- ---
t_data		Server::getData() const{
	return d;
}
Client *	Server::getClients(int fd) const{
	std::map<int, Client*>::const_iterator it;
	for (it = clientList.begin(); it != clientList.end(); ++it)
		if (it->first == fd)
			return it->second;
	return NULL;
}
Socket const &		Server::getSocket() const{
	return sock;
}
std::string const &		Server::getPwd() const{
	return password;
}
