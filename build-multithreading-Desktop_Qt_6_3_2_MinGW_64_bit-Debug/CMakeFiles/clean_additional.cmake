# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\multithreading_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\multithreading_autogen.dir\\ParseCache.txt"
  "multithreading_autogen"
  )
endif()
