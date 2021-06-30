#include "server.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Server::Server() {}
Server::~Server() {}

//	---	---	---	Functions --- --- ---




//	---	---	---	Setters --- --- ---

void	Server::setName(std::string v){
	coReg.name = v;
}
void	Server::setCmd(std::string v){
	coReg.cmd = v;
}
void	Server::setParamList(std::vector<std::string> v){
	coReg.paramList = v;
}

// --- --- --- Getters --- --- ---

std::string					Server::getName() const{
	return coReg.name;
}
std::string					Server::getCmd() const{
	return coReg.cmd;
}
std::vector<std::string>	Server::getParamList()const{
	return coReg.paramList;
}
