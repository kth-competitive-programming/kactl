cmake_minimum_required(VERSION 3.15)
project(contest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic -Wconversion \
-Wshadow -Wfloat-equal -Wfatal-errors")
if (DEBUG_EXEC) # set in 'Debug'
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fsanitize=address,undefined")
else () # in 'Run' and 'OJ'
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..) # folder with source
set(srcs a b c d e f g h i j k l m) # adjust names as necessary
foreach(F IN LISTS srcs)
  add_executable(${F}.out ${F}.cpp)
endforeach()
