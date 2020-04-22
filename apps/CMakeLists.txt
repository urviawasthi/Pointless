get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../" ABSOLUTE)
include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${FinalProject_SOURCE_DIR}/apps/*.h"
        "${FinalProject_SOURCE_DIR}/apps/*.hpp"
        "${FinalProject_SOURCE_DIR}/apps/*.cc"
        "${FinalProject_SOURCE_DIR}/apps/*.cpp")


ci_make_app(
    APP_NAME    cinder-myapp
    CINDER_PATH ${CINDER_PATH}
    SOURCES     ${SOURCE_LIST}
    LIBRARIES   mylibrary
    BLOCKS
)

target_compile_features(cinder-myapp PRIVATE cxx_std_14)

# Cross-platform compiler lints
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
        OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(cinder-myapp PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    cmake_policy(SET CMP0015 NEW)
    target_compile_options(cinder-myapp PRIVATE
            /W3)
endif ()

cmake_minimum_required(VERSION 3.5)
PROJECT(final-project-urviawasthi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES run.cc)

add_executable(final-project-urviawasthi ${SOURCE_FILES})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
set(ImageMagick C:\\Users\\urvi\\install\\ImageMagick-Windows\\ImageMagick)
set(ImageMagick_INCLUDE_DIRS C:\\Users\\urvi\\install\\ImageMagick-Windows\\ImageMagick\\Magick++\\lib)
set(ImageMagick_LIBRARIES C:\\Users\\urvi\\install\\ImageMagick-Windows\\ImageMagick\\Magick++\\lib)
find_package(ImageMagick REQUIRED COMPONENTS Magick++ MagickCore)
include_directories(${ImageMagick_INCLUDE_DIRS})
link_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(final-project-urviawasthi ${ImageMagick_LIBRARIES})