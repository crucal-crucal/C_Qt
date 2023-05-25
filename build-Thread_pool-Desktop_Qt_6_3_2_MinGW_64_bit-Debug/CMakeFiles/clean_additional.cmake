# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Thread_pool_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Thread_pool_autogen.dir\\ParseCache.txt"
  "Thread_pool_autogen"
  )
endif()
