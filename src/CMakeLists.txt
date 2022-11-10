add_subdirectory(lib/handy/handy)
add_subdirectory(lib/platform/platform)

add_subdirectory(lib/resource/resource)

option(BUILD_tests "Build the demo applications" ON)
if(BUILD_tests)
    add_subdirectory(app/handy_tests/handy_tests)
    add_subdirectory(app/handy_dialog/handy_dialog)
endif()
