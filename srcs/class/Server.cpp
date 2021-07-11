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
void	Server::addClient(Client * c){
	int size = clientList.size();
	for (int i = 0; i < size + 1 ; i++){
		if (clientList.count(i) == 0){
			clientList.insert(std::pair<int, Client*>(i, c));
			break;
		}
	}
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
// std::list<Client *>	Server::getClients() const{
// 	return clients;
// }
Socket const &		Server::getSocket() const{
	return sock;
}


