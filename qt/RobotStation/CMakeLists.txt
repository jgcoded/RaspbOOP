cmake_minimum_required(VERSION 2.8)

set(TARGET RobotStation)

project(${TARGET})

set(CMAKE_PREFIX_PATH "/opt/Qt/5.3/gcc_64/lib/cmake/Qt5Widgets")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

set(SOURCES main.cpp stationwindow.cpp robotconnectdialog.cpp)
set(HEADERS stationwindow.h robotconnectdialog.h)
set(FORMS   stationwindow.ui robotconnectdialog.ui)

qt5_wrap_cpp(MOCS ${HEADERS})
qt5_wrap_ui(GEN ${FORMS})

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${GEN})

target_link_libraries(${TARGET} Qt5::Widgets)
