cmake_minimum_required(VERSION 3.10)
project(windowApp)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )



add_executable(windowApp main.cpp MainWindow.cpp AddIPModal.cpp AddIPModal.h)

target_link_libraries(windowApp ${GTKMM_LIBRARIES})