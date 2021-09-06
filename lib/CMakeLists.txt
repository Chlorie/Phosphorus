add_library(phosphorus)
add_library(phosphorus::phosphorus ALIAS phosphorus)

target_set_output_dirs(phosphorus)
set_target_properties(phosphorus PROPERTIES LINKER_LANGUAGE CXX)

function (add_headers TGT)
    set(headers ${ARGN})
    list(TRANSFORM headers PREPEND "include/phosphorus/")
    set(${TGT} ${headers} PARENT_SCOPE)
endfunction ()
function (add_sources TGT)
    set(sources ${ARGN})
    list(TRANSFORM sources PREPEND "src/")
    set(${TGT} ${sources} PARENT_SCOPE)
endfunction ()

add_headers(HEADERS
    # Header files here (relative to ./include/phosphorus/)
    "core/application.h"
    "core/entry_point.h"
    "core/error.h"
    "core/export.h"
    "core/log.h"

    "utils/chrono.h"
)
add_sources(SOURCES
    # Source files here (relative to ./src/)
    "core/application.cpp"
    "core/error.cpp"
    "core/log.cpp"
)

find_package(spdlog CONFIG REQUIRED)

target_sources(phosphorus PRIVATE ${HEADERS} ${SOURCES} "include/phosphorus/core/entry_point.h")
target_set_options(phosphorus)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(phosphorus
        PRIVATE PH_EXPORT_SHARED
        PUBLIC PH_BUILD_SHARED)
endif ()

target_include_directories(phosphorus
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(phosphorus
PUBLIC
    spdlog::spdlog
)

target_compile_features(phosphorus PRIVATE cxx_std_20)

if (ENABLE_INSTALL)
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/phosphorusConfigVersion.cmake"
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(TARGETS phosphorus
        EXPORT phosphorusTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
    )

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/phosphorusConfig.cmake.in"
        "${PROJECT_BINARY_DIR}/phosphorusConfig.cmake"
        INSTALL_DESTINATION lib/cmake/phosphorus
    )

    export(TARGETS phosphorus NAMESPACE phosphorus:: FILE phosphorusConfig.cmake)
    install(EXPORT phosphorusTargets NAMESPACE phosphorus:: DESTINATION lib/cmake/phosphorus)
    install(FILES "${PROJECT_BINARY_DIR}/phosphorusConfigVersion.cmake"
                  "${PROJECT_BINARY_DIR}/phosphorusConfig.cmake"
            DESTINATION lib/cmake/phosphorus)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/include/ DESTINATION include)
endif ()
