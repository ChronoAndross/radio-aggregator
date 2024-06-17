#include "PacketQueue.hpp"

static std::deque<std::string> packetQueue;
static std::mutex packetQueueMutex;

void PacketQueue::packetPush(const std::string& packetMsg) {
    std::lock_guard<std::mutex> packetQueueLock(packetQueueMutex);
    std::cout << "pushing packetMsg=" + packetMsg << std::endl;
    packetQueue.push_back(packetMsg);
}

const std::string& PacketQueue::packetPop() {
    std::lock_guard<std::mutex> packetQueueLock(packetQueueMutex);
    auto& packetMsg = packetQueue.front();
    std::cout << "popping packetMsg=" + packetMsg << std::endl;
    packetQueue.pop_front();
    return packetMsg;
}

size_t PacketQueue::packetQueueSize() {
    return packetQueue.size();
}