add_library(phosphorus)
add_library(phosphorus::phosphorus ALIAS phosphorus)

target_set_output_dirs(phosphorus)
set_target_properties(phosphorus PROPERTIES 
    LINKER_LANGUAGE CXX
    DEFINE_SYMBOL ""
)

set(HEADERS
    # Header files here (relative to ./include/phosphorus/)
    "phosphorus.h"

    "core/application.h"
    "core/entry_point.h"
    "core/error.h"
    "core/export.h"
    "core/log.h"

    "event/event.h"
    "event/events_fwd.h"
    "event/key_events.h"
    "event/mouse_events.h"
    "event/window_events.h"

    "graphics/window.h"
    "graphics/generic/buffer.h"
    "graphics/generic/context.h"
    "graphics/generic/render_backend.h"

    "input/input.h"
    "input/key.h"
    "input/mouse_button.h"

    "layer/layer.h"
    "layer/layer_stack.h"

    "math/angle.h"
    "math/color.h"
    "math/linear_algebra.h"

    "utils/chrono.h"
    "utils/format.h"
    "utils/pimpl.h"
    "utils/virtual_base.h"
)
set(SOURCES
    # Source files here (relative to ./src/)
    "core/application.cpp"
    "core/error.cpp"
    "core/log.cpp"

    "event/key_events.cpp"
    "event/mouse_events.cpp"
    "event/window_events.cpp"
    
    "graphics/window.cpp"
    "graphics/generic/buffer.cpp"
    "graphics/generic/buffer_base.h"
    "graphics/generic/context.cpp"
    "graphics/generic/context_base.h"

    "input/key.cpp"
    "input/mouse_button.cpp"

    "layer/layer_stack.cpp"
)

if (WIN32)
    target_compile_definitions(phosphorus PUBLIC PHOSPHORUS_WINDOWS)
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(phosphorus PUBLIC PHOSPHORUS_LINUX)
endif ()

if (PHOSPHORUS_OPENGL)
    target_compile_definitions(phosphorus PUBLIC PHOSPHORUS_OPENGL)
    list(APPEND SOURCES
        "graphics/opengl/buffer.h"
        "graphics/opengl/buffer.cpp"
        "graphics/opengl/context.h"
        "graphics/opengl/context.cpp"
    )
endif ()

list(TRANSFORM HEADERS PREPEND "include/phosphorus/")
list(TRANSFORM SOURCES PREPEND "src/")

if (BUILD_SHARED_LIBS)
    target_compile_definitions(phosphorus
        PRIVATE PH_EXPORT_SHARED
        PUBLIC PH_BUILD_SHARED)
endif ()

find_package(clu CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_sources(phosphorus PRIVATE ${HEADERS} ${SOURCES})
target_set_options(phosphorus)

target_include_directories(phosphorus
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(phosphorus
PUBLIC
    clu::clu
    glm::glm
    spdlog::spdlog
    glfw glad::glad
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
