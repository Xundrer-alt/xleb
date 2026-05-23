cmake_minimum_required(VERSION 4.1)
set(CMAKE_C_COMPILER_WORKS ON CACHE BOOL "Skip compiler test" FORCE)
set(CMAKE_ASM_COMPILER_WORKS ON CACHE BOOL "Skip compiler test" FORCE)

project(kernel VERSION 0.0.1 LANGUAGES C ASM)
add_executable(kernel)
target_include_directories(kernel PRIVATE
    src/include
)

add_subdirectory(src)

target_link_options(kernel PRIVATE
    -nostdlib
    -static
    -T ${CMAKE_SOURCE_DIR}/src/${ARCH}/linker.ld
)
