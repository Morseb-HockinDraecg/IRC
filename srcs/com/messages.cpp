#include "irc.hpp"

static int	trimFirstSpace(int fd, std::string &s);

// ignore cmd
void	ign(Server &s, int z, std::string n) {(void)s; (void)z; (void)n;}

// Connection registration

void	pass(Server &s, int fd, std::string pwd){

	if (trimFirstSpace(fd, pwd))
		return;
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

	if (trimFirstSpace(fd, nick))
		return;
	cl = s.getClients(fd);
	if (cl)
		cl->setNickname(nick.substr(0, nick.find("\n")));
}
void	user(Server &s, int fd, std::string user){
	Client *cl;

	if (trimFirstSpace(fd, user))
		return;
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
		welcomeMsg(fd, s, *cl);
		if (!cl->getRegister()){
			cl->setRegister(true);
		}
	}
}

// Channel operations

static void	sendMsgChan(std::string const &input, Server &s, int fd){
	std::list<Client *> *cl = s.getNames(s.getClients(fd)->getActivChan());
	std::list<Client *>::iterator it;

	if (!cl)
		return ;
	for (it = cl->begin(); it != cl->end(); it++){
		if ((*it)->getClientSocket() == fd)
			continue ;
		send((*it)->getClientSocket(), input.c_str(), input.length(), 0);
		send((*it)->getClientSocket(), "\n", 1, 0);
	}
}

void	join(Server &s, int fd, std::string channel){
	std::string	msg;

	if (trimFirstSpace(fd, channel))
		return;
	s.addChannel(new Channel(channel));
	s.addChannelUser(channel, s.getClients(fd));
	msg = ":";
	msg += s.getClients(fd)->getID();
	msg += " JOIN ";
	msg += channel;
	msg += "\n";
	sendMsgChan(msg, s, fd);
	send(fd, msg.c_str(), msg.length(), 0);
	msg = "331    RPL_NOTOPIC ";
	msg += channel;
	msg += " :No topic is set\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	msg = " ";
	msg += channel;
	names(s, fd, msg);

}
void	names(Server &s, int fd, std::string channel){
	std::list<Client *> *names;
	std::list<Client *>::iterator it;
	std::string	msg;

	if (trimFirstSpace(fd, channel))
		return;
	names = s.getNames(channel);
	if (!names){
		send(fd, ERR_NOSUCHSERVER, sizeof(ERR_NOSUCHSERVER), 0);
		return;
	}
	for (it = names->begin(); it != names->end(); it++){
		msg = ":";
		msg += s.getClients(fd)->getID();
		msg = "353    RPL_NAMREPLY (\"=\")";
		msg += channel;
		msg += " : ";
		msg += (*it)->getNickname();
		msg += "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	msg = ":";
	msg += s.getClients(fd)->getID();
	msg = "366    RPL_ENDOFNAMES ";
	msg += channel;
	msg += " :End of /NAMES list\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}
void	list(Server &s, int fd, std::string channel){
	s.listChannel(fd);
	(void)channel;
}

//Sending messages

void	privmsg(Server &s, int fd, std::string targetAndText){
	std::string	target;
	std::string	textToSend;
	std::string	msg;
	Client		*c;
	std::list<Client *> *cl;


	if (trimFirstSpace(fd, targetAndText))
		return;
	try{
		target = targetAndText.substr(0, targetAndText.find(" "));
		textToSend = targetAndText.substr(target.length() + 1);
	} catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
	c = s.getClients(target);
	cl = s.getNames(target);
	if (c || cl){
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
		if (c)
			send(c->getClientSocket(), msg.c_str(), msg.length(), 0);
		else
			sendMsgChan(msg, s, fd);
	}else{
		send(fd, ERR_NORECIPIENT, sizeof(ERR_NORECIPIENT), 0);
		return ;		
	}
}
void	kick(Server &s, int fd, std::string kick){
	//kick a <client> since a <channel> by a this->superuser
	//format => KICK <channel> <client> [<comment>]

	//if this->user is superuser
		//eject a client (target) from the channel
		//send <comment> to <client> 
	//endif
	(void)s; (void)fd; (void)kick;
}
// void	pong(int fd){
// 	send(fd, "PONG 127.0.0.1", strlen("PONG 127.0.0.1"), 0);
// 	std::cout << "*-*" << std::endl;
// 	std::cout << "PONG" << std::endl;
// 	std::cout << "*-*" << std::endl;
// }
static int	trimFirstSpace(int fd, std::string &s){
	try {
		s = s.substr(1);
	} catch(std::exception const &e ) {
		send(fd, ERR_NEEDMOREPARAMS, sizeof(ERR_NEEDMOREPARAMS), 0);
		return 1;
	}
	if (s.empty()){
		send(fd, ERR_NEEDMOREPARAMS, sizeof(ERR_NEEDMOREPARAMS), 0);
		return 1;
	}
	return 0;
}