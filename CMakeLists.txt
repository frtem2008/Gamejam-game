cmake_minimum_required(VERSION 3.28)
project(GamejamProg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent REQUIRED)

set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TEST_SUITE OFF)
set(SFML_USE_SYSTEM_DEPS OFF)
set(SFML_USE_DRM OFF)

message(STATUS "Downloading SFML")
FetchContent_Declare(SFML SYSTEM
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
add_executable(${PROJECT_NAME} ${SOURCES} )

target_link_libraries(${PROJECT_NAME}
        PRIVATE sfml-graphics
        PRIVATE sfml-audio
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy
            -Wenum-compare -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
            -Wredundant-decls -Wsign-promo -Wsign-conversion
            -Wno-unused-variable -Wno-float-equal -Wno-unknown-pragmas -Wno-conversion -Wno-unused-parameter
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /wd4100 /wd4068)
endif ()

set(ADDITIONAL_INCLUDE_DIRS "src")
target_include_directories(${PROJECT_NAME} PRIVATE ${ADDITIONAL_INCLUDE_DIRS})

set(OUT_FILE_NAME ${PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUT_FILE_NAME})
