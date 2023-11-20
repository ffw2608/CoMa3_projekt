# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\musiktafel_temp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\musiktafel_temp_autogen.dir\\ParseCache.txt"
  "musiktafel_temp_autogen"
  )
endif()
