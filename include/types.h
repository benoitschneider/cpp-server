#ifndef TYPES_H
#define TYPES_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "exceptions.h"
   
// TODO : state pattern ?
enum EServiceStatus
{
  ServiceUp,
  ServiceDown
};

// needed to connect to a server : @ & port
typedef struct
{
  struct sockaddr_in server_addr;
  short port;
} SServerConnection;

// TODO : merge SServerConnection ?
// structure used by a server to keep its data
typedef struct
{
  struct sockaddr_in server_addr;
  short port;
  short socket;
  short maxpending;
  bool ready;
} SServerProperties;

// structure used by a server to keep its clients data
typedef struct
{
  struct sockaddr_in client_addr;
  short socket;
} SClientProperties;

#endif // TYPES_H
