#include "../PacketReceiver/PacketReceiver.hpp"
#include "../PacketSender/PacketSender.hpp"
#include "PacketThread.hpp"
#include "../PacketException/PacketException.hpp"
#include <functional>

void PacketThread::loopReceiver() {
    while (!this->exitThread) {
        std::cout << "receiver on thread id=" << packetThread.get_id() << ", polling message" << std::endl;
        if (this->receiver) {
            auto msg = this->receiver->pollMessage();
            if (!msg.empty()) {
                std::cout << msg << std::endl;
                PacketQueue::packetPush(msg);
            } else {
                std::cout << "empty message, continuing for thread id=" << packetThread.get_id() << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}

void PacketThread::loopSender() {
    while (!this->exitThread) {
        std::cout << "sender on thread id=" << packetThread.get_id() << ", check packet queue for new messages" << std::endl;
        if (PacketQueue::packetQueueSize() >= 1) {
            auto& msg = PacketQueue::packetPop();
            this->sender->sendMessage(msg);
        } else {
            std::cout << "no messages in queue, continuing for thread id=" << packetThread.get_id() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

PacketThread::PacketThread(PacketSender* sender) {
    if (sender) {
        this->packetThread = std::thread([&]() {this->loopSender();});
        this->sender = sender;
    } else {
        throw PacketException("invalid sender passed into PacketThread");
    }
}

PacketThread::PacketThread(PacketReceiver* receiver) {
    if (receiver) {
        this->packetThread = std::thread([&]() {this->loopReceiver();});
        this->receiver = receiver;
    } else {
        throw PacketException("invalid receiver passed into PacketThread");
    }
}

void PacketThread::stopThread() {
    if (this->sender != nullptr || this->receiver != nullptr) {
        std::cout << "exiting thread for id=" << packetThread.get_id();
        this->exitThread = true;
        this->packetThread.join();
    } else {
        std::cout << "cant stop because thread not initialized" << std::endl;
    }
}

PacketThread::~PacketThread() {
    stopThread();
}