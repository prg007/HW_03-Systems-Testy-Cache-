#pragma once
#include "evictor.hh"
#include <unordered_map>
#include <list>
using namespace std;

class LRUEvictor : public Evictor
{
  private:
    //LRU vec is a list where the most recently used is at the front of the list, and the least recently used is at the back.
    list<key_type> LRU_vec;

    // time table maps keys to their iterators in the LRU_vec list, which makes erasures from the list constant time. 
    unordered_map<key_type, list<key_type>::iterator> time_table;


  public:
    LRUEvictor();
    ~LRUEvictor();

    // touches a key, which we enqueue to the key_q
    void touch_key(const key_type& key);

    // evicts a key by dequeuing from the key_q. Returns that key to the caller to be evicted.
    const key_type evict();
};
