#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <inttypes.h>

#include "hashtable.h"

HashTable::HashTable(const uint64_t *keys, const uint32_t size, const uint32_t capacity) {
  size_m = size;
  capacity_m = capacity;

  table_m.keys = new uint64_t[capacity_m];
  table_m.values= new uint32_t[capacity_m];
  memset(table_m.keys, 0xff, sizeof(uint64_t)*capacity_m);

  for (int i = 0; i < size; i++) {
    uint64_t key = keys[i];
    uint64_t hash = key % capacity_m;

    while (true) {
      uint64_t cur = table_m.keys[i]; 

      if (cur == kEmpty || cur == key) {
        table_m.keys[i] = key;
        table_m.values[i] = 0;
        break;
      }
      hash = (hash + 1) % capacity_m;
    }
  }
}

void HashTable::count(const uint64_t *keys, const uint32_t size) {
  for (int i = 0; i < size; i++) {
    uint64_t key = keys[i];
    uint64_t hash = key % capacity_m;

    while (true) {
      uint64_t cur = table_m.keys[i]; 

      if (cur == key) {
        table_m.values[i]++;
        break;
      }
      if (cur == kEmpty) {
        break;
      }
      hash = (hash + 1) % capacity_m;
    }
  }
}

void HashTable::get(const uint64_t *keys, uint32_t *counts, const uint32_t size) {
  for (int i = 0; i < size; i++) {
    uint64_t key = keys[i];
    uint64_t hash = key % capacity_m;

    while (true) {
      uint64_t cur = table_m.keys[i]; 

      if (cur == key) {
        counts[i] = table_m.values[i];
        break;
      }
      if (cur == kEmpty) {
        counts[i] = 0;
        break;
      }
      hash = (hash + 1) % capacity_m;
    }
  }
}

std::string HashTable::to_string() const {
  int print_size = (capacity_m < 40) ? capacity_m : 40;

  std::ostringstream oss;
  std::ostringstream keys_oss;
  std::ostringstream values_oss;

  keys_oss << "[";
  values_oss << "[";
  uint32_t elements = 0;
  for (int i = 0; i < capacity_m; i++) {
    uint64_t key = table_m.keys[i];
    uint32_t value = table_m.values[i];

    if (key == kEmpty) { continue; }

    if (elements != 0) { 
      keys_oss << ", "; 
      values_oss << ", "; 
    }

    keys_oss << key;
    values_oss << value;
    
    elements++;
    if (elements >= print_size) { break; }
  }
  keys_oss << "]";
  values_oss << "]";

  oss << "Counter(" << keys_oss.str() << ", " << values_oss.str();
  oss << ", size=" << size_m << ", capacity=" << capacity_m << ")";

  return oss.str();
}
