#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

namespace Exceptions
{
  class ServerException : public std::exception 
  {
    public: 
      virtual const char* what() const throw()
      {
        return mMsg.c_str();
      }

      virtual ~ServerException() throw()
      {}
    protected:
      ServerException(const char* msg): mMsg(msg) {}
    private:
      std::string mMsg;
  };

  class PortNotFree : public ServerException 
  {
    public :
      PortNotFree(): ServerException("Exceptions::PortNotFree: port not available") {}
  };
  
  class SocketCreationFailed : public ServerException
  {
    public:
      SocketCreationFailed(): ServerException("Exceptions::SocketCreationFailed") {}
  };

  class ListenFailed : public ServerException
  {
    public:
      ListenFailed(): ServerException("Exceptions::ListenFailed") {}
  };
}
#endif
