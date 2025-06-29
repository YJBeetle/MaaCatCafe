cmake_minimum_required(VERSION 3.28)

project(MaaCatCafe VERSION 0.1.0 LANGUAGES CXX)

include(${PROJECT_SOURCE_DIR}/cmake/FetchMaaFramework.cmake)
find_package(MaaFramework CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    MaaFramework::MaaFramework
    MaaFramework::MaaToolkit
)
