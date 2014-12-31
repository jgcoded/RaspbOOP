cmake_minimum_required(VERSION 2.8)

set(TARGET RobotStation)

project(${TARGET})

set(STATION_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(QT5_VERSION 5.3.2)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Qt5Widgets REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIR}
)

set(SOURCES main.cpp stationwindow.cpp robotconnectdialog.cpp ../../src/data/Command.cpp)
set(HEADERS stationwindow.h robotconnectdialog.h ../../include/raspboop/data/Command.h)
set(FORMS   stationwindow.ui robotconnectdialog.ui)

qt5_wrap_cpp(MOCS ${HEADERS})
qt5_wrap_ui(GEN ${FORMS})

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${GEN})

target_link_libraries(${TARGET} Qt5::Widgets ${Boost_LIBRARIES})
set_target_properties(${TARGET} PROPERTIES FOLDER ${TARGET})

if(INSTALL_SDK)
  install(TARGETS ${TARGET}
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib/static)
endif()

