#include "../PacketSender/PacketSender.hpp"
#include "../PacketReceiver/PacketReceiver.hpp"
#include "PacketThread.hpp"
#include <list>
#include <thread>
class PacketThreadGroup {
public:
    PacketThreadGroup(const std::list<std::shared_ptr<PacketTargetInfo>> &portsReceiving, const std::list<std::shared_ptr<PacketTargetInfo>> &portsSending);
    virtual ~PacketThreadGroup();
private:
    std::list<std::unique_ptr<PacketReceiver>> activePacketReceiving;
    std::list<std::unique_ptr<PacketSender>> activePacketSenders;
    std::list<std::unique_ptr<PacketThread>> activeThreadsReceiving;
    std::list<std::unique_ptr<PacketThread>> activeThreadsSending;
};