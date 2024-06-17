#include "PacketThreadGroup.hpp"

PacketThreadGroup::PacketThreadGroup(const std::list<std::shared_ptr<PacketTargetInfo>> &portsReceiving, const std::list<std::shared_ptr<PacketTargetInfo>> &portsSending) {
    for (auto portReceiving : portsReceiving) {
        activePacketReceiving.push_back(std::make_unique<PacketReceiver>(portReceiving.get()));
        activeThreadsReceiving.push_back(std::make_unique<PacketThread>(activePacketReceiving.back().get()));
    }

    for (auto portSending : portsSending) {
        activePacketSenders.push_back(std::make_unique<PacketSender>(portSending.get()));
        activeThreadsSending.push_back(std::make_unique<PacketThread>(activePacketSenders.back().get()));
    }
}

PacketThreadGroup::~PacketThreadGroup() {
    for (auto& threadReceive : activeThreadsReceiving) {
        threadReceive.get()->stopThread();
    }

    for (auto& threadSend : activeThreadsSending) {
        threadSend.get()->stopThread();
    }

}