cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)

find_package (Qt5Widgets)
find_package (Qt5OpenGL)

if(WIN32)
    set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/glew32.dll )
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include )
endif()

find_package(GLEW REQUIRED)

set (SRC src)

set (lib_src ${SRC}/glRenderQtWidget.cpp
             ${SRC}/mainwindow.cpp)

set (lib_hdr ${SRC}/glRenderQtWidget.h
             ${SRC}/mainwindow.h)

set (lib_ui  ${SRC}/mainwindow.ui)

set (bin_src ${SRC}/main.cpp)

qt5_wrap_cpp(lib_hdr_moc ${lib_hdr})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
        ${SRC}
        ${PROJECT_BINARY_DIR}/app
        ${GLRENDER_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS})

add_library (Lib SHARED
    ${lib_src}
    ${lib_hdr_moc}
    ${lib_ui_moc})

target_link_libraries (Lib Qt5::Widgets Qt5::OpenGL ${GLEW_LIBRARIES} ${GLRENDER_LIBRARIES})

add_executable(App ${bin_src})
target_link_libraries (App Lib)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
