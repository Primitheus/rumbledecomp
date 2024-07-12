cmake_minimum_required(VERSION 3.15)

project(rumblefighter CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0091 NEW)

include(CheckCXXSourceCompiles)
include(CMakeDependentOption)
include(CMakePushCheckState)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit Rumble Fighter")
if (NOT bits EQUAL 32)
  set(CMAKE_GENERATOR_PLATFORM Win32)
endif()

cmake_dependent_option(RUMBLEFIGHTER_USE_DX9_LIBS "Build with internal DirectX 9 SDK Libraries" ON RF_USE_DX9 OFF)

add_library(DirectX9::DirectX9 INTERFACE IMPORTED)
target_include_directories(DirectX9::DirectX9 INTERFACE "${CMAKE_SOURCE_DIR}/3rdparty/dx9/inc")
if(RUMBLEFIGHTER_USE_DX9_LIBS)
    target_link_directories(DirectX9::DirectX9 INTERFACE "${CMAKE_SOURCE_DIR}/3rdparty/dx9/lib")
endif()

add_executable(rumblefighter WIN32
  "rumblefighter/res/rumblefighter.rc"
  "rumblefighter/JamFighter.cpp"
)

add_executable(home WIN32
  "Home/home.cpp"
  "Home/res/home.rc"
)

add_executable(rumblelauncher WIN32
  "RumbleLauncher/launcher.cpp"
  "RumbleLauncher/res/launcher.rc"
)

target_compile_definitions(rumblefighter PRIVATE RUMBLEFIGHTER_APP)
target_compile_definitions(home PRIVATE HOME_APP)

# Use internal DirectX 5 if required
target_link_libraries(rumblefighter PRIVATE $<$<BOOL:${RF_USE_DX9}>:DirectX9::DirectX9>)

# Make sure filename is rumblefighter.exe
set_property(TARGET rumblefighter PROPERTY OUTPUT_NAME rumblefighter)
set_property(TARGET rumblefighter PROPERTY SUFFIX ".exe")

set_property(TARGET home PROPERTY OUTPUT_NAME Home)
set_property(TARGET home PROPERTY SUFFIX ".exe")

set_property(TARGET rumblelauncher PROPERTY OUTPUT_NAME RumbleLauncher)
set_property(TARGET rumblelauncher PROPERTY SUFFIX ".exe")

# Use a specific linker
set(CMAKE_LINKER "C:/Users/Primitheus/Desktop/Projects/PMSCV6/VC98/BIN/link.exe")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> /OUT:<TARGET> <LINK_LIBRARIES>")

# Print linker-related variables for debugging

message(STATUS "CMAKE_LINKER: ${CMAKE_LINKER}")
message(STATUS "FLAGS: ${FLAGS}")
message(STATUS "CMAKE_CXX_LINK_FLAGS: ${CMAKE_CXX_LINK_FLAGS}")
message(STATUS "LINK_FLAGS: ${LINK_FLAGS}")
message(STATUS "OBJECTS: ${OBJECTS}")
message(STATUS "LINK_LIBRARIES: ${LINK_LIBRARIES}")
message(STATUS "TARGET: ${TARGET}")
