cmake_minimum_required(VERSION 3.9)
project(opengl)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_CXX_STANDARD 17)

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
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/RoseCpp)
add_subdirectory(dependencies/freetype2)

include_directories(dependencies)
include_directories(dependencies/glfw)
include_directories(dependencies/glfw/deps)
include_directories(dependencies/glfw/include)
include_directories(dependencies/glm)
include_directories(dependencies/RoseCpp/src)
include_directories(dependencies/freetype2/include)
include_directories(dependencies/glad/include/glad)
include_directories(dependencies/glad/include/KHR)

include_directories(src/Engine/EngineInternal)
include_directories(src/Engine/EngineInternal/Rendering)
include_directories(src)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE IMGUI_SRC_FILES dependencies/imgui/*.cpp)

set(SOURCE_FILES ${SRC_FILES} ${IMGUI_SRC_FILES})

set(GLAD "dependencies/glad/include/glad/glad.h" "dependencies/glad/src/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h" "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h" "${GLFW_SOURCE_DIR}/deps/tinycthread.c" src/Engine/EngineInternal/Rendering/Mesh/SurfacePrototype.h src/Engine/EngineInternal/Rendering/Mesh/MeshBuilder.h src/Engine/EngineInternal/Utils/Objects.h src/Engine/EngineInternal/Rendering/GameObject/GameObjectBase.h src/Engine/EngineInternal/Rendering/GameObject/GameObjectBase.cpp src/Engine/EngineInternal/Rendering/Primitives/LinePrototype.h src/Engine/EngineInternal/Behaviour/RotatingBehaviour.h src/Scenes/OrthoScene.h src/Engine/EngineInternal/Utils/stb_image.h src/Engine/EngineInternal/Utils/TextureLoader.cpp src/Engine/EngineInternal/Rendering/Primitives/SkyboxPrototype.h src/Engine/EngineInternal/Rendering/Renderer/MeshInfo.h src/Engine/EngineInternal/Rendering/Primitives/Point.h src/Engine/EngineInternal/Utils/FastMath.h)

add_executable(opengl ${SOURCE_FILES} ${TINYCTHREAD} ${GETOPT} ${GLAD})

target_link_libraries(opengl glfw freetype)
