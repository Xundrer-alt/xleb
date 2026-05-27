set(SRC
    gdt.S
)
target_include_directories(kernel PRIVATE
    .
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(basic_drivers)
add_subdirectory(boot)
add_subdirectory(interrupt)
add_subdirectory(mm)
add_subdirectory(task)