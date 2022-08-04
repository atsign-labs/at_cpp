cmake_minimum_required(VERSION 3.22)
project(at_client_cpp_demo)

set(CMAKE_CXX_STANDARD 14)

set(OPENSSL_ROOT_DIR  "C:\\Program Files\\OpenSSL-Win64")
find_package(OpenSSL REQUIRED)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(at_client_cpp_demo main.cpp)

target_include_directories(at_client_cpp_demo PRIVATE .)
target_include_directories(at_client_cpp_demo PRIVATE "C:/Program Files/OpenSSL-Win64/include")
target_link_directories(at_client_cpp_demo PRIVATE "C:/Program Files/OpenSSL-Win64/lib")
target_link_libraries(at_client_cpp_demo PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(at_client_cpp_demo PRIVATE at_client_cpp)

add_library(at_client_cpp lib/Server.cpp lib/Crypto.cpp lib/AtClient.cpp lib/Utils.cpp)

target_include_directories(at_client_cpp PRIVATE .)
target_include_directories(at_client_cpp PRIVATE "C:/Program Files/OpenSSL-Win64/include")
target_link_directories(at_client_cpp PRIVATE "C:/Program Files/OpenSSL-Win64/lib")

target_link_libraries(at_client_cpp PRIVATE OpenSSL::SSL)
target_link_libraries(at_client_cpp PRIVATE ssl crypto)
target_link_libraries(at_client_cpp PRIVATE nlohmann_json::nlohmann_json)
