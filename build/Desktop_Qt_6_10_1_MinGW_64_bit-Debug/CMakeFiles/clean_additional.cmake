# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appSGPL_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appSGPL_autogen.dir\\ParseCache.txt"
  "appSGPL_autogen"
  )
endif()
