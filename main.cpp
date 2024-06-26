#include <iostream>
#include <memory>
#include <csignal> 
#include <thread>
#include <atomic>
#include "PacketThread/PacketThreadGroup.hpp"

static std::atomic_bool gAbortAggregator;

void signal_handler(int signal_num) 
{ 
    std::cout << "The interrupt signal is (" << signal_num 
         << "). \n"; 
  
    // It terminates the  program 
    gAbortAggregator = true;
} 

int main() {
    gAbortAggregator = false;
    
    // register signal SIGINT and signal handler 
    signal(SIGINT, signal_handler); 

    { // packet thread group allocation in scope
        std::unique_ptr<PacketThreadGroup> ptg = std::make_unique<PacketThreadGroup>(std::list<std::shared_ptr<PacketTargetInfo>>{std::make_shared<PacketTargetInfo>(4000), std::make_shared<PacketTargetInfo>(4001), std::make_shared<PacketTargetInfo>(4002)}, std::list<std::shared_ptr<PacketTargetInfo>>{std::make_shared<PacketTargetInfo>(5000)});
        while (!gAbortAggregator) {
            std::cout << "wait for 3 seconds on main thread" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    std::cout << "shutting down aggregator" << std::endl;
    return 0;
}