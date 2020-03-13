

#include "cache.hh"
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Cache::Impl
{

  public:
    Cache::size_type _maxmem;
    Evictor* _evictor;
    Cache::size_type _currbytes;
    std::unordered_map<key_type,std::string, Cache::hash_func> _umap;
    vector<char*> _char_vec;

    // Pass in the hash function into the unordered map.
    Impl(Cache::hash_func hasher)
    : _umap(0, hasher)
    {};
};

Cache::Cache (Cache::size_type maxmem, float max_load_factor , Evictor* evictor, Cache::hash_func hasher)
      : pimpl_(new Impl(hasher == nullptr ? hash<key_type>() : hasher)) // if hasher is nullptr, pass default std::hash
      {
        // maximum memory capacity in bytes for values in cache
        pimpl_->_maxmem = maxmem;

        // eviction policy
        pimpl_->_evictor = evictor;

        // current number of bytes used by values in cache
        pimpl_->_currbytes = 0;

        // vector that keeps track of allocated character arrays to destruct later
        pimpl_->_char_vec = vector<char*>();

        // load factor
        pimpl_->_umap.max_load_factor(max_load_factor);
      }

Cache::~Cache()
{
  // deallocate returned character arrays
  for (auto p : pimpl_->_char_vec)
  {
    delete[] p;
  }
  pimpl_->_char_vec.clear();

  // destroy evictor as well.
  // pimpl_->_evictor->Evictor::~Evictor();
}

// Just for debugging purposes.
template<typename K, typename V>
void print_map(std::unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}


void Cache::set(key_type key, Cache::val_type val, Cache::size_type size)
  {

    //If the given size exceeds maxmem, then we can't put it in the maxmem no matter what
    if (size>pimpl_->_maxmem)
    {
      return;
    }


    if ((pimpl_->_currbytes + size) > pimpl_->_maxmem)
    {
      // default strategy : just return
      if (pimpl_->_evictor == nullptr)
      {
        return;
      }

      // eviction poliy:
      // Keep evicting until there is enough space to add new key-val pair.
      while (((pimpl_->_currbytes + size) > pimpl_->_maxmem ))
      {
        auto delete_key = pimpl_->_evictor->evict();
        del(delete_key);
      }

    }

    // Deep copying the key, then adding it to the umap.
    key_type deepkey;
    deepkey = key;

    auto deepvalue = std::string(val);

    //Deleting ensures that when we overwrite we don't double count the size of the value.
    // If key is not in the cache then this fails silently.
    del(deepkey);

    pimpl_->_umap[deepkey] = deepvalue;
    pimpl_->_currbytes += size;

    if (pimpl_->_evictor != nullptr)
    {
      pimpl_->_evictor->touch_key(deepkey);
    }


    // The lines below are to make sure our hash functions were working correctly, because we couldn't test them with asserts.
    // This is because our umap is a private data member, so we can't access it in the test file. See test_cache_lib.cc and the Readme for more info.

    // cout << "key: " << deepkey << "\n" <<"bucket key is in: " << pimpl_->_umap.bucket(deepkey) << "\n" << "no. of buckets in umap: " << pimpl_->_umap.bucket_count() << endl;
    // cout << endl;

  }





bool Cache::del(key_type key)
{
  // check if key is in umap.
  if ((pimpl_->_umap).find(key) == (pimpl_->_umap).end())
  {
        return false;
  }
  else // if found, erase the key and update current bytes
  {
    pimpl_->_currbytes -= pimpl_->_umap[key].length();
    pimpl_->_umap.erase(key);
    return true;
  }
}

Cache::val_type Cache::get(key_type key, Cache::size_type& val_size) const
  {
    // Checks if the key is in the umap
    if (pimpl_->_umap.find(key) == pimpl_->_umap.end())
    {
          return nullptr;
    }

    std::string str1 = pimpl_->_umap[key];
    auto len = str1.length();

    // update val_size from caller
    val_size = len;

    // Initialize a character array on the heap that holds the contents of the value associated with key, then return it to the caller.
    char *char_array = new char[len + 1];

    // Push it to the char_vec to destruct later.
    pimpl_->_char_vec.push_back(char_array);

    std::strcpy(char_array, str1.c_str());

    if (pimpl_->_evictor != nullptr)
    {
      pimpl_->_evictor->touch_key(key);
    }

    return char_array;
  }


Cache::size_type Cache::space_used() const
{
  // pimpl_->_currbytes already holds the number of current bytes in use.
  return pimpl_->_currbytes;
}


void Cache::reset()
{
  // reset the unordered map and the current number of bytes.
  pimpl_->_umap.clear();
  pimpl_->_currbytes = 0;
}
