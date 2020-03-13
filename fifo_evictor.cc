

#include "fifo_evictor.hh"
#include <iostream>
using namespace std;

FifoEvictor::FifoEvictor()
{
  queue<key_type> key_q;
}

FifoEvictor::~FifoEvictor()
{

}

void FifoEvictor::touch_key(const key_type& key)
{
   key_q.push(key);
}

const key_type FifoEvictor::evict()
{
  // return "" if nothing can be evicted. Assume that caller never has "" as a key. 
  if (key_q.empty())
  {
    return "";
  }
  auto return_head =  key_q.front();
  key_q.pop();
  return return_head;
}
