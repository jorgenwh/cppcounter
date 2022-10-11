cmake_minimum_required(VERSION 3.16)
project(cppcounter_C LANGUAGES CXX)

find_package(pybind11 REQUIRED)

set(CMAKE_CXX_FLAGS "-O3")

set(SOURCE_DIR "cppcounter")
include_directories(${SOURCE_DIR})

set(SOURCES 
  "${SOURCE_DIR}/hashtable.cpp"
)

pybind11_add_module(${PROJECT_NAME} ${SOURCES} "${SOURCE_DIR}/bindings.cpp")
