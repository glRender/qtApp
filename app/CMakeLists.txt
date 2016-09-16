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
set (INCLUDE include)

set (glRenderQtWidget_src ${SRC}/glRenderQtWidget.cpp)
set (glRenderQtWidget_hdr ${INCLUDE}/glRenderQtWidget.h)

qt5_wrap_cpp(glRenderQtWidget_hdr_moc ${glRenderQtWidget_hdr})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

include_directories(
        ${PROJECT_BINARY_DIR}/libs/glRender/include
        ${GLEW_INCLUDE_DIRS}
)

if(WIN32)
    file(COPY libs/glew/lib/glew32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

add_library (glRenderQtWidget SHARED ${glRenderQtWidget_src} ${glRenderQtWidget_hdr_moc}
            )
target_link_libraries (glRenderQtWidget Qt5::Widgets Qt5::OpenGL ${GLEW_LIBRARIES} ${PROJECT_BINARY_DIR}/libs/glRender/libglRender.so)

target_include_directories(glRenderQtWidget PUBLIC include)

file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})