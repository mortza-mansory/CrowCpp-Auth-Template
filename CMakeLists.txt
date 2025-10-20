cmake_minimum_required(VERSION 3.16)
project(crow_auth_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch Asio
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-30-2
)
FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include CACHE PATH "Path to Asio headers")

# Fetch JSON
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Fetch JWT
FetchContent_Declare(
  jwt_cpp
  GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
  GIT_TAG v0.7.0
)
FetchContent_MakeAvailable(jwt_cpp)

# Fetch Crow
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.3.0
)
FetchContent_MakeAvailable(crow)

find_package(OpenSSL REQUIRED)

add_executable(crow_auth_server src/main.cpp)

target_include_directories(crow_auth_server PRIVATE
    ${asio_SOURCE_DIR}/asio/include
    ${jwt_cpp_SOURCE_DIR}/include
    ${crow_SOURCE_DIR}/include
    ${nlohmann_json_SOURCE_DIR}/include
)

target_link_libraries(crow_auth_server PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    pthread
)

add_definitions(-DCROW_USE_ASIO)
add_definitions(-DCROW_ENABLE_SSL)
