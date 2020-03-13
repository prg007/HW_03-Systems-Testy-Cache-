#pragma once
#include "evictor.hh"
#include <queue>
using namespace std;

class FifoEvictor : public Evictor
{
  private:
    // We use std::queue as our FIFO data structure to keep track of the keys that have been touched.
    queue<key_type> key_q;
  public:
    FifoEvictor();
    ~FifoEvictor();

    // touches a key, which we enqueue to the key_q
    void touch_key(const key_type& key);

    // evicts a key by dequeuing from the key_q. Returns that key to the caller to be evicted.
    const key_type evict();
};
