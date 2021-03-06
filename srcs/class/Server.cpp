#include "Server.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Server::Server(Socket &s, std::string pwd) : sock(s), password(pwd), nfds(1) {
	d.name = "IRCserver";
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
	while (!this->channelList.empty()){
		std::map<Channel *, std::list<Client*>* >::iterator it = channelList.begin();
		delete it->first;
		delete it->second;
		channelList.erase(it);
	}
}

//	---	---	---	Operators --- --- ---

std::ostream & operator<<(std::ostream & o, Server const &rhs){
	rhs.displayClients();
	o << std::endl;
	return o;
}

//	---	---	---	Functions --- --- ---

void	Server::addChannel(Channel * chan){
	std::list<Client *> *lst = new std::list<Client *>;
	std::map<Channel *, std::list<Client*>* >::iterator it;

	for (it = channelList.begin(); it != channelList.end(); ++it){
		if (it->first->getName() == chan->getName())
			return ;
	}
	channelList.insert(std::pair<Channel *, std::list<Client*>* >(chan, lst));
}
void	Server::addChannelUser(std::string chan, Client *c){
	std::map<Channel *, std::list<Client*>* >::iterator it;

	if (channelList.begin()->second->empty())
		c->promot(chan);
	for (it = channelList.begin(); it != channelList.end(); ++it){
		if (it->first->getName() == chan)
			it->second->push_back(c);
	}
}
void	Server::rmChannelUser(std::string chan, Client *c){
	std::map<Channel *, std::list<Client*>* >::iterator it;

	if (c == NULL)
		return ;
	for (it = channelList.begin(); it != channelList.end(); ++it){
		if (it->first->getName() == chan){
			it->second->remove(c);
			if (it->second->empty()){
				delete it->first;
				delete it->second;
				channelList.erase(it);
				break;
			}
		}
	}
}
void	Server::listChannel(int fd){
	std::map<Channel *, std::list<Client*>* >::iterator it;

	for (it = channelList.begin(); it != channelList.end(); ++it){
		send(fd, it->first->getName().c_str(), it->first->getName().length(), 0);
		send(fd, "\n", 1, 0);
	}
}
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
bool	Server::clientOnChan(std::string client, std::string chan){
	std::map<Channel *, std::list<Client*>* >::iterator itC;
	std::list<Client *>::iterator itL;
	
	if (client.empty() || chan.empty())
		return false;
	for (itC = channelList.begin(); itC != channelList.end(); ++itC){
		if (itC->first->getName() == chan){
			for(itL = itC->second->begin();itL != itC->second->end();++itL)
				if ((*itL)->getUsername() == client)
					return true;
		}
	}
	return false;
}


//	---	---	---	Setters --- --- ---


// --- --- --- Getters --- --- ---

std::list<Client *>*	Server::getNames(std::string chanName)const {
	std::map<Channel *, std::list<Client*>* >::const_iterator it;

	for (it = channelList.begin(); it != channelList.end(); ++it){
		if (it->first->getName() == chanName){
			return it->second;
		}
	}
	return NULL;
}
std::map<Channel *, std::list<Client*>* > Server::getChanList() const{
	return channelList;
}

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

Client *	Server::getClients(std::string nickname) const{
	std::map<int, Client*>::const_iterator it;

	for (it = clientList.begin(); it != clientList.end(); ++it)
		if (it->second->getNickname() == nickname)
			return it->second;
	return NULL;
}

Client	*	Server::getClientsUser(std::string user) const{
	std::map<int, Client*>::const_iterator it;

	for (it = clientList.begin(); it != clientList.end(); ++it)
		if (it->second->getUsername() == user)
			return it->second;
	return NULL;
}

Socket const &		Server::getSocket() const{
	return sock;
}
std::string const &		Server::getPwd() const{
	return password;
}
