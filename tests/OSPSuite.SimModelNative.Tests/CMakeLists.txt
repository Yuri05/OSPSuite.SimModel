cmake_minimum_required (VERSION 3.9)
project (OSPSuite.SimModelNative.Tests)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    set(RPATH ".")
    list(APPEND CMAKE_BUILD_RPATH ${RPATH})
endif()

find_package(LibXml2 REQUIRED)

include_directories (
    ${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SimModelNative/include 
	${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SimModelSolverBase/src/OSPSuite.SimModelSolverBase/include 
	${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SysTool/include 
	${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.XMLWrapper/include 
	${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../packages/OSPSuite.FuncParser.Ubuntu22/OSPSuite.FuncParserNative/include
	${LIBXML2_INCLUDE_DIR}
)

# Collect source files from OSPSuite.SimModelNative and dependencies
file (GLOB SIMMODEL_SOURCES 
        ${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SimModelNative/src/*.cpp
		${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SimModelSolverBase/src/OSPSuite.SimModelSolverBase/src/*.cpp
		${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.SysTool/src/*.cpp
		${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../src/OSPSuite.XMLWrapper/src/*.cpp
)

# Collect test source files
file (GLOB TEST_SOURCES 
        ${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/src/*.cpp
)

add_executable (OSPSuite.SimModelNative.Tests ${TEST_SOURCES} ${SIMMODEL_SOURCES})

target_link_libraries (OSPSuite.SimModelNative.Tests 
    gtest_main
    ${OSPSuite.SimModelNative.Tests_SOURCE_DIR}/../../${FuncParserDir}libOSPSuite.FuncParserNative.${EXT}
	${LIBXML2_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(OSPSuite.SimModelNative.Tests)
