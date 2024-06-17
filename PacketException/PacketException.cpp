#include "PacketException.hpp"

PacketException::PacketException(const std::string& exceptionMsg)
{
    this->exceptionMsg = exceptionMsg;
}