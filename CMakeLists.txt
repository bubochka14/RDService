cmake_minimum_required(VERSION 3.2)
project(RDSessionViewer VERSION 0.01 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.3.2/msvc2019_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Sql)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

option(ENABLE_TESTING "" ON)

if(ENABLE_TESTING)
    enable_testing()

    add_subdirectory(tests)
endif()

add_subdirectory(app)
