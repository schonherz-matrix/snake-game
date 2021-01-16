cmake_minimum_required(VERSION 3.16)

project(
  matrix-snake-game
  HOMEPAGE_URL "kszk.bme.hu"
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(LIBMUEB_AS_DLL)

find_package(
  Qt5
  COMPONENTS Widgets Network Multimedia
  REQUIRED)
find_package(libmueb 2.0 REQUIRED)

add_executable(
  ${PROJECT_NAME} WIN32
  src/bite.cpp
  src/bite.h
  src/board.cpp
  src/board.h
  src/config.cpp
  src/config.h
  src/direction.h
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
  src/matrixscene.cpp
  src/matrixscene.h
  src/snake.cpp
  src/snake.h
  resources/resources.qrc)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::Network
                          libmueb::muebtransmitter)
