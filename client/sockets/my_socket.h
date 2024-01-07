#ifndef SOCKETS_CLIENT_MY_SOCKET_H
#define SOCKETS_CLIENT_MY_SOCKET_H

#include <string>

class MySocket {
public:
    static MySocket* createConnection(std::string hostName, short port);

    ~MySocket();
    void sendData(const std::string& data);
    void sendEndMessage();
    unsigned long long connectSocket;
protected:
    MySocket(unsigned long long socket);
private:
    static const char * endMessage;
};

#endif //SOCKETS_CLIENT_MY_SOCKET_H
