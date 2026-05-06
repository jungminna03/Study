# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Purpose

Personal study project for game math (vectors, transforms, collisions, etc.), implemented as a Siv3D visualization sandbox. Each topic is explored interactively by drawing on a centered grid and manipulating shapes with input.

## Build & Run

Single root `CMakeLists.txt` drives both platforms. Open the repo root in **CLion** — it picks up the CMake project automatically. C++ standard is `c++23` everywhere (Siv3D 0.6.16 headers use `std::byteswap`).

### Windows

- Toolchain: **MSVC** (Build Tools v143+ / MSVC 14.50+ from VS 2022 or 2026). MinGW is not supported — Siv3D 0.6.16 ships only MSVC libs. In CLion: Settings → Build, Execution, Deployment → Toolchains → add **Visual Studio (amd64)**.
- Dependency: **Siv3D 0.6.16**, located via the `SIV3D_0_6_16` environment variable (e.g. `C:\…\OpenSiv3D_0.6.16`). The CMake configure step errors out if it isn't set. Headers come from `%SIV3D_0_6_16%\include` (+ `\include\ThirdParty`) and libs from `%SIV3D_0_6_16%\lib\Windows`.
- Linking: `Siv3D.lib` / `Siv3D_d.lib` is named explicitly; transitive third-party libs are pulled in via `#pragma comment(lib, ...)` inside Siv3D headers. `delayimp` is linked because the build uses `/DELAYLOAD` for system DLLs.
- Run: set the Run Configuration's **Working directory** to `$PROJECT_DIR$/GameMath/App` so Siv3D can resolve its assets. Debug binary name is `GameMath(debug).exe`; Release is `GameMath.exe`.
- Output: CLion default (`cmake-build-debug/` etc.). No post-build copy into `GameMath/App/`.

### macOS

- Toolchain: **AppleClang** (Xcode Command Line Tools).
- Dependency: **Siv3D 0.6.16** installed at `~/Siv3D`. The CMake configure step errors if `~/Siv3D/include/Siv3D.hpp` is missing.
- Build target: a `MACOSX_BUNDLE` (`GameMath.app`). `Info.plist` and `icon.icns` are sourced from `GameMath-macOS/`.
- Architecture: `x86_64` only (Siv3D's shipped libs aren't fat). On Apple Silicon the app runs under Rosetta 2. Deployment target: macOS 10.15.
- A post-build step `rsync`s `GameMath/App/engine/` and `GameMath/App/example/` into `GameMath.app/Contents/Resources/`. Working directory doesn't matter — the bundle is self-contained.

### CLI build (either platform)

```sh
cmake -S . -B build
cmake --build build --config Debug   # or Release
```

On Windows the configure must run inside an MSVC Developer Command Prompt (or after `vcvars64.bat`).

There are no tests, no linter, and no CI in this repo.

## Architecture

Single-TU app — all gameplay/math code lives in `GameMath/Main.cpp`.

- `Main.cpp` includes `<Siv3D.hpp>` directly on its first line. No precompiled header is used; both Windows and macOS builds compile the same source without any force-include. New `.cpp` files should `#include <Siv3D.hpp>` directly. If you add new sources, list them in `CMakeLists.txt` (the `GAMEMATH_SOURCES` variable).
- `void Main()` is the Siv3D entry point (not `int main`). The frame loop is `while (System::Update()) { update(); draw(); }` — keep new per-frame logic split between those two free functions.
- `RenderGrid()` draws a unit grid centered on the scene with red/green axes; `unitSize = 20.0` pixels = 1 logical unit. Use this as the coordinate system when visualizing math (positions in the code are in scene pixels, divide by `unitSize` for logical units).
- Assets (fonts, shaders, examples, DLLs like `SoundTouch_x64.dll`) live under `GameMath/App/`. Windows reads them from CWD (Run Configuration working directory must point at `GameMath/App`); macOS copies `engine/` and `example/` into the `.app` bundle's `Contents/Resources/` via a CMake post-build step.
- `GameMath/App/Resource.rc` (+ `icon.ico`) embeds Siv3D engine resources into the Windows `.exe`. The RC compiler resolves `Resource(engine/...)` paths via `target_include_directories` pointing at `GameMath/App/`.

## Conventions

- Commit message style observed in history: `[ADD] <topic>`, `[FIX] <what>`, `[REMOVE] <what>`, `[UPDATE] <what>`. Match this when committing.
- Siv3D is included with `using namespace s3d` implicitly enabled by `<Siv3D.hpp>`, so types like `Circle`, `Line`, `Color`, `Scene`, `KeyRight` are used unqualified.
