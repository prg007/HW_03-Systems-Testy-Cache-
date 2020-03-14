# HW_03-Systems-Testy-Cache-
### Names : Prasun and Hrishee 

## File Overview 
All the files from HW2 (hash it out) are present, except now we include a testing file `testy_cache.cc` to test functionality. To compile and run, do `make` and then `./test`. You may have to change the compiler version in the makefile to be compatible with your computer. 
## Testy Cache (Part 1)
We are using the [Catch2 test framework](https://github.com/catchorg/Catch2). We have 7 test cases, with a total of 19 sections split among them. Each test name is the unit/integration test case name, while each description is a test section corresponding to that test case.

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
... | Returns "" if queue is empty | Pass
Integration Test (Cache + Evictor) | Check eviction of single entry | Pass
... | Checks eviction of multiple entries | Pass
... | Checks eviction of multiple entries by resetting a key with a larger value | Pass

 
## Testing other groups code (Part 2)

We run our tests on three other groups Cache code:

[Eric + Vinay](https://github.com/gopalanvinay/hw2-systems)

[Jon + Eli](https://github.com/jon-takagi/CS389HW2)

[Albert + Yao](https://github.com/zhengyaogu/cs389hw2)


### Eric + Vinay
Test name | Description | Pass/Fail 
----------|-------------|----------
Cache Accepts input | Check that the cache is initialized with zero memory use | Pass
 ... | Cache doesn't accept input that exceeds maxmems | Pass
... | Accepts 1st input and make the value of 2nd input greater than maxmem | Pass
... | Cache accepts input with a given key-value and then resets key with a new value | Fail
... | Cache resets existing key where sum of previous and updated value exceeds maxmem | Fail
Check Cache contents | Gets valid values associated with each key_type and resets variable sent in the get method to correct length of value | Fail 
... | Gets nullptr for invalid key in cache | Pass
Check Cache deletion | Deletes valid keys and checks if size has been updated | Fail
... | Deletes non-existent keys and checks that size hasn't been modified | Fail
Check Cache resets | Size of Cache should be zero if reset nonempty cache | Pass 
... | Size of cache should be zero if reset empty cache  | Pass
... | Gets nullptr after removing existing keys from cache | Pass
Hash test | Cache accepts and uses custom hash function | Pass
FIFO Evictor test| Checks Touch and Eviction of a single item | Pass
... | Touches a key in between multiple Evictions | Pass
... | Returns "" if queue is empty | Fail
Integration Test (Cache + Evictor) | Check eviction of single entry | Fail
... | Checks eviction of multiple entries | Fail
... | Checks eviction of multiple entries by resetting a key with a larger value | Pass

The only compilation/linking issue we faced with Eric + Vinay's code is the name of the FifoEvictor class in their implementation. In ours, it was `FifoEvictor` but in theirs it was `Fifo`. For it to compile and be compatible with our test cases, we had to change all instances of `Fifo` to `FifoEvictor` in their interface/implementation. The number of fails in their code may be attributed to bugs and/or different assumptions made when they wrote their Cache (as a number of instructions in the assigment were left to interpretation, such as what happens when to the val_size when getting an invalid key). 

### Jon + Eli
Test name | Description | Pass/Fail 
----------|-------------|----------
Cache Accepts input | Check that the cache is initialized with zero memory use | Pass
 ... | Cache doesn't accept input that exceeds maxmems | Pass
... | Accepts 1st input and make the value of 2nd input greater than maxmem | Pass
... | Cache accepts input with a given key-value and then resets key with a new value | Pass
... | Cache resets existing key where sum of previous and updated value exceeds maxmem | Pass
Check Cache contents | Gets valid values associated with each key_type and resets variable sent in the get method to correct length of value | Pass 
... | Gets nullptr for invalid key in cache | Fail
Check Cache deletion | Deletes valid keys and checks if size has been updated | Pass
... | Deletes non-existent keys and checks that size hasn't been modified | Pass
Check Cache resets | Size of Cache should be zero if reset nonempty cache | Pass 
... | Size of cache should be zero if reset empty cache  | Pass
... | Gets nullptr after removing existing keys from cache | Fail
Hash test | Cache accepts and uses custom hash function | Pass
FIFO Evictor test| Checks Touch and Eviction of a single item | Pass
... | Touches a key in between multiple Evictions | Pass
... | Returns "" if queue is empty | Fail
Integration Test (Cache + Evictor) | Check eviction of single entry | Pass
... | Checks eviction of multiple entries | Pass
... | Checks eviction of multiple entries by resetting a key with a larger value | Pass

We encountered no nontrivial compilation/linking errors with Jon + Eli, apart from renaming FifoEvictor. They passed 28 out of 30 assertions(Or REQUIRED) statements. In evictor, while evicting a key, they forget to check if the queue is empty first in which case it should return an empty string. Also, in get method for an invalid key, we are operating under the assumption that the variable val_size passed by reference does not change. It seems that Eli + Jon reset val_size to zero in this edge case. Both interpretations are fine. 

### Albert + Yao
Test name | Description | Pass/Fail 
----------|-------------|----------
Cache Accepts input | Check that the cache is initialized with zero memory use | Pass
 ... | Cache doesn't accept input that exceeds maxmems | Pass
... | Accepts 1st input and make the value of 2nd input greater than maxmem | Pass
... | Cache accepts input with a given key-value and then resets key with a new value | Pass
... | Cache resets existing key where sum of previous and updated value exceeds maxmem | Pass
Check Cache contents | Gets valid values associated with each key_type and resets variable sent in the get method to correct length of value | Pass 
... | Gets nullptr for invalid key in cache | Fail
Check Cache deletion | Deletes valid keys and checks if size has been updated | Pass
... | Deletes non-existent keys and checks that size hasn't been modified | Pass
Check Cache resets | Size of Cache should be zero if reset nonempty cache | Pass 
... | Size of cache should be zero if reset empty cache  | Pass
... | Gets nullptr after removing existing keys from cache | Fail
Hash test | Cache accepts and uses custom hash function | Pass
FIFO Evictor test| Checks Touch and Eviction of a single item | Pass
... | Touches a key in between multiple Evictions | Pass
... | Returns "" if queue is empty | Pass
Integration Test (Cache + Evictor) | Check eviction of single entry | Pass
... | Checks eviction of multiple entries | Pass
... | Checks eviction of multiple entries by resetting a key with a larger value | Pass

We encountered no nontrivial compilation/linking errors, apart from renaming FifoEvictor. According to our test, they reset val_size to zero when getting an invalid key in the cache, similar to Jon + Eli.   
