# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CMake_mysql_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CMake_mysql_autogen.dir\\ParseCache.txt"
  "CMake_mysql_autogen"
  )
endif()
