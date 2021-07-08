#include "irc.hpp"

// static void	addClient(Client *c, Socket const &b, Server &s, pollfd fds[200], int nfds);
static void closeFd_RearrangePoll(int &nfds, pollfd fds[200], int i); // close fd client left + re sort the fd list
// static void clearPoll(int nfds, pollfd fds[200]); // close all fd of poll before quit

static void	addClient(Socket const &b, Server &s, pollfd fds[200], int &nfds){
	int new_sd = -1;
	Client *c;
	
	do{
		try{
			c = connectingClient(b);
			new_sd = c->getClientSocket();
			if (new_sd < 0)
				continue;
			s.addClient(c);
			std::cout << "\e[36mnew client !\n\e[0m";
			std::cout << "  New incoming connection - " << new_sd << std::endl;
			fds[nfds].fd = new_sd;
			fds[nfds].events = POLLIN;
			nfds++;
		}catch (const MyException &e){
			std::cout << e.what();
			new_sd = ERROR;
		}
	}while (new_sd != ERROR);
}


void pollLoop(Socket &b)
{
	// (void)c;
	// int new_sd = -1;
	int rc;
	int end_server = FALSE;
	int current_size = 0, i;
	// int nfds = 1, current_size = 0, i;
	// struct pollfd fds[200];
	Server s(b);

	// memset(fds, 0, sizeof(fds));
	// fds[0].fd = b.getSockFd();
	// fds[0].events = POLLIN;


	while (end_server == FALSE){
		rc = poll(s.fds, s.nfds, -1);
		if (rc < 0){
			perror("poll function failed ");
			break;
		}
		current_size = s.nfds;
		for (i = 0; i < current_size; i++){
			if (s.fds[i].revents == 0)
				continue;
			if (s.fds[i].fd == b.getSockFd()){
				addClient(b, s, s.fds, s.nfds);
				// do{
				// 	try{
				// 		c = connectingClient(b);
				// 		s.addClient(c);
				// 		new_sd = c->getClientSocket();
				// 		if (new_sd < 0)
				// 			continue;
				// 		std::cout << "\e[36mnew client !\n\e[0m";
				// 		std::cout << "  New incoming connection - " << new_sd << std::endl;
				// 		fds[nfds].fd = new_sd;
				// 		fds[nfds].events = POLLIN;
				// 		nfds++;
				// 	}catch (const MyException &e){
				// 		std::cout << e.what();
				// 		new_sd = ERROR;
				// 	}
				// }
				// while (new_sd != ERROR);
			}else{
				if (s.fds[i].revents & POLLHUP || s.fds[i].revents & POLLERR || s.fds[i].revents & POLLNVAL){
					std::cout << "\e[33mThe client was disconnected\n\e[0m";
					closeFd_RearrangePoll(s.nfds, s.fds, i);
				}else if (s.fds[i].revents & POLLIN){
					msg(s.fds[i].fd);
				}
			}
		}
	}
	// clearPoll(nfds, fds);
}

//	
//	--- --- statics functions --- ---
//

static void closeFd_RearrangePoll(int &nfds, pollfd fds[200], int i)
{
	int j;

	close(fds[i].fd);
	fds[i].fd = -1;
	for (i = 0; i < nfds; i++){
		if (fds[i].fd == -1){
			for (j = i; j < nfds; j++){
				fds[j].fd = fds[j + 1].fd;
			}
			i--;
			nfds--;
		}
	}
}

// static void clearPoll(int nfds, pollfd fds[200])
// {
// 	for (int i = 0; i < nfds; i++){
// 		if (fds[i].fd >= 0)
// 			close(fds[i].fd);
// 	}
// }