#ifndef SERVER_H
#define SERVER_H

#include <abstractserver.h>

class CServer : public CAbstractServer
{
public:
  CServer (short port, short maxpending) : CAbstractServer (port, maxpending) {}
};

#endif
