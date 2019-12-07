cmake_minimum_required(VERSION 3.13)

# set the project name
project(test1 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(test1string test1.cpp)
	
# add the executable
add_executable(test1 main.c)

target_link_libraries(test1 PUBLIC test1string)

enable_testing()

# does the application run
add_test(NAME Runs COMMAND test1)