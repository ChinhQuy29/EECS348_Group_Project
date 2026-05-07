# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Complete348_Project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Complete348_Project_autogen.dir\\ParseCache.txt"
  "Complete348_Project_autogen"
  )
endif()
