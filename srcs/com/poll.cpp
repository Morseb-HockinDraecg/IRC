#include "irc.hpp"

// static void	addClient(Client *c, Socket const &b, Server &s, pollfd fds[200], int nfds);
static void closeFd_RearrangePoll(int &nfds, pollfd fds[200], int i); // close fd client left + re sort the fd list
static void clearPoll(int nfds, pollfd fds[200]); // close all fd of poll before quit

// static void	addClient(Client *c, Socket const &b, Server &s, pollfd fds[200], int nfds){
// 	int new_sd = -1;

// 	do{
// 		try{
// 			c = connectingClient(b);
// 			s.addClient(c);
// 			new_sd = c->getClientSocket();
// 			if (new_sd < 0)
// 				continue;
// 			std::cout << "\e[36mnew client !\n\e[0m";
// 			std::cout << "  New incoming connection - " << new_sd << std::endl;
// 			fds[nfds].fd = new_sd;
// 			fds[nfds].events = POLLIN;
// 			nfds++;
// 		}catch (const MyException &e){
// 			std::cout << e.what();
// 			new_sd = ERROR;
// 		}
// 	}while (new_sd != ERROR);
// }


void pollLoop(Socket &b, Client *c)
{
	// (void)c;
	int new_sd = -1;
	int rc;
	int end_server = FALSE;
	int nfds = 1, current_size = 0, i;
	struct pollfd fds[200];
	Server s;

	memset(fds, 0, sizeof(fds));
	fds[0].fd = b.getSockFd();
	fds[0].events = POLLIN;


	while (end_server == FALSE){
		rc = poll(fds, nfds, -1);
		if (rc < 0){
			perror("poll function failed ");
			break;
		}
		current_size = nfds;
		for (i = 0; i < current_size; i++){
			if (fds[i].revents == 0)
				continue;
			if (fds[i].fd == b.getSockFd()){
				// addClient(c, b, s, fds, nfds);
				do{
					try{
						c = connectingClient(b);
						s.addClient(c);
						new_sd = c->getClientSocket();
						if (new_sd < 0)
							continue;
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
			}else{
				if (fds[i].revents & POLLHUP || fds[i].revents & POLLERR || fds[i].revents & POLLNVAL){
					std::cout << "\e[33mThe client was disconnected\n\e[0m";
					closeFd_RearrangePoll(nfds, fds, i);
				}else if (fds[i].revents & POLLIN){
					msg(fds[i].fd);
				}
			}
		}
	}
	clearPoll(nfds, fds);
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

static void clearPoll(int nfds, pollfd fds[200])
{
	for (int i = 0; i < nfds; i++){
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}