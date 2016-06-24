#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H

#include "types.h"
#include <thread>
#include <chrono>
#include <vector>
#include <sys/wait.h> // waitpid 

class CConnectionHandler 
{
  public:
    void StartConnectionHandling ();    
    void HandleConnection (SClientProperties clientProp);
    void SetServerProperties(SServerProperties* serverProp);

  protected:
    SServerProperties* mServerProp;
    pid_t mChild;
};

#endif // COMMUNICATIONHANDLER_H
