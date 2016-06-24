#include "connectionhandler.h" 
#include <string.h>

#define BUFFER_SIZE 256

void CConnectionHandler::HandleConnection(SClientProperties clientProp)
{
  char ipAddress[INET_ADDRSTRLEN];

  std::cout << "Handling connection: " << inet_ntop(AF_INET, &(clientProp.client_addr.sin_addr), ipAddress, INET_ADDRSTRLEN) << " on socket " << clientProp.socket << std::endl;

  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  auto n = read(clientProp.socket, buffer, BUFFER_SIZE - 1);
  if (n < 0)
  {
    std::cout << "Read failed (TODO: exception)" << std::endl;
    throw std::exception();  
  } 

  std::cout << "Client " << inet_ntop(AF_INET, &(clientProp.client_addr.sin_addr), ipAddress, INET_ADDRSTRLEN) << " said " << std::string(buffer) << " on socket " << clientProp.socket << std::endl;

  std::cout << "End of connection: " << inet_ntop(AF_INET, &(clientProp.client_addr.sin_addr), ipAddress, INET_ADDRSTRLEN) << " close socket " << clientProp.socket << std::endl;

  close(clientProp.socket);
}

void CConnectionHandler::StartConnectionHandling()
{
  if ( (mChild = fork()) == 0)
  {
    std::vector<std::thread> threads;
  
    SClientProperties clientProp;
    auto clientLength = sizeof(clientProp);
    
    while (mServerProp->ready)
    {
      if ((clientProp.socket = accept(mServerProp->socket, (struct sockaddr*)&clientProp.client_addr, &clientLength)) < 0)
      {
        std::cout << "Accept failed" << std::endl;
        throw std::exception();
      }
 
      threads.push_back( std::thread(&CConnectionHandler::HandleConnection, this, clientProp) );
    }

    std::cout << "Server not ready, abort (TODO : specific exception)" << std::endl; 
    std::cout << "Wait for all threads and throw" << std::endl;

    for (std::thread& th : threads)
     th.join();

    throw std::exception();
  }
  else
  {
    std::cout << "CConnectionHandler::StartConnectionHandler: process waiting for son to finish." << std::endl;
    int returnStatus;
    waitpid(mChild, &returnStatus, 0);

    if (returnStatus == 1)
      std::cout << "Child terminated with an error." << std::endl;
  }
}

void CConnectionHandler::SetServerProperties(SServerProperties* serverProp)
{
  mServerProp = serverProp;
}
