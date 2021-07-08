#include "Server.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Server::Server(Socket &s) : sock(s), nfds(1) {
	memset(fds, 0, sizeof(fds));
	fds[0].fd = s.getSockFd();
	fds[0].events = POLLIN;
}
Server::~Server() {
	for (int i = 0; i < nfds; i++){
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}

//	---	---	---	Operators --- --- ---

std::ostream & operator<<(std::ostream & o, Server const &rhs){
	std::list<Client *> clients = rhs.getClients();
	std::list<Client *>::iterator it;
	std::list<Client *>::iterator ite = clients.end();
	for (it = clients.begin(); it != ite; it++){
		o << (*it)->getUsername() << std::endl;
	}
	return o;
}


//	---	---	---	Functions --- --- ---
void	Server::addClient(Client * c){
	std::list<Client *>::iterator it;
	std::list<Client *>::iterator ite = clients.end();

	for (it = clients.begin(); it != ite; it++){
		if ((*it)->getUsername() ==	c->getUsername()){
			return ;
		}
	}
	clients.push_front(c);
}
void	Server::delClient(std::string username){
	std::list<Client *>::iterator it;
	std::list<Client *>::iterator ite = clients.end();

	for (it = clients.begin(); it != ite; it++){
		if ((*it)->getUsername() == username){
			delete *it;
			clients.erase(it);
			return ;
		}
	}
}

//	---	---	---	Setters --- --- ---

// --- --- --- Getters --- --- ---
std::list<Client *>	Server::getClients() const{
	return clients;
}
Socket const &		Server::getSocket() const{
	return sock;
}


