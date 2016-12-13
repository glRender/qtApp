cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set (SRC src)
set (lib_src ${SRC}/glRenderQtWidget.cpp
             ${SRC}/mainwindow.cpp
             ${SRC}/Mark.cpp
             ${SRC}/WoodenBox.cpp
             ${SRC}/BrickBox.cpp
             ${SRC}/Line.cpp
)
set (lib_hdr ${SRC}/glRenderQtWidget.h
             ${SRC}/mainwindow.h
             ${SRC}/Mark.hpp
             ${SRC}/WoodenBox.hpp
             ${SRC}/BrickBox.hpp
             ${SRC}/Line.hpp
)
set (lib_ui  ${SRC}/mainwindow.ui)
set (bin_src ${SRC}/main.cpp)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5OpenGL REQUIRED)

qt5_wrap_cpp(lib_hdr_moc ${lib_hdr})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
        ${SRC}
        ${PROJECT_BINARY_DIR}/app
        ${GLRENDER_INCLUDE_DIR}
)

add_library (Lib SHARED
    ${lib_src}
    ${lib_hdr_moc}
    ${lib_ui_moc})

target_link_libraries (Lib LINK_PUBLIC
    Qt5::Widgets
    Qt5::OpenGL
    ${GLRENDER_LIBRARIES}
)

add_executable(App ${bin_src})
target_link_libraries (App Lib)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
