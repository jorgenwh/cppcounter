#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>
#include <inttypes.h>

static const uint64_t kEmpty = 0xffffffffffffffff;

struct Table {
  uint64_t *keys;
  uint32_t *values;
};

class HashTable {
public:
  HashTable() = default;
  HashTable(const uint64_t *keys, const uint32_t size, const uint32_t capacity);
  ~HashTable() {
    delete[] table_m.keys;
    delete[] table_m.values;
  }

  void count(
      const uint64_t *keys, const uint32_t size, const uint32_t num_threads);
  void get(
      const uint64_t *keys, uint32_t *counts, const uint32_t size, const uint32_t num_threads);

  uint32_t size() const { return size_m; }
  uint32_t capacity() const { return capacity_m; }

  std::string to_string() const;
private:
  uint32_t size_m;
  uint32_t capacity_m;
  Table table_m;

  std::mutex mu_m;

  void counting_worker(const uint64_t *keys, const uint32_t size, 
      const uint32_t offset, const uint32_t num_threads);
};

#endif // HASHTABLE_H_
