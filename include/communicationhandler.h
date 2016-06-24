#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H

#include "types.h"

class CCommunicationHandler
{
public:
  virtual void HandleCommunication() = 0;
protected:
  CCommunicationHandler(short socket) { mSocket = socket; }
  short mSocket;  
};

#endif
