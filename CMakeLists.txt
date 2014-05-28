cmake_minimum_required (VERSION 2.6)
project (Rapidformat)

set(TARGET rapidformat)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/wxfb/wxfb.cpp)

if(WIN32)
    add_executable(${TARGET} WIN32 ${SOURCES})
else()
    add_executable(${TARGET} ${SOURCES})
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/wxfb)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(${TARGET} ${wxWidgets_LIBRARIES})

set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost COMPONENTS locale REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${TARGET} ${Boost_LIBRARIES})

add_definitions(-std=c++11)

add_custom_command(TARGET ${TARGET} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/keywords.txt $<TARGET_FILE_DIR:${TARGET}>)