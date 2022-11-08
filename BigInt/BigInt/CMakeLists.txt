# CMakeList.txt: проект CMake для BigInt; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.

cmake_minimum_required (VERSION 3.8)

project(BigInt LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (BigInt "BigInt.cpp" "BigInt.h" )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -Werror -Wall")
add_compile_options(-werror -wall -fsanitize=address --coverage)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
