#include "../include/abstractserver.h"

CAbstractServer::CAbstractServer (short port, short maxpending) 
{
  mServProp.port = port;
  mServProp.maxpending = maxpending;
  mServProp.ready = false;

  try
  {
    Connect();
  }
  catch(Exceptions::ServerException& e)
  {
    std::cout << "Specific server exception occured, abort." << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "Unknown exception occured, abort." << std::endl;
    std::cout << e.what() << std::endl;
  }
}

CAbstractServer::~CAbstractServer () 
{
  if (mServProp.socket > 0) 
  {
    close(mServProp.socket);
  }
}

void CAbstractServer::Connect () 
{
  if ( (!mServProp.ready) && (mServProp.port > 0) && (mServProp.maxpending > 0) ) 
  {
    if ((mServProp.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    {
      throw Exceptions::SocketCreationFailed();
    }

    memset(&mServProp.server_addr,0 ,sizeof(mServProp.server_addr));
    mServProp.server_addr.sin_family = AF_INET;
    mServProp.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    mServProp.server_addr.sin_port = htons(mServProp.port);

    if (bind( mServProp.socket, 
             (const sockaddr *) &mServProp.server_addr,
              sizeof(mServProp.server_addr)) < 0 ) 
    {
      throw Exceptions::PortNotFree();
    }

    if (listen(mServProp.socket, mServProp.maxpending) < 0)
    {
      throw Exceptions::ListenFailed();
    }

    mServProp.ready = true;
    mHandler.SetServerProperties(&mServProp);
    mHandler.StartConnectionHandling();
  } 
  else 
  {
    // debugging
    std::cout << mServProp.port << "|" << mServProp.maxpending << "|" << mServProp.ready << std::endl;
  }
}

SServerProperties& CAbstractServer::GetServerData () 
{
  return mServProp;
}

bool CAbstractServer::IsReady () 
{
  return mServProp.ready;
}

