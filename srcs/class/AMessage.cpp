#include "AMessage.hpp"

//	---	---	---	Construcor - Destructor --- --- ---
AMessage::AMessage() {}
AMessage::~AMessage() {}
AMessage::AMessage (AMessage const &rhs){
	*this = rhs;
}
AMessage::AMessage(std::string n, std::string c, std::vector<std::string> p) : name(n), cmd(c), paramList(p) {
}

//	---	---	---	Operator --- --- ---

AMessage & AMessage::operator=(AMessage const &rhs){
	name = rhs.getName();
	cmd = rhs.getCmd();
	paramList = rhs.getParamList();
	return *this;
}
//	---	---	---	Setters --- --- ---

void	AMessage::setName(std::string v){
	name = v;
}
void	AMessage::setParamList(std::vector<std::string> v){
	paramList = v;
}

// --- --- --- Getters --- --- ---

std::string					AMessage::getName() const{
	return name;
}
std::string					AMessage::getCmd() const{
	return cmd;
}
std::vector<std::string>	AMessage::getParamList()const{
	return paramList;
}
