#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "hashtable.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(cppcounter_C, m) {
  m.doc() = "Documentation for the cppcounter C backend module";

  py::class_<HashTable>(m, "HashTable")
    .def(py::init([](py::array_t<uint64_t> &keys, const uint32_t capacity) {
      const uint64_t *data = (uint64_t *)keys.data();
      const uint32_t size = keys.size();
      return new HashTable(data, size, capacity);
    }))
    .def("count", [](HashTable &self, py::array_t<uint64_t> &keys) {
      const uint64_t *data = (uint64_t *)keys.data();
      const uint32_t size = keys.size();
      self.count(data, size);
    })
    .def("get", [](HashTable &self, py::array_t<uint64_t> &keys) {
      py::buffer_info buf = keys.request();
      const uint64_t *data = (uint64_t *)keys.data();
      const uint32_t size = keys.size();

      auto ret = py::array_t<uint32_t>(buf.size);
      uint32_t *counts_data = ret.mutable_data();

      self.get(data, counts_data, size);

      return ret;
    })
    .def("size", &HashTable::size)
    .def("capacity", &HashTable::capacity)
    .def("__repr__", &HashTable::to_string)
    ;

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
