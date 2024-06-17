#include <cstring> 
#include "../PacketTargetInfo/PacketTargetInfo.hpp"
#include <iostream> 
#include <sys/socket.h> 
#include <unistd.h> 

class PacketSender
{
public:
    PacketSender(PacketTargetInfo* packetTargetInfo);
    void sendMessage(const std::string message);
    ~PacketSender();

protected:
    int serverSocket = -1;
    struct addrinfo *servinfo = nullptr;
private:
    bool isServerSocketActive();
};