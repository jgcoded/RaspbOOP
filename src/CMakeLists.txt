# Raspboop CMake file

cmake_minimum_required(VERSION 2.8)

# Raspboop Modules

set(MODULES
  essentials/Core
  data/Command
  boards/L298N
  abstracts/GPIOConsumer
  abstracts/Sensor
  sensors/HCSR04
  sensors/HCSR501
  controls/GPIOManager
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/raspboop/Raspboop
  ${CMAKE_SOURCE_DIR}/include/raspboop/essentials/Pins
)

set(INTERFACES
  ${CMAKE_SOURCE_DIR}/include/raspboop/interfaces/Commandable
  ${CMAKE_SOURCE_DIR}/include/raspboop/interfaces/Serializable
)

foreach(module ${MODULES})
  list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/include/raspboop/${module})
endforeach(module)

foreach(interface ${INTERFACES})
  list(APPEND HEADERS ${interface})
endforeach(interface)

add_library(raspboop ${HEADERS} ${MODULES})
target_link_libraries(raspboop ${RASPBOOP_LIBRARIES})
