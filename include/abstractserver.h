#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <vector>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "connectionhandler.h"
#include "types.h"

class CAbstractServer 
{
public:
  void Connect ();
  SServerProperties& GetServerData ();
  ~CAbstractServer ();
  bool IsReady();
protected:
  CAbstractServer (short port, short maxpending);
  SServerProperties mServProp;
  CConnectionHandler mHandler;
};

#endif // ABSTRACTSERVER_H
