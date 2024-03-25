#include "../incs/WebServer.h"

bool run = 1;
const int kQueue = kqueue();

static void signal_handler(int i)
{
	if (i == SIGINT)
		run = 0;
}

static int findServerByFD(std::vector<Server *> servers, int ident)
{
	int i = 0;
	std::vector<Server *>::iterator it = servers.begin();
	for (; it != servers.end(); it++, i++)
		if ((**it).GetSocketfd() == ident)
			return i;
	return -1;
}

std::vector<Server *> initServers(std::map<std::string, std::vector<Configs> > portConfigs)
{
	std::map<std::string, std::vector<Configs> >::iterator it = portConfigs.begin();
	std::vector<Server *> servers;

	for (; it != portConfigs.end(); it++)
	{
		Server *s = new Server((*it).second[0].GetPort(), (*it).second[0].GetHost(), &((*it).second[0]));
		try
		{
			s->connect(kQueue);
		}
		catch (const SocketExcept &e)
		{
			std::cout << RED << e.what() << RESET << std::endl;
		}
		servers.push_back(s);
	}
	return servers;
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		std::cerr << RED << "Error: Wrong numbers of arguments" << RESET << std::endl;
		return 1;
	}
	ConfigFile cf(argc == 1 ? "default_config_file.conf" : argv[1]);
	signal(SIGINT, signal_handler);
	execAutoindex();

	std::vector<Server *> servers = initServers(cf.GetMapConfig());

	Clients clients;

	struct kevent evList[MAX_EVENTS];

	while (run)
	{
		std::string bufferStr;
		int num_events = kevent(kQueue, NULL, 0, evList, MAX_EVENTS, NULL);
		for (int i = 0; i < num_events; i++)
		{
			int index = findServerByFD(servers, evList[i].ident);
			if (index != -1)
			{
				ssize_t addrlen = sizeof(sockaddr);
				int connection = accept(evList[i].ident, (struct sockaddr *)(*servers[index]).GetSockAddr(), (socklen_t *)&addrlen);
				try
				{
					if (clients.AddConnection(connection, evList[i].ident))
					{
						ResponseHandler resHeader(NULL, std::make_pair("500", DEFAULT_ERROR_PATH));
						throw ServerException("500", resHeader.createResp(500), connection);
					}
					else
					{
						EV_SET((*servers[index]).GetEvSet(), connection, EVFILT_READ, EV_ADD, 0, 0, NULL);
						kevent(kQueue, (*servers[index]).GetEvSet(), 1, NULL, 0, NULL);
					}
				}
				catch (const ServerException &e)
				{
					e.what();
				}
			}
			else if (evList[i].filter == EVFILT_READ)
			{
				Configs config;
				char buffer[8192];
				index = findServerByFD(servers, clients.GetConnection(evList[i].ident)->evIdent);
				size_t totalBytesRead = 0;
				int bytesRead = 0;
				do
				{
					bytesRead = recv(evList[i].ident, buffer, 8192, 0);
					totalBytesRead += bytesRead;
					if (bytesRead > 0)
						bufferStr.append(buffer, bytesRead);
					usleep(100);
				} while (bytesRead > 0);
				RequestHandler reqHeader = RequestHandler(bufferStr, totalBytesRead + 1);
				try
				{
					config = cf.GetConfig((*servers[index]).GetHostPort(), reqHeader.GetHost());
					if (config.isEmpty())
						throw std::exception();
				}
				catch (const std::out_of_range &e)
				{
					continue;
				}
				catch (const std::exception &e)
				{
					std::cout << RED << "Error: no vaiable configuration" << RESET << std::endl;
					continue;
				}
				ResponseHandler resHeader = ResponseHandler(servers[index], &reqHeader, &config);
				std::string resp;
				try
				{
					if (reqHeader.GetMethod() == "POST" && reqHeader.GetBody().length() > config.GetLimitSizeBody())
					{
						resHeader = ResponseHandler(NULL, std::make_pair("413", config.GetErrorPath("413")));
						throw ServerException(resHeader.getError().first,
							resHeader.createResp(std::atoi(resHeader.getError().first.c_str())),
							evList[i].ident);
					}
					else
					{
						if (!config.GetRedirectionCode())
							resp.append(resHeader.createResp(200));
						else
						{
							resp.append(resHeader.createResp(config.GetRedirectionCode()));
							std::string redir("Location: ");
							redir.append(config.GetRedirectionUrl());
							redir.append("\r\n");
							resp.insert(resp.find('\n') + 1, redir);
						}
						if (!resHeader.getError().first.empty())
						{
							resHeader = ResponseHandler(NULL, resHeader.getError());
							throw ServerException(resHeader.getError().first,
								resHeader.createResp(std::atoi(resHeader.getError().first.c_str())),
								evList[i].ident);
						}
					}
				}
				catch (const ServerException &e)
				{
					resp = e.what();
				}
				std::string respChunck;
				int dataSent = 0;
				do
				{
					respChunck = resp.substr(0, 35000);
					dataSent = send(evList[i].ident, respChunck.c_str(), respChunck.size(), 0);
					if (dataSent < 0)
						break;
					resp = resp.substr(dataSent);
				} while (resp.size());
				bufferStr.clear();
				index = findServerByFD(servers, clients.GetConnection(evList[i].ident)->evIdent);
				EV_SET((*servers[index]).GetEvSet(), evList[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
				kevent(kQueue, (*servers[index]).GetEvSet(), 1, NULL, 0, NULL);
				clients.DelConnection(evList[i].ident);
				usleep(100);
			}
		}
	}

	std::cout << RED << "EXIT" << RESET << std::endl;
	close(kQueue);
	std::vector<Server *>::iterator i = servers.begin();
	for (; i != servers.end(); i++)
	{
		(*i)->disconnect();
		delete (*i);
	}
	return 0;
}
