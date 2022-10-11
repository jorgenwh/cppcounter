#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <sstream>
#include <string>
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

  void count(const uint64_t *keys, const uint32_t size);
  void get(const uint64_t *keys, uint32_t *counts, const uint32_t size);

  uint32_t size() const { return size_m; }
  uint32_t capacity() const { return capacity_m; }

  std::string to_string() const;
private:
  uint32_t size_m;
  uint32_t capacity_m;
  Table table_m;
};

#endif // HASHTABLE_H_
