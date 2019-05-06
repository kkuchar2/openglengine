cmake_minimum_required(VERSION 3.9)
project(opengl)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_CXX_STANDARD 17)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()


file (GLOB_RECURSE RESOURCE_FILES "resources/*.*")

foreach(resource ${resources})
    get_filename_component(filename ${resource} NAME)
    get_filename_component(dir ${resource} DIRECTORY)
    get_filename_component(dirname ${dir} NAME)

    set (output "")

    while(NOT ${dirname} STREQUAL resources)
        get_filename_component(path_component ${dir} NAME)
        set (output "${path_component}/${output}")
        get_filename_component(dir ${dir} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)
    endwhile()

    set(output "${CMAKE_CURRENT_BINARY_DIR}/resources/${output}/${filename}")

    add_custom_command(
            COMMENT "Moving updated resource-file '${filename}'"
            OUTPUT ${output}
            DEPENDS ${resource}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${resource}
            ${output}
    )
    add_custom_target(${filename} ALL DEPENDS ${resource} ${output})

endforeach()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INCLUDE_NONE OFF CACHE BOOL "" FORCE)

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)

option(BUILD_STATIC_LIB ON)





message("${Cyan}Configuring glfw${ColourReset}")

add_subdirectory(dependencies/glfw)

message("${Cyan}Configuring glm${ColourReset}")

option(GLM_TEST_ENABLE "Build unit tests" OFF)

add_subdirectory(dependencies/glm)

message("${Cyan}Configuring RoseCpp${ColourReset}")

add_subdirectory(dependencies/RoseCpp)

message("${Cyan}Configuring bullet3${ColourReset}")

option(BUILD_SHARED_LIBS ON)
option(BUILD_UNIT_TESTS OFF)
option(USE_GRAPHICAL_BENCHMARK OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_ENET OFF)
option(BUILD_CLSOCKET OFF)
option(BUILD_BULLET3 OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_BULLET2_DEMOS OFF)

add_subdirectory(dependencies/bullet3)

include_directories(dependencies)
include_directories(dependencies/glfw)
include_directories(dependencies/glfw/deps)
include_directories(dependencies/glfw/include)
include_directories(dependencies/glm)
include_directories(dependencies/bullet3/src)
include_directories(dependencies/RoseCpp/src)
include_directories(dependencies/freetype2/include)
include_directories(dependencies/glad/include/glad)
include_directories(dependencies/glad/include/KHR)

include_directories(dependencies)

include_directories(src)
include_directories(src/Engine/EngineInternal)
include_directories(src/Engine/EngineInternal/Utils)
include_directories(src/Engine/EngineInternal/Rendering)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE IMGUI_SRC_FILES dependencies/imgui/*.cpp)

set(SOURCE_FILES ${SRC_FILES} ${IMGUI_SRC_FILES})

set(GLAD "dependencies/glad/include/glad/glad.h" "dependencies/glad/src/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h" "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h" "${GLFW_SOURCE_DIR}/deps/tinycthread.c")
set(TINYOBJ "dependencies/tinyobj/tiny_obj_loader.h" "dependencies/tinyobj/tiny_obj_loader.cpp" src/Engine/EngineInternal/Rendering/Mesh/MeshRenderer.cpp src/Engine/EngineInternal/Rendering/Mesh/MeshRenderer.h src/Engine/EngineInternal/Rendering/Mesh/TriangleInfo.h src/Engine/EngineInternal/Rendering/Mesh/BoundingBox.h)

add_executable(opengl ${SOURCE_FILES} ${TINYOBJ} ${TINYCTHREAD} ${GETOPT} ${GLAD})

target_link_libraries(opengl
        glfw
        freetype
        Bullet3Common
        BulletDynamics
        BulletCollision
        LinearMath
)
