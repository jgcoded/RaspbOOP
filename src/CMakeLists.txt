# Raspboop CMake file

cmake_minimum_required(VERSION 2.8)

# Raspboop Modules

set(MODULES
  essentials/Core
  boards/L298N
  abstracts/GPIOConsumer
  abstracts/Sensor
  sensors/HCSR04
  sensors/HCSR501
  controls/GPIOManager
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/raspboop/Raspboop
)

foreach(module ${MODULES})
  list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/include/raspboop/${module})
endforeach(module)

add_library(raspboop ${MODULES} ${HEADERS})
