cmake_minimum_required(VERSION 3.16)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql)

qt_standard_project_setup()

qt_add_executable(app_tests
    sessionsqlmodel_test.cpp
)
target_include_directories(app_tests PRIVATE
    ${APP_SOURCE}

)
target_link_libraries(app_tests PRIVATE
    APP_LIB
    GTest::gtest_main

)

include(GoogleTest)
gtest_discover_tests(app_tests)
