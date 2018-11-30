#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "mbuf.h"
#include "transport.h"

namespace rmq {

/**
 * Consumers create MessageBuffers and read topic they subscribed 
 * from the broker. Consumers first read the available offset from
 * the broker before issue a read. It can decide when and how often
 * to fetch the offset, and currently there is no guarantee the data
 * get overwritten by Producers before Consuers read them since we
 * pick space retention mechanism instead of time retention mechanism
 * used by Kafka.
 * 
 * Like Producers, each Consumer creates one data buffer and one
 * control buffer. The control buffer is for storing the offset.
 * 
 * In the aspect of tranport, a Consumer is a sender rather than
 * a receiver. Users will pass in the ip of the receiver (in this
 * case the broker) to set up RDMA connection.
 * 
 * Users need to manually call init_tranport() after constructing Consumer.
 * 
 * Currently we assume each Consumer only subscribe to one topic,
 * and thus there is no need to do the subscription process. (/huaji)
 * 
 * Usage:
 *      First call Consumer custom constructor,
 *      which constructs data_buf and ctrl_buf.
 *      Then call Consumer::init_transport() to complete the setup.
 */

template <typename T>
class Consumer {
private:
    std::unique_ptr<MessageBuffer<T>> data_buf;             // assume one buffer for now
    std::unique_ptr<MessageBuffer<uint64_t>> ctrl_buf;      // store write_addr
    std::unique_ptr<Transport> transport;
    std::string broker_ip;

    //size_t fetch_and_add_write_idx(size_t start_idx, size_t num_msg);

public:
    Consumer() {}
    Consumer(size_t data_buf_cap, std::string broker_ip)
    : broker_ip(std::string(broker_ip)) {
        transport = std::make_unique<Transport>();
        data_buf = std::make_unique<MessageBuffer<T>>(data_buf_cap, transport->get_pd());
        ctrl_buf = std::make_unique<MessageBuffer<uint64_t>>(1, transport->get_pd(), 1);
    }
    ~Consumer() {}

    // gets called after constructing mbuf
    void init_transport(int gid_idx) {
        transport->init(broker_ip.c_str(), data_buf->get_mr(), ctrl_buf->get_mr(), gid_idx);
    }

    // start_idx: indicates the starting address of the data in the buffer pushed to the broker
    // num_msg: # of data blocks to send in a batch
    // e.g., push(0, 2) pushes the first 2 elements in the buffer to the broker
    // returns num_msg actually written
    //size_t push(size_t start_idx, size_t num_msg);

};





}


#endif // PRODUCER_H_