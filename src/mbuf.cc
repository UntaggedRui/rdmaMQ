#include "mbuf.h"
#include <unistd.h>

namespace rmq {

template <typename T>
void MessageBuffer<T>::init() {
    //addr = memalign(sysconf(_SC_PAGESIZE), total_size);
    addr = malloc(total_size);
    mr = ibv_reg_mr(pd, addr, total_size,
            IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_REMOTE_READ);
    assert_exit(mr, "Failed to register MR.");
    LOG_DEBUG("Managed to register MR for mbuf.\n");
}

// explicit instantiations
template class MessageBuffer<char>;
template class MessageBuffer<int>;
template class MessageBuffer<std::string>;

}