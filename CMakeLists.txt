cmake_minimum_required(VERSION 3.0.0)
project(engineSFML VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(Threads REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories("src/")
include_directories("hpp/")

file(GLOB files CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "hpp/*.hpp"
     "src/*.cpp"
) 

add_library(engineSFML ${files} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
