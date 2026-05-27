set(SRC
    gdt.S
)
if(ENABLE_TESTS)
    list(APPEND SRC ktest.c)
endif()
target_include_directories(kernel PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(basic_drivers)
add_subdirectory(boot)
add_subdirectory(interrupt)
add_subdirectory(mm)
add_subdirectory(task)