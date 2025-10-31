# OSPSuite.SimModelNative.Tests

This project contains pure C++ unit tests for the OSPSuite.SimModelNative library using the Google Test framework.

## Purpose

The tests in this project test the C++ functionality directly without relying on C# interop, providing:
- Faster test execution
- More granular testing of C++ classes and functions
- Better coverage of edge cases
- Platform-specific behavior validation

## Test Framework

This project uses [Google Test (gtest)](https://github.com/google/googletest) version 1.14.0, which is:
- Cross-platform (Windows, Linux, macOS)
- Industry standard for C++ testing
- Well-documented and widely supported
- Easy to integrate with CI/CD pipelines

## Building and Running Tests

### Windows

The tests are built automatically as part of the main solution build:

```batch
msbuild OSPSuite.SimModel.sln -t:build -restore /property:Configuration=Release;Platform=x64
```

To run the tests:

```batch
Build\Release\x64\Tests\OSPSuite.SimModelNative.Tests.exe
```

Or run the full build script which includes tests:

```batch
buildWindows.bat
```

### Linux / macOS

The tests are built using CMake:

```bash
# Build process is integrated in buildNix.sh
./buildNix.sh Ubuntu22 4.0.0.1
```

Or manually:

```bash
cmake -BBuild/Release/x64/Tests/ -Htests/OSPSuite.SimModelNative.Tests/ -DCMAKE_BUILD_TYPE=Release -DFuncParserDir=Build/Release/x64/ -DEXT=so
make -C Build/Release/x64/Tests/
./Build/Release/x64/Tests/OSPSuite.SimModelNative.Tests
```

## Test Coverage

Current test coverage includes:

### Core Utilities
- **MathHelper**: NaN/Inf handling, numeric validation, distribution functions
- **ValuePoint**: Construction, copying, field validation

### Data Structures
- **TObjectVector**: Dynamic array operations, memory management
- **TObjectList**: ID-based lookups, entity management (planned)

### Formulas
- **ConstantFormula**: Value operations, differentiation, cloning
- **MinFormula, MaxFormula**: Basic construction (planned for expansion)
- **DivFormula, DiffFormula**: Basic construction (planned for expansion)

## Adding New Tests

To add new test files:

1. Create a new `.cpp` file in the `src/` directory
2. Include necessary headers:
   ```cpp
   #include <gtest/gtest.h>
   #include "SimModel/YourClass.h"
   ```
3. Write test cases using Google Test macros:
   ```cpp
   TEST(TestSuiteName, TestName) {
       // Arrange
       YourClass obj;
       
       // Act
       auto result = obj.method();
       
       // Assert
       EXPECT_EQ(result, expectedValue);
   }
   ```
4. Add the file to `CMakeLists.txt` (for Unix) and `OSPSuite.SimModelNative.Tests.vcxproj` (for Windows)

## Test Execution

Tests can be run with various options:

```bash
# Run all tests
./OSPSuite.SimModelNative.Tests

# Run specific test suite
./OSPSuite.SimModelNative.Tests --gtest_filter=MathHelperTest.*

# Generate XML output
./OSPSuite.SimModelNative.Tests --gtest_output=xml:test_results.xml

# List all tests
./OSPSuite.SimModelNative.Tests --gtest_list_tests
```

## CI Integration

The tests are automatically run as part of the CI pipeline on:
- Windows (x64)
- Ubuntu 22.04 (x64, ARM64)
- macOS (x64, ARM64)

Test results are collected and published as artifacts.

## Dependencies

The test project depends on:
- OSPSuite.SimModelNative source files
- OSPSuite.SysTool
- OSPSuite.XMLWrapper
- OSPSuite.SimModelSolverBase
- Google Test framework (installed via NuGet on Windows, FetchContent on Unix)
- libxml2
- OSPSuite.FuncParserNative

## Notes

- Tests are compiled directly with the source files (not linking to a library) to allow for testing of internal functions
- Memory management is handled by the test framework's fixture cleanup
- Platform-specific tests should use conditional compilation directives
