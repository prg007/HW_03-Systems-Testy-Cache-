#define CATCH_CONFIG_MAIN

#include "cache.hh"
#include "catch.hpp"
#include <iostream>
#include "fifo_evictor.hh"
#include <list>

using namespace std;

list<key_type> hash_list;
Cache::size_type cons(key_type key)
{
  // so compiler doesn't complain
  hash_list.push_back(key);

  return 1;
}


TEST_CASE("Cache Accepts Input / Checking Set method")

{
  SECTION("Check that the cache is initialized with zero memory use")
  {
    Cache cacheobj(30);
    REQUIRE(cacheobj.space_used() == 0);
  }
  SECTION("Cache doesn't accept input that exceeds maxmems")
  {
    Cache cacheobj(5);                                 //Maxmem over here is 5 bytes
    cacheobj.set("s","Stupid",6);
    REQUIRE(cacheobj.space_used() == 0);
  }
  SECTION("Accepts 1st input and make the value of 2nd input greater than maxmem ")
  {
    Cache cacheobj(5);
    cacheobj.set("s","Sun",3);
    cacheobj.set("m","Moon",4);
    REQUIRE(cacheobj.space_used() == 3);
  }
  SECTION("Cache accepts input with a given key-value and then resets key with a new value")
  {
    Cache cacheobj(13);
    cacheobj.set("s","sun",3);
    REQUIRE(cacheobj.space_used() == 3);
    cacheobj.set("s","sunflower",9);
    REQUIRE(cacheobj.space_used() == 9);
  }

}

TEST_CASE("Checks Cache Content /Get Method")
{
  SECTION("Gets valid values associated with each key_type and resets variable sent in the get method to correct length of value")
  {
    Cache cacheobj(30);
    Cache::size_type ref_len = 10;
    cacheobj.set("s","Sun",3);
    std::string s1 = "Sun";
    REQUIRE(s1.compare(cacheobj.get("s",ref_len)) == 0); //Compare method compares the two strings i.e.sun with sun to check correct value is sent
    REQUIRE(ref_len == 3);                               //ref_len gets assigned to the correct value
  }

  SECTION(" Gets nullptr for invalid key in cache")
  {
    Cache cacheobj(30);
    cacheobj.set("s","sun",3);

    Cache::size_type ref_len = 10;
    REQUIRE(cacheobj.get("z",ref_len) == nullptr);     //Checks non-existent key z which should return nullptr as it doesn't exist in umap
  }
}

TEST_CASE("Check cache deletion /del method")

{

  SECTION("Deletes valid keys and checks if size has been updated.")
  {
    Cache cacheobj(30);

    cacheobj.set("s","Sun",3);
    cacheobj.set("m","Moon",4);
    cacheobj.set("e","Earth",5);

    REQUIRE(cacheobj.del("m") == true);
    REQUIRE(cacheobj.space_used() == 8);
  }

  SECTION("Deletes non-existent keys and checks that size hasn't been modified")
  {
    Cache cacheobj(30);
    cacheobj.set("s","Sun",3);
    REQUIRE(cacheobj.del("m") == false);
    REQUIRE(cacheobj.space_used() == 3);
  }
}

TEST_CASE("Resets everything in Cache /reset method")
{

  SECTION("Size of Cache should be zero if cache is not empty")
  {
    Cache cacheobj(30);

    cacheobj.set("s","Sun",3);
    cacheobj.set("m","Moon",4);
    cacheobj.set("e","Earth",5);
    cacheobj.set("n","Neptune",7);

    cacheobj.reset();

    REQUIRE(cacheobj.space_used() == 0);
  }

SECTION("Size of cache should be zero if cache is empty")

  {
    Cache cacheobj(30);

    cacheobj.reset();

    REQUIRE(cacheobj.space_used() == 0);
  }

SECTION("Checks that umap has been properly cleared out. In other words checks all possible keys are nullptr values when we use get on those keys")
  {
    Cache cacheobj(30);

    cacheobj.set("s","Sun",3);
    cacheobj.set("m","Moon",4);
    cacheobj.set("e","Earth",5);
    cacheobj.set("n","Neptune",7);

    cacheobj.reset();

    REQUIRE(cacheobj.space_used() == 0);

    Cache::size_type ref_len = 10;
    REQUIRE(cacheobj.get("z",ref_len) == nullptr);
    REQUIRE(cacheobj.get("a",ref_len) == nullptr);
    REQUIRE(cacheobj.get("b",ref_len) == nullptr);
  }

}

//Unit Testing of Hash Test

TEST_CASE("HASH TEST")
{

  SECTION("CHECk IF HASH_OBJ GETS ACCEPTED")
  {

    Cache cacheobj(10,0.75,nullptr,cons); //Giving cacheobj the hash function cons
    cacheobj.set("s","Sun",3);
    REQUIRE(hash_list.front() == "s");   //By checking that the list contains s,we actually get to see that the hash function is getting called by the cache object above

  }

}


//Unit Testing of Fifo Class
TEST_CASE("Fifo Evictor")
{

  SECTION("Checks Touch and Eviction of a single item")
  {
    FifoEvictor fifoobj;
    fifoobj.touch_key("apple");
    fifoobj.touch_key("orange");
    fifoobj.touch_key("banana");
    fifoobj.touch_key("cucumber");

    REQUIRE(fifoobj.evict() == "apple");

  }

  SECTION("Touches a key in between multiple Evictions")
  {
      FifoEvictor fifoobj;
      fifoobj.touch_key("apple");
      fifoobj.touch_key("orange");
      fifoobj.touch_key("banana");
      fifoobj.touch_key("cucumber");

      fifoobj.evict();
      fifoobj.evict();
      fifoobj.touch_key("cucumber");
      REQUIRE(fifoobj.evict() == "banana");
      REQUIRE(fifoobj.evict() == "cucumber");
    }


}

//Integration Testing, checks both Cache and Evictor working in conjunction
TEST_CASE("Eviction policy / Checks Fifo Evictor")
{
  SECTION("Check eviction of single entry")
  {
    FifoEvictor fifo2;
    Cache cacheobj2(11, 0.75, &fifo2);
    cacheobj2.set("a", "ant", 3);
    cacheobj2.set("b", "ball", 4);

    // Making sure that "a" gets evicted to make room for "c". If this is happening,
    // total space used should be 7 - 3 + 6 = 10.
    cacheobj2.set("c", "campus", 6);
    REQUIRE(cacheobj2.space_used() == 10);
  }

  SECTION("Checks eviction of multiple entries")
  {

    FifoEvictor fifo3;
    Cache cacheobj3(14, 0.75, &fifo3);

    cacheobj3.set("a", "ant", 3);
    cacheobj3.set("b", "ball", 4);
    cacheobj3.set("c", "campus", 6);
    cacheobj3.set("d", "dungeon", 7);

    // "a" and "b" should be evicted to make room for "d", so
    // new space used should be 13 - 3 - 4 + 7 = 13.
    REQUIRE(cacheobj3.space_used() == 13);
  }

  SECTION("Checks eviction of multiple entries by resetting a key with a larger value ")
  {
    FifoEvictor fifo3;
    Cache cacheobj3(20, 0.75, &fifo3);

    cacheobj3.set("a", "ant", 3);
    cacheobj3.set("b", "ball", 4);
    cacheobj3.set("c", "campus", 6);
    cacheobj3.set("a", "appless", 7);    //Reset a with a bigger sze
    cacheobj3.set("d", "dungeon", 7);

    //Over here, we are Incrementng a so that only "a" gets evicted instead of both a and b
    REQUIRE(cacheobj3.space_used() == 17);
    REQUIRE(cacheobj3.del("a") == false);
  }

}
