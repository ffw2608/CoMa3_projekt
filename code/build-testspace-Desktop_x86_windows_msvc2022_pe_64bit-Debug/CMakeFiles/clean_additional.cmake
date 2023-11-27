# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\testspace_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\testspace_autogen.dir\\ParseCache.txt"
  "testspace_autogen"
  )
endif()
