set(TARGET_NAME handy_tests)

set(${TARGET_NAME}_HEADERS
    catch.hpp
)

set(${TARGET_NAME}_SOURCES
    main.cpp

    Base64_tests.cpp
    Crc_tests.cpp
    FunctionTraits_tests.cpp
    StringId_tests.cpp
    StringUtilities_tests.cpp
)

add_executable(${TARGET_NAME}
               ${${TARGET_NAME}_HEADERS}
               ${${TARGET_NAME}_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        ad::handy)

cmc_cpp_all_warnings_as_errors(${TARGET_NAME} ENABLED ${BUILD_CONF_WarningAsError})

cmc_cpp_sanitizer(${TARGET_NAME} ${BUILD_CONF_Sanitizer})

set_target_properties(${TARGET_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)

install(TARGETS ${TARGET_NAME})
