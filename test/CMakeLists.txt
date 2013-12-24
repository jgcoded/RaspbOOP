# Raspboop unit tests

cmake_minimum_required(VERSION 2.8)

set(TESTS
)

foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} raspboop wiringPi)
endforeach(test)
