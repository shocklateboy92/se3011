project(box)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_executable(box record.cpp streams.cpp main.cpp)
TARGET_LINK_LIBRARIES(box ${QT_LIBRARIES})

install(TARGETS box RUNTIME DESTINATION bin)
