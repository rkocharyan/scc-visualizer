# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\scc_algorithms_visualizer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\scc_algorithms_visualizer_autogen.dir\\ParseCache.txt"
  "scc_algorithms_visualizer_autogen"
  )
endif()
