#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <deque>
#include <mutex>
class PacketQueue {
public:
    static void packetPush(const std::string& packetMsg);
    static const std::string& packetPop();
    static size_t packetQueueSize();
};