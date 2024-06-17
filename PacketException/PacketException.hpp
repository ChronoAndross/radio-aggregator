#include <memory>
#include <cstring>
#include <iostream>
#include <unistd.h>
class PacketException : std::exception
{
private:
    std::string exceptionMsg;
public:
    PacketException(const std::string& exceptionMsg);
};