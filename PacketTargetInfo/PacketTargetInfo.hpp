#include <netinet/in.h> 
#include <netdb.h>
#ifndef PACKET_TARGET_INFO
#define PACKET_TARGET_INFO
struct PacketTargetInfo {
public:
    PacketTargetInfo(int port, in_addr_t address = INADDR_ANY) : port(port), address(address) {}
    in_addr_t getAddress() { return address; }
    int getPort() { return port; }
private:
    in_addr_t address;
    int port;
};
#endif