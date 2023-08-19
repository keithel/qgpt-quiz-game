add_subdirectory(nlohmann_json)
add_subdirectory(curl)

set(CURL_DIR "${CMAKE_CURRENT_BINARY_DIR}/curl/generated")
set(nlohmann_json_DIR "${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json/generated")

add_subdirectory(liboai/liboai)
