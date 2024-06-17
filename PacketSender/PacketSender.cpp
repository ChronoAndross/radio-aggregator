#include "PacketSender.hpp"
#include "../Utils/StringCreator.hpp"
#include "../PacketException/PacketException.hpp"

// Shamelessly adapted from https://www.beej.us/guide/bgnet/html/#client-server-background

PacketSender::PacketSender(PacketTargetInfo* packetTargetInfo)
{
    struct addrinfo addrCriteria, *p;
    int yes=1;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_INET;
    addrCriteria.ai_socktype = SOCK_DGRAM;
    auto addrStr = StringCreator::uitos(packetTargetInfo->getAddress());
    auto portStr = StringCreator::itos(packetTargetInfo->getPort());
    int addrInfoSuccess = getaddrinfo(addrStr.c_str(), portStr.c_str(), &addrCriteria, &servinfo);
    if (addrInfoSuccess != 0) {
        throw PacketException(StringCreator::stringFormat("PacketSender() getaddrinfo: %s\n", gai_strerror(addrInfoSuccess)));
    }
    this->serverSocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (!isServerSocketActive()) {
        throw PacketException("PacketSender failed to initalize the socket correctly");
    }
}

void PacketSender::sendMessage(const std::string message) {
    if (isServerSocketActive()) {
        int numBytes = sendto(this->serverSocket, message.c_str(), message.size(), 0, servinfo->ai_addr, servinfo->ai_addrlen);
        std::cout << "sent bytes=" << numBytes << std::endl;
    } else {
        std::cout << "server socket not active, skip sending and discard message" << std::endl;
    }
}

bool PacketSender::isServerSocketActive() {
    return this->serverSocket != -1;
}

PacketSender::~PacketSender()
{
    if (isServerSocketActive()) {
        freeaddrinfo(servinfo);
        close(this->serverSocket);
    }
}