cmake_minimum_required(VERSION 3.5.0)
set(PROJ_NAME AlgoVis)
project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJ_NAME} src/main.cpp src/Renderer.cpp src/Sort.cpp)
target_link_libraries(${PROJ_NAME} PRIVATE sfml-window sfml-graphics)
target_include_directories(${PROJ_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(${PROJ_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJ_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJ_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJ_NAME})