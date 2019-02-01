cmake_minimum_required(VERSION 3.13)
project(opengl)

set(CMAKE_CXX_STANDARD 17)

#############################################################################################################
#############################################################################################################

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/Rose/RoseCpp)

include_directories(dependencies/glfw)
include_directories(dependencies/glfw/deps)
include_directories(dependencies/glfw/include)
include_directories(dependencies/glm)
include_directories(dependencies/Rose/RoseCpp/src)

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h" "${GLFW_SOURCE_DIR}/deps/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h" "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h" "${GLFW_SOURCE_DIR}/deps/tinycthread.c")


#############################################################################################################
#############################################################################################################

file(GLOB_RECURSE SRC_FILES src/*.cpp)
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

set(SOURCE_FILES ${SRC_FILES} src/MessageSystem/BusNode.h src/MessageSystem/Message.h src/MessageSystem/MessageBus.h src/InputSystem.h src/MessageSystem/CursorPositionMessage.h src/Engine/Engine.h src/Engine/EngineException.h)

add_executable(opengl ${SOURCE_FILES} ${TINYCTHREAD} ${GETOPT} ${GLAD})

target_link_libraries(opengl glfw)
