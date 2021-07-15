#include "irc.hpp"

static int	trimFirstSpace(int fd, std::string &s);

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
		if (!cl->getRegister()){
			welcomeMsg(fd, s, *cl);
			cl->setRegister(true);
		}
	}
}

// Channel operations
void	join(Server &s, int fd, std::string channel){
	if (trimFirstSpace(fd, channel))
		return;
	s.addChannel(new Channel(channel));
	s.addChannelUser(channel, s.getClients(fd));
	channel += " :topic\n";
	send(fd, "332    RPL_TOPIC ", strlen("332    RPL_TOPIC "), 0);
	send(fd, channel.c_str(), channel.length(), 0);
	send(fd, "\r\n", 2, 0);

}
void	names(Server &s, int fd, std::string channel){
	std::list<Client *> *names;
	std::list<Client *>::iterator it;

	if (trimFirstSpace(fd, channel))
		return;
	names = s.getNames(channel);
	if (!names){
		send(fd, ERR_NOSUCHSERVER, sizeof(ERR_NOSUCHSERVER), 0);
		return;
	}
	send(fd, "353    RPL_NAMREPLY ", strlen("353    RPL_NAMREPLY "), 0);
	send(fd, channel.c_str(), channel.length(), 0);
	send(fd, "\r\n", 2, 0);


	for (it = names->begin(); it != names->end(); it++){
		send(fd, (*it)->getNickname().c_str(), (*it)->getNickname().length(), 0);
		send(fd, "\n", 1, 0);
	}
	channel += ":End of NAMES list\n";
	send(fd, "366    RPL_ENDOFNAMES ", strlen("366    RPL_ENDOFNAMES "), 0);
	send(fd, channel.c_str(), channel.length(), 0);
	send(fd, "\r\n", 2, 0);


    //    353    RPL_NAMREPLY
    //           "( "=" / "*" / "@" ) <channel>
    //            :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )



	(void)s;
	(void)fd;
	(void)channel;
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

	if (trimFirstSpace(fd, targetAndText))
		return;
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