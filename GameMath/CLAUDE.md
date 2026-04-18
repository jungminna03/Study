# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Purpose

Personal study project for game math (vectors, transforms, collisions, etc.), implemented as a Siv3D visualization sandbox. Each topic is explored interactively by drawing on a centered grid and manipulating shapes with input.

## Build & Run

- Solution: `GameMath.slnx` (Visual Studio, x64 only — `Debug|x64` and `Release|x64`).
- Toolset: `v145`, language standard `stdcpplatest`, Unicode, `/Zc:__cplusplus`.
- Dependency: **Siv3D 0.6.16**, located via the `SIV3D_0_6_16` environment variable. Includes/libs are pulled from `$(SIV3D_0_6_16)\include` and `$(SIV3D_0_6_16)\lib\Windows`. If a build fails with missing `Siv3D.hpp`, this env var is the first thing to check.
- Build (CLI): `msbuild GameMath.slnx /p:Configuration=Debug /p:Platform=x64` (or `Release`).
- Run: launch from VS, or run the built exe from `GameMath/App/`. The post-build step xcopies the binary into `GameMath/App/`, and `LocalDebuggerWorkingDirectory` is set there so Siv3D can resolve assets.
- Output dirs: `Intermediate/GameMath/Debug/` and `Intermediate/GameMath/Release/`. Debug binary is named `GameMath(debug).exe`.

There are no tests, no linter, and no CI in this repo.

## Architecture

Single-TU app — all gameplay/math code lives in `GameMath/Main.cpp`.

- `stdafx.h` is the precompiled header and is **force-included** into every translation unit (`<ForcedIncludeFiles>stdafx.h</ForcedIncludeFiles>`). It does `# include <Siv3D.hpp>`, so `Main.cpp` does not need its own includes. New `.cpp` files must `#include "stdafx.h"` first or the PCH build will fail.
- `void Main()` is the Siv3D entry point (not `int main`). The frame loop is `while (System::Update()) { update(); draw(); }` — keep new per-frame logic split between those two free functions.
- `RenderGrid()` draws a unit grid centered on the scene with red/green axes; `unitSize = 20.0` pixels = 1 logical unit. Use this as the coordinate system when visualizing math (positions in the code are in scene pixels, divide by `unitSize` for logical units).
- Assets (fonts, shaders, examples, DLLs like `SoundTouch_x64.dll`) live under `GameMath/App/` and are loaded relative to the working directory at runtime.

## Conventions

- Commit message style observed in history: `[ADD] <topic>`, `[FIX] <what>`. Match this when committing.
- Siv3D is included with `using namespace s3d` implicitly enabled (`NO_S3D_USING` is commented out in `stdafx.h`), so types like `Circle`, `Line`, `Color`, `Scene`, `KeyRight` are used unqualified.
