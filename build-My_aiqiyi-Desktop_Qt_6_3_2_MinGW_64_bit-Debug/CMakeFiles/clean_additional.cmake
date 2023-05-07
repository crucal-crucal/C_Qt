# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\My_aiqiyi_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\My_aiqiyi_autogen.dir\\ParseCache.txt"
  "My_aiqiyi_autogen"
  )
endif()
