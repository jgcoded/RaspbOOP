# Raspboop unit tests

cmake_minimum_required(VERSION 2.8)

set(TESTS
  boards
  gpiomanager
  packet
  sensors
)

foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} raspboop ${RASPBOOP_LIBRARIES})
endforeach(test)
