#include <iostream>
#include <memory>
#include <csignal> 
#include <thread>
#include "PacketThread/PacketThreadGroup.hpp"

void signal_handler(int signal_num) 
{ 
    std::cout << "The interrupt signal is (" << signal_num 
         << "). \n"; 
  
    // It terminates the  program 
    exit(signal_num); 
} 

int main() {
    // register signal SIGABRT and signal handler 
    //signal(SIGABRT, signal_handler); 
    { // packet thread group allocation in scope
        std::unique_ptr<PacketThreadGroup> ptg = std::make_unique<PacketThreadGroup>(std::list<std::shared_ptr<PacketTargetInfo>>{std::make_shared<PacketTargetInfo>(4000), std::make_shared<PacketTargetInfo>(4001), std::make_shared<PacketTargetInfo>(4002)}, std::list<std::shared_ptr<PacketTargetInfo>>{std::make_shared<PacketTargetInfo>(5000)});
        while (1) {
            std::cout << "wait for 3 seconds on main thread" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    return 0;
}