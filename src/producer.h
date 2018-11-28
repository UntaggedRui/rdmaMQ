#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "mbuf.h"

namespace rmq {

/**
 * Producer creates MessageBuffers and push their content to
 * the broker. A producer pick which idx and length of the
 * buffer to push. Connection setup is done after each buffer
 * is created.
 * 
 * For simplicity, each producer only creates one buffer instead
 * of multiple with different types.
 * 
 * In the aspect of tranport, producer is a sender rather than
 * receiver. User will pass in the ip of the receiver (in this
 * case the broker) to set up RDMA connection.
 */

template <typename T>
class Producer {
private:
    MessageBuffer<int> mbuf;        // assume type int for now
    std::unique_ptr<Transport> transport;
    std::string broker_ip;          // Do we really need this?
    
    
    


public:
    Producer() {}
    Producer(char *broker_ip) : broker_ip(broker_ip) {
        transport = std::make_unique<Transport>();
    }
    ~Producer() {}


}





}


#endif // PRODUCER_H_