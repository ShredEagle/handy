set(TARGET_NAME platform)

set(${TARGET_NAME}_HEADERS
    Filesystem.h
    Gui.h
    Locale.h
    Path.h
)

set(${TARGET_NAME}_SOURCES
    Gui.cpp
    Locale.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND ${TARGET_NAME}_SOURCES Path-windows.cpp)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND ${TARGET_NAME}_SOURCES Path-linux.cpp)
endif ()

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
             FILES ${${TARGET_NAME}_HEADERS} ${${TARGET_NAME}_SOURCES}
)

add_library(${TARGET_NAME}
    ${${TARGET_NAME}_SOURCES}
    ${${TARGET_NAME}_HEADERS}
)

add_library(ad::${TARGET_NAME} ALIAS ${TARGET_NAME})

cmc_target_current_include_directory(${TARGET_NAME})

cmc_cpp_all_warnings_as_errors(${TARGET_NAME} ENABLED ${BUILD_CONF_WarningAsError})

cmc_cpp_sanitizer(${TARGET_NAME} ${BUILD_CONF_Sanitizer})

##
## Dependencies
##

cmc_find_dependencies(FILE CMakeFinds.cmake.in)

#target_link_libraries(${TARGET_NAME}
#)


##
## Install
##

install(TARGETS ${TARGET_NAME}
        EXPORT ${TARGET_NAME}Targets)

include(cmc-install)
# Install the header files
cmc_install_with_folders(DESTINATION include/${TARGET_NAME}/${TARGET_NAME}
                         FILES ${${TARGET_NAME}_HEADERS})
# Prepare CMake package in both build and install trees
cmc_install_packageconfig(${TARGET_NAME} ${TARGET_NAME}Targets ${PROJECT_NAME}
                          FIND_FILE CMakeFinds.cmake.in
                          NAMESPACE ad::)
