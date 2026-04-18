# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Purpose

Personal study project for game math (vectors, transforms, collisions, etc.), implemented as a Siv3D visualization sandbox. Each topic is explored interactively by drawing on a centered grid and manipulating shapes with input.

## Build & Run

The project builds on both Windows (Visual Studio / MSBuild) and macOS (Xcode / xcodebuild) from the same `Main.cpp`.

### Windows

- Solution: `GameMath.slnx` (or the mirror `GameMath.sln`), x64 only — `Debug|x64` and `Release|x64`.
- Toolset: `v145`, language standard `stdcpplatest`, Unicode, `/Zc:__cplusplus`.
- Dependency: **Siv3D 0.6.16**, located via the `SIV3D_0_6_16` environment variable. Includes/libs are pulled from `$(SIV3D_0_6_16)\include` and `$(SIV3D_0_6_16)\lib\Windows`. If a build fails with missing `Siv3D.hpp`, this env var is the first thing to check.
- Build (CLI): `msbuild GameMath.sln /p:Configuration=Debug /p:Platform=x64` (or `Release`).
- Run: launch from VS, or run the built exe from `GameMath/App/`. The post-build step xcopies the binary into `GameMath/App/`, and `LocalDebuggerWorkingDirectory` is set there so Siv3D can resolve assets.
- Output dirs: `Intermediate/GameMath/Debug/` and `Intermediate/GameMath/Release/`. Debug binary is named `GameMath(debug).exe`.

### macOS

- Project: `GameMath-macOS/` — `project.yml` (xcodegen, committed) generates `GameMath.xcodeproj` (gitignored). Regenerate after edits: `cd GameMath-macOS && xcodegen generate`.
- Tool: [xcodegen](https://github.com/yonaskolb/XcodeGen) — `brew install xcodegen`.
- Dependency: Siv3D 0.6.16 macOS distribution at `$SIV3D_0_6_16_MACOS` (set in `~/.zshrc`, e.g. `$HOME/Siv3D`). Contains `include/`, `lib/macOS/`, `examples/`.
- Build (CLI): `xcodebuild -project GameMath-macOS/GameMath.xcodeproj -scheme GameMath -configuration Debug build`. The env var must be visible — if launching `xcodebuild` outside an interactive shell, pass it inline (`xcodebuild ... SIV3D_0_6_16_MACOS=$HOME/Siv3D build`).
- Output: `GameMath/App/GameMath.app` (via `CONFIGURATION_BUILD_DIR`). A post-build rsync copies `GameMath/App/engine/` and `GameMath/App/example/` into `GameMath.app/Contents/Resources/` so Siv3D can find its engine assets (shaders, fonts, soundfont) at runtime.
- Run: `open GameMath/App/GameMath.app`, or from Xcode/Rider.
- Target arch: `x86_64` only (Siv3D's shipped libs aren't fat). On Apple Silicon the app runs under Rosetta 2.
- Deployment target: macOS 10.15.
- C++ standard: `c++2a` (matches the Siv3D `empty` template baseline).

There are no tests, no linter, and no CI in this repo.

## Architecture

Single-TU app — all gameplay/math code lives in `GameMath/Main.cpp`.

- `Main.cpp` includes `<Siv3D.hpp>` directly on its first line. No precompiled header is used; both Windows and macOS builds compile the same source without any force-include. New `.cpp` files should `#include <Siv3D.hpp>` directly.
- `void Main()` is the Siv3D entry point (not `int main`). The frame loop is `while (System::Update()) { update(); draw(); }` — keep new per-frame logic split between those two free functions.
- `RenderGrid()` draws a unit grid centered on the scene with red/green axes; `unitSize = 20.0` pixels = 1 logical unit. Use this as the coordinate system when visualizing math (positions in the code are in scene pixels, divide by `unitSize` for logical units).
- Assets (fonts, shaders, examples, DLLs like `SoundTouch_x64.dll`) live under `GameMath/App/`. Windows reads them from CWD (working dir set by `LocalDebuggerWorkingDirectory`); macOS copies `engine/` and `example/` into the `.app` bundle's `Contents/Resources/` and Siv3D reads them from there.

## Conventions

- Commit message style observed in history: `[ADD] <topic>`, `[FIX] <what>`, `[REMOVE] <what>`, `[UPDATE] <what>`. Match this when committing.
- Siv3D is included with `using namespace s3d` implicitly enabled by `<Siv3D.hpp>`, so types like `Circle`, `Line`, `Color`, `Scene`, `KeyRight` are used unqualified.
