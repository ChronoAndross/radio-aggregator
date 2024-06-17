#include "PacketReceiver.hpp"
#include "../Utils/StringCreator.hpp"
#include "../PacketException/PacketException.hpp"
#include "../Utils/AddressUtils.hpp"
#include <arpa/inet.h>

// Shamelessly adapted from https://www.beej.us/guide/bgnet/html/#client-server-background

#define MAXDATASIZE 100 // max number of bytes we can get at once 

PacketReceiver::PacketReceiver(PacketTargetInfo* packetTargetInfo) {
    struct addrinfo addrCriteria, *servinfo, *p;
    char s[INET_ADDRSTRLEN];
    int addrInfoSuccess;

    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_INET;
    addrCriteria.ai_socktype = SOCK_STREAM;
    auto addrStr = StringCreator::uitos(packetTargetInfo->getAddress());
    auto portStr = StringCreator::itos(packetTargetInfo->getPort());
    addrInfoSuccess = getaddrinfo(addrStr.c_str(), portStr.c_str(), &addrCriteria, &servinfo);
    if (addrInfoSuccess != 0) {
        throw PacketException(StringCreator::stringFormat("PacketReceiver() getaddrinfo: %s\n", gai_strerror(addrInfoSuccess)));
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((socketFileDesc = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(socketFileDesc, p->ai_addr, p->ai_addrlen) == -1) {
            close(socketFileDesc);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        throw PacketException("client: failed to connect");
    }

    inet_ntop(p->ai_family, AddressUtils::getInAddress((struct sockaddr *)p->ai_addr),s, sizeof(s));
    std::cout << "client: connection to " << s << std::endl;
    freeaddrinfo(servinfo); // all done with this structure
}

std::string PacketReceiver::pollMessage() {
    std::string outStr;
    if (isSocketOpen()) {
        int numBytes = -1;
        char readBuffer[MAXDATASIZE];
        if ((numBytes = recv(socketFileDesc, readBuffer, MAXDATASIZE-1, 0)) > -1) {
            readBuffer[numBytes] = '\0';
            outStr = std::string(readBuffer);
        }
    }

    return outStr;
}

bool PacketReceiver::isSocketOpen() {
    return socketFileDesc != -1;
}

PacketReceiver::~PacketReceiver() {
    if (isSocketOpen()) {
        std::cout << "client: closing socketFileDesc=" << socketFileDesc << std::endl;
        close(socketFileDesc);
        socketFileDesc = -1;
    }
}