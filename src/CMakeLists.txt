add_library(queue INTERFACE)

target_include_directories(queue INTERFACE .)

add_executable(app main.cpp)
target_link_libraries(app queue)