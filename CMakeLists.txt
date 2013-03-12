project(box)

set (CMAKE_CXX_FLAGS -std=c++11)

add_executable(box main.cpp)

install(TARGETS box RUNTIME DESTINATION bin)
