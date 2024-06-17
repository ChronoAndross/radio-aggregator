#include "../PacketQueue/PacketQueue.hpp"

#include <thread>
class PacketThread {
public:
    PacketThread(PacketSender* sender);
    PacketThread(PacketReceiver* receiver);
    void stopThread();
    virtual ~PacketThread();
protected:
    void loopReceiver();
    void loopSender();
private:
    PacketSender* sender = nullptr;
    PacketReceiver* receiver = nullptr;
    bool exitThread = false;
    std::thread packetThread;
};