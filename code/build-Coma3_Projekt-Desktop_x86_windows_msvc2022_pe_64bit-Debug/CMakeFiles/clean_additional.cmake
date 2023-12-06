# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Coma3_Projekt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Coma3_Projekt_autogen.dir\\ParseCache.txt"
  "Coma3_Projekt_autogen"
  )
endif()
