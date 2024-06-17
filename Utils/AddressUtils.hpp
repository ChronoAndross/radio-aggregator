#include <netinet/in.h>
class AddressUtils {
public:
    // get sockaddr, IPv4 only:
    static void* getInAddress(struct sockaddr *sa) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
};