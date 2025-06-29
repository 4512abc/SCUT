# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ZZz_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ZZz_autogen.dir\\ParseCache.txt"
  "ZZz_autogen"
  )
endif()
