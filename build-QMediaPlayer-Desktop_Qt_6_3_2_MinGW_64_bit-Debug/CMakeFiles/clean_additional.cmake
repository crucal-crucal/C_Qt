# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QMediaPlayer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QMediaPlayer_autogen.dir\\ParseCache.txt"
  "QMediaPlayer_autogen"
  )
endif()
