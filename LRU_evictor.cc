#include "LRU_evictor.hh"
using namespace std;

LRUEvictor::LRUEvictor()
{
    list<key_type> LRU_vec;
    unordered_map<key_type, list<key_type>::iterator> time_table;
}

LRUEvictor::~LRUEvictor()
{

}

void LRUEvictor::touch_key(const key_type& key)
{
    // key does exist in hash table
    if (time_table.find(key) != time_table.end()){
        LRU_vec.erase(time_table[key]);
    }
    LRU_vec.push_front(key);
    time_table[key] = LRU_vec.begin();
}

const key_type LRUEvictor::evict()
{
  // return "" if nothing can be evicted. Assume that caller never has "" as a key. 
  if (time_table.bucket_count() == 0)
  {
    return "";
  }
  auto last = LRU_vec.back();
  LRU_vec.pop_back();
  time_table.erase(last);

  return last;
}
