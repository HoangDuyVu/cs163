# cmake_minimum_required(VERSION 3.10)
# project(SFMLProject)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Find the SFML library
# set(SFML_STATIC_LIBRARIES TRUE)
# set(SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML")
# find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

# # Add your source files here
# add_executable(main main.cpp)

# # Link your executable to SFML
# target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio opengl32)

cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 2.6.x)
# FetchContent_MakeAvailable(SFML)

# # Fetch SQLiteCpp
# FetchContent_Declare(
#     SQLiteCpp
#     GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
#     GIT_TAG 3.3.1
#     GIT_CONFIG "core.autocrlf=false")
# FetchContent_GetProperties(SQLiteCpp)
# if(NOT SQLiteCpp_POPULATED)
#     FetchContent_Populate(SQLiteCpp)
#     add_subdirectory(${sqlitecpp_SOURCE_DIR} ${sqlitecpp_BINARY_DIR})
# endif()

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)



# Fetch json
# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
# FetchContent_MakeAvailable(json)

file(GLOB SRCS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

add_executable(game ${SRCS})
target_link_libraries(game PRIVATE raylib)
if (UNIX)
    target_link_libraries(game PRIVATE pthread dl)
endif()
target_compile_features(game PRIVATE cxx_std_17)

target_include_directories(game PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif()

install(TARGETS game)

# cmake -S. -Bbuild -G "MinGW Makefiles"
# cmake --build build
# cmake --build build --verbose
