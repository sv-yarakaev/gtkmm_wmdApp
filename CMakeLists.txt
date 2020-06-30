cmake_minimum_required(VERSION 3.10)
project(windowApp)

set(CMAKE_CXX_STANDARD 17)




find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

set(RESOURCE_XML
        "res.xml" )

add_custom_command( OUTPUT ${RESOURCE_XML}
        COMMAND ${CMAKE_COMMAND} -E glib-compile-resources --target=resources.c --generate-source ${RESOURCE_XML}
        VERBATIM
)



add_executable(windowApp main.cpp MainWindow.cpp  resources.c utils.cpp redir_output.cpp )

target_link_libraries(windowApp ${GTKMM_LIBRARIES} )