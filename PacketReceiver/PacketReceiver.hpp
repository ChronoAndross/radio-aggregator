#include "../PacketTargetInfo/PacketTargetInfo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>

class PacketReceiver {
public:
    PacketReceiver(PacketTargetInfo* packetTargetInfo);
    std::string pollMessage();
    virtual ~PacketReceiver();
protected:
    int socketFileDesc = -1;
private:
    bool isSocketOpen();
};