#include "base.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
Base::Base() {}
Base::~Base() {}

//	---	---	---	Setters --- --- ---
void	Base::setAddr(struct sockaddr_in v){
	addr = v;
}
void	Base::setSockFd(int v){
	sockFd = v;
}

// --- --- --- Getters --- --- ---

struct sockaddr_in Base::getAddr(){
	return addr;
}
int Base::getSockFd(){
	return sockFd;
}
