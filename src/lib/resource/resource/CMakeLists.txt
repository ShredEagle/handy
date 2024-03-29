set(TARGET_NAME resource)

set(${TARGET_NAME}_HEADERS
    ResourceFinder.h
    ResourceLocator.h
    ResourceManager.h
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
             FILES ${${TARGET_NAME}_HEADERS} ${${TARGET_NAME}_SOURCES}
)

add_library(${TARGET_NAME} INTERFACE)

add_library(ad::${TARGET_NAME} ALIAS ${TARGET_NAME})

# Custom target to have the files show up in the IDE
add_custom_target(${TARGET_NAME}_IDE
    SOURCES
        ${${TARGET_NAME}_HEADERS}
)

cmc_target_current_include_directory(${TARGET_NAME})


##
## Dependencies
##

cmc_find_dependencies(FILE CMakeFinds.cmake.in)

target_link_libraries(${TARGET_NAME}
    INTERFACE
        ad::handy
        ad::platform)


##
## Install
##

install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME}Targets)

include(cmc-install)
# Install the header files
cmc_install_with_folders(DESTINATION include/${TARGET_NAME}/${TARGET_NAME}
                         FILES ${${TARGET_NAME}_HEADERS})
# Prepare CMake package in both build and install trees
cmc_install_packageconfig(${TARGET_NAME} ${TARGET_NAME}Targets ${PROJECT_NAME}
                          FIND_FILE CMakeFinds.cmake.in
                          NAMESPACE ad::)
