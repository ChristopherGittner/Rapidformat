cmake_minimum_required (VERSION 3.0)
project (Rapidformat)

set(TARGET rapidformat)

set(SOURCES src/sdf.py src/main.cpp src/MainFrame.cpp src/Preferences.cpp src/PreferencesFrame.cpp src/ProgressDialog.cpp src/RapidformatApp.cpp wxfb/wxfb.cpp)

if(WIN32)
    add_executable(${TARGET} WIN32 ${SOURCES})
else()
    add_executable(${TARGET} ${SOURCES})
endif()

include_directories(include)
include_directories(wxfb)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(${TARGET} ${wxWidgets_LIBRARIES})

if(WIN32)
  find_package(Boost REQUIRED)
else()
  find_package(Boost COMPONENTS locale REQUIRED)
  target_link_libraries(${TARGET} ${Boost_LIBRARIES})
endif()

include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-std=c++11)

add_custom_command(TARGET ${TARGET} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/keywords.txt $<TARGET_FILE_DIR:${TARGET}>)
