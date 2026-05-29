# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2026 Xundrer-alt
cmake_minimum_required(VERSION 4.1)
set(CMAKE_C_COMPILER_WORKS ON CACHE BOOL "Skip compiler test" FORCE)
set(CMAKE_ASM_COMPILER_WORKS ON CACHE BOOL "Skip compiler test" FORCE)

project(xleb VERSION 0.0.1 LANGUAGES C ASM)
add_executable(kernel)
configure_file(
    ${CMAKE_SOURCE_DIR}/src/config.h.in
    ${CMAKE_BINARY_DIR}/config.h
    @ONLY
)
target_include_directories(kernel PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}
)

option(ENABLE_TESTS "Build tests and ktest instead kmain" OFF)
if(ENABLE_TESTS)
    message(STATUS "Tests enabled")
endif()
add_subdirectory(src)

# rust part
set(RUST_DIR ${CMAKE_SOURCE_DIR}/rust)
set(RUST_LIB ${RUST_DIR}/target/i686-unknown-linux-gnu/release/librust.rlib)
set(RUST_HEADER ${CMAKE_BINARY_DIR}/rust_ffi.h)
add_custom_command(
    OUTPUT ${RUST_HEADER}
    COMMAND cbindgen --lang c --output ${RUST_HEADER} ${RUST_DIR}
    WORKING_DIRECTORY ${RUST_DIR}
    COMMENT "Generating C headers from Rust"
    DEPENDS ${RUST_DIR}/src/lib.rs
)
add_custom_target(rust_headers ALL
    DEPENDS ${RUST_HEADER}
)
add_custom_target(rust_build ALL
    COMMAND cargo build --release
    WORKING_DIRECTORY ${RUST_DIR}
    COMMENT "Building Rust library"
    BYPRODUCTS ${RUST_LIB}
)
add_dependencies(rust_build rust_headers)
add_dependencies(kernel rust_build)
target_link_libraries(kernel
    ${RUST_LIB}
)

target_link_options(kernel PRIVATE
    -nostdlib
    -static
    -T ${CMAKE_SOURCE_DIR}/src/${ARCH}/linker.ld
)
