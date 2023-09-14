add_library(helloLib hello.c hello.h)

target_link_libraries(helloLib)

# target_include_directories(helloLib PUBLIC ../include/)
target_include_directories(helloLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
