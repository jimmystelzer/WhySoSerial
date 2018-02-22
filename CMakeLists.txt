cmake_minimum_required(VERSION 2.8)

project(WhySoSerial)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

set(FLTK_SKIP_OPENGL true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR}) 
link_directories(${FLTK_LIBRARY_DIRS}) 
add_definitions(${FLTK_DEFINITIONS})

find_program(LSB_RELEASE lsb_release)
    execute_process(COMMAND ${LSB_RELEASE} -sc
    OUTPUT_VARIABLE LSB_RELEASE_CODENAME_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(LSB_RELEASE_CODENAME_SHORT STREQUAL "trusty")
    find_program(FLTK_CONFIG fltk-config)
    execute_process(COMMAND ${FLTK_CONFIG} --ldstaticflags
        OUTPUT_VARIABLE FLTK_CONFIG_LD
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(COMMAND ${FLTK_CONFIG} --cxxflags
        OUTPUT_VARIABLE FLTK_CONFIG_CXX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(LIBS "${FLTK_CONFIG_LD}")
else()
    set(LIBS "${FLTK_LIBRARIES}")
endif()


add_subdirectory(src)
