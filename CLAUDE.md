# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

OSPSuite.SimModel is the ODE-based calculation engine for PK/PD models built with PK-Sim or MoBi (Open Systems Pharmacology). It consists of a C++ native simulation kernel wrapped by a .NET managed layer via P/Invoke, packaged as a unified multi-platform NuGet package.

## Build Commands

### Windows (primary development platform)

```bash
# 1. Restore native NuGet packages (required before first C++ build)
nuget restore packages.config -PackagesDirectory packages

# 2. Build the C++ native library (use VS Developer Command Prompt or ensure msbuild is on PATH)
msbuild src/OSPSuite.SimModelNative/OSPSuite.SimModelNative.vcxproj /p:Configuration=Release /p:Platform=x64 "/p:SolutionDir=$(pwd)/"

# 3. Build the .NET managed layer and tests
dotnet build OSPSuite.SimModel.sln --configuration Release
```

The C++ vcxproj projects require MSBuild (not `dotnet build`). The .NET projects can be built with `dotnet build`. CI creates a `.NetOnly.sln` (with C++ projects removed) for the managed build step.

### Linux / macOS

```bash
./buildNix.sh Linux    # or MacOS
```

This runs CMake + make for the native library, then `dotnet build` and `dotnet test` for the managed layer.

### Running Tests

```bash
# .NET tests (NUnit, BDD-style)
dotnet test tests/OSPSuite.SimModel.Tests/OSPSuite.SimModel.Tests.csproj --configuration Release

# C++ unit tests (Google Test) — requires SimModelNative to be built first
msbuild tests/OSPSuite.SimModelNative.Tests/OSPSuite.SimModelNative.Tests.vcxproj /p:Configuration=Release /p:Platform=x64 "/p:SolutionDir=$(pwd)/"
Build/Release/x64/OSPSuite.SimModelNative.Tests.exe
```

## Architecture

### Native C++ Layer (`src/OSPSuite.SimModelNative/`)

Headers in `include/SimModel/`, sources in `src/`. Namespace: `SimModelNative`.

Core classes:
- **`Simulation`** — orchestrates loading XML, managing entities, running the ODE solver, collecting results
- **`DESolver`** — wraps CVODES (Adams/BDF methods, sensitivity analysis, band linear solver)
- **Formula hierarchy** — `Formula` base with ~20 subtypes (`ExplicitFormula`, `TableFormula`, `IfFormula`, etc.) loaded from XML `FormulaList`
- **`Species`** (ODE state variables), **`Parameter`**, **`Observer`** (computed outputs), **`Switch`** (events)
- **`PInvokeSimulation.h`** / **`PInvokeQuantity.h`** — flat `extern "C"` API exported for .NET interop

Platform abstraction:
- `OSPSuite.SysTool` — dynamic library loading, file system helpers
- `OSPSuite.XMLWrapper` — MSXML6 on Windows, libxml2 on Linux/macOS
- `SIM_EXPORT` macro: `__declspec(dllexport)` on Windows, empty elsewhere

### .NET Managed Layer (`src/OSPSuite.SimModel/`)

Target: **net10.0**. All P/Invoke uses `CallingConvention.Cdecl`.

- **`Simulation.cs`** — main public API. Lifecycle: `LoadFromXMLFile`/`LoadFromXMLString` → set variable parameters/species → `FinalizeSimulation` → `RunSimulation` → read results
- **`NativeLibraryPreload.cs`** — `[ModuleInitializer]` that preloads transitive native dependencies (`FuncParserNative`, `SimModelSolver_CVODES`) via `NativeLibrary.Load`
- **`SimModelImportDefinitions.cs`** — DLL name constant for `[DllImport]`

### Key Dependencies

- **OSPSuite.SimModelSolver_CVODES** — SUNDIALS CVODES ODE solver (native + managed wrapper)
- **OSPSuite.FuncParser** — mathematical formula parser (native + managed wrapper)
- **OSPSuite.Utility** — shared .NET utilities

Git submodules (clone with `--recursive`):
- `src/OSPSuite.SimModelSolverBase` — abstract solver interface (`ISolverCaller`)
- `schema/` — XSD schema for SimModel XML format

### Build Output Layout

Native binaries go to `Build/<Configuration>/x64/` on Windows, or `runtimes/<rid>/native/` for NuGet packaging. The unified nupkg includes native binaries for win-x64, linux-x64, and osx-arm64.

### Test Conventions

- **.NET tests** use `OSPSuite.BDDHelper` with `ContextSpecification<T>` pattern. Test classes inherit from `concern_for_Simulation` and follow the `Because`/`should_*` naming convention. XML test fixtures live in `tests/TestData/`.
- **C++ unit tests** (`tests/OSPSuite.SimModelNative.Tests/`) use Google Test. The test project compiles all SimModelNative sources directly (not linking against the DLL) so that non-exported internal classes can be tested. Uses NuGet package `Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn`.

## Version Management

Version is defined in `src/OSPSuite.SimModelNative/version.h` with placeholder values (0.0.0.0). CI replaces these with the actual version (currently `5.0.0.<build_number>`).

## Important Notes

- macOS Intel (x86_64) support was dropped; only arm64 is supported
- The `ProduceReferenceAssembly` is disabled in the .NET csproj to avoid a race condition in mixed C++/C# parallel builds (see comment in csproj)
- Native NuGet packages (from `packages.config`) are separate from .NET NuGet packages and must be restored with `nuget restore`, not `dotnet restore`
