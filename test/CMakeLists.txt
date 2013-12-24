# Raspboop unit tests

cmake_minimum_required(VERSION 2.8)

set(TESTS
  sensors
)

foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} raspboop)
endforeach(test)
