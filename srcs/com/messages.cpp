#include "irc.hpp"

// Connection registration

void	pass(Server &s, int fd, std::string pwd){
	if (s.getClients(fd)->getPass()){
		send(fd, ERR_ALREADYREGISTRED, sizeof(ERR_ALREADYREGISTRED), 0);
		return ;
	}
	if (s.getPwd() == pwd){
		send(fd, "SUCCESS", strlen("SUCCESS"), 0);
		s.getClients(fd)->setPass(1);
	}
	else
		send(fd, ERR_PASSWDMISMATCH, sizeof(ERR_PASSWDMISMATCH), 0);
}

void	nick(Server &s, int fd, std::string nick){
	Client *cl;

	cl = s.getClients(fd);
	if (cl)
		cl->setNickname(nick.substr(0, nick.find("\n")));
}

void	user(Server &s, int fd, std::string user){
	Client *cl;

	cl = s.getClients(fd);

	if (cl){
		// if (cl->getRegister()){
		// 	send(fd, ERR_ALREADYREGISTRED, sizeof(ERR_ALREADYREGISTRED), 0);
		// 	return ;
		// }
		if (cl->getNickname().empty()){
			send(fd, ERR_NONICKNAMEGIVEN, sizeof(ERR_NONICKNAMEGIVEN), 0);
			return;
		}
		cl->setUsername(user.substr(0, user.find("\n")));
		if (!cl->getRegister()){
			welcomeMsg(fd, s, *cl);
			cl->setRegister(true);
		}
	}
}

//Sending messages

void	privmsg(Server &s, int fd, std::string targetAndText){
	std::string	target;
	std::string	textToSend;
	std::string	msg;
	Client		*c;

	try{
		target = targetAndText.substr(0, targetAndText.find(" "));
		textToSend = targetAndText.substr(target.length() + 1);
	} catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
	c = s.getClients(target);
	if (c){
		if (textToSend.empty()){
			send(fd, ERR_NOTEXTTOSEND, sizeof(ERR_NOTEXTTOSEND), 0);
			return ;
		}
		std::string nick = s.getClients(fd)->getNickname();
		msg = ":";
		msg += s.getClients(fd)->getID();
		msg += " PRIVMSG ";
		msg += nick;
		msg += " :";
		msg += textToSend;
		msg += "\n";
		send(c->getClientSocket(), msg.c_str(), msg.length(), 0);
	}else{
		send(fd, ERR_NORECIPIENT, sizeof(ERR_NORECIPIENT), 0);
		return ;		
	}
}




// void	pong(int fd){
// 	send(fd, "PONG 127.0.0.1", strlen("PONG 127.0.0.1"), 0);
// 	std::cout << "*-*" << std::endl;
// 	std::cout << "PONG" << std::endl;
// 	std::cout << "*-*" << std::endl;
// }