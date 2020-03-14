# HW_03-Systems-Testy-Cache-
### Names : Prasun and Hrishee 

## File Overview 
All the files from HW2 (hash it out) are present, except now we include a testing file `testy_cache.cc` to test functionality. To compile and run, do `make` and then `./test`. You may have to change the compiler version in the makefile to be compatible with your computer. 
## Testy Cache (Part 1)
We are using the [Catch2 test framework](https://github.com/catchorg/Catch2). We have 7 test cases, with a total of 17 sections split among them. Each test name is the unit/integration test case name, while each description is a test section corresponding to that test case.

Test name | Description | Pass/Fail 
----------|-------------|----------
Cache Accepts input | Check that the cache is initialized with zero memory use | Pass
 ... | Cache doesn't accept input that exceeds maxmems | Pass
... | Accepts 1st input and make the value of 2nd input greater than maxmem | Pass
... | Cache accepts input with a given key-value and then resets key with a new value | Pass
... | Cache resets existing key where sum of previous and updated value exceeds maxmem | Fail
Check Cache contents | Gets valid values associated with each key_type and resets variable sent in the get method to correct length of value | Pass 
... | Gets nullptr for invalid key in cache | Pass
Check Cache deletion | Deletes valid keys and checks if size has been updated | Pass
... | Deletes non-existent keys and checks that size hasn't been modified | Pass
Check Cache resets | Size of Cache should be zero if reset nonempty cache | Pass 
... | Size of cache should be zero if reset empty cache  | Pass
... | Gets nullptr after removing existing keys from cache | Pass
Hash test | Cache accepts and uses custom hash function | Pass
FIFO Evictor test| Checks Touch and Eviction of a single item | Pass
... | Touches a key in between multiple Evictions | Pass
Integration Test (Cache + Evictor) | Check eviction of single entry | Pass
... | Checks eviction of multiple entries | Pass
... | Checks eviction of multiple entries by resetting a key with a larger value | Pass

 
## 
