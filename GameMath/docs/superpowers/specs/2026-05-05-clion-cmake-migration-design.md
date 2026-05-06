# CLion/CMake 빌드 시스템 이관

## 목적

기존 Visual Studio(.sln/.vcxproj) + Xcode(xcodegen project.yml) 이중 빌드 시스템을 단일 CMake 기반으로 교체해 Windows/macOS 양쪽에서 CLion으로 직접 열 수 있게 한다.

## 범위

- CLion 전용. VS, Xcode 워크플로우는 지원하지 않는다.
- Windows: MSVC(Build Tools v143+) 강제. Siv3D 0.6.16이 MSVC 빌드본만 제공하므로 MinGW는 비대상.
- macOS: AppleClang. Apple Silicon에서는 Rosetta 2로 동작 (Siv3D lib가 x86_64 only).

## 산출/삭제 파일

**신규**
- `CMakeLists.txt` (루트, 단일)
- `.gitignore` (루트, 신규)

**삭제**
- `GameMath.sln`, `GameMath.slnx`
- `GameMath/GameMath.vcxproj`, `GameMath/GameMath.vcxproj.filters`, `GameMath/GameMath.vcxproj.user`
- `GameMath-macOS/project.yml`
- `.vs/`, `Intermediate/` (작업 트리에서 제거; .gitignore에도 포함)

**유지**
- `GameMath/Main.cpp`, `GameMath/.editorconfig`
- `GameMath/App/` 전체 (engine/, example/, dll/, Resource.rc, icon.ico)
- `GameMath-macOS/Info.plist`, `GameMath-macOS/icon.icns` (CMake에서 .app 번들 생성에 재사용)
- `CLAUDE.md` (Build & Run 섹션 갱신)

## CMakeLists.txt 설계

루트 단일 파일. `cmake_minimum_required(VERSION 3.20)`, `project(GameMath CXX)`, `set(CMAKE_CXX_STANDARD 20)`, `set(CMAKE_CXX_STANDARD_REQUIRED ON)`.

소스: `add_executable(GameMath GameMath/Main.cpp)`. 플랫폼별 분기:

### Windows (MSVC)

- Siv3D 위치: `$ENV{SIV3D_0_6_16}`. 미설정 시 `message(FATAL_ERROR …)`로 안내.
- `target_include_directories`: `${SIV3D}/include`, `${SIV3D}/include/ThirdParty`
- `target_link_directories`: `${SIV3D}/lib/Windows` (Siv3D 헤더의 `#pragma comment(lib, ...)`이 의존 lib 자동 링크)
- 명시 링크: `Siv3D$<$<CONFIG:Debug>:_d>` (Debug에서 `Siv3D_d.lib`)
- 컴파일 옵션: `/std:c++latest /Zc:__cplusplus /utf-8 /MP /permissive- /W4 /wd26451 /wd26812`
- 정의: `_WINDOWS;UNICODE;_UNICODE;_ENABLE_EXTENDED_ALIGNED_STORAGE;_SILENCE_CXX20_CISO646_REMOVED_WARNING;_SILENCE_ALL_CXX23_DEPRECATION_WARNINGS;_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS`
- MSVC 런타임: `MultiThreaded$<$<CONFIG:Debug>:Debug>` (`CMAKE_MSVC_RUNTIME_LIBRARY` 사용; static CRT)
- Subsystem: WIN32 (`set_target_properties(... WIN32_EXECUTABLE TRUE)`) — Siv3D가 자체 entry point 제공
- DelayLoad: `/DELAYLOAD:advapi32.dll …` (vcxproj 항목 그대로 이식)
- 리소스: `target_sources(GameMath PRIVATE GameMath/App/Resource.rc)` + `set_source_files_properties(... PROPERTIES VS_TOOL_OVERRIDE "Manifest" …)` 대신 RC 컴파일러가 `GameMath/App/`을 working dir로 인식하도록 `target_include_directories`에 추가
- Debug exe 이름: `set_target_properties(GameMath PROPERTIES DEBUG_OUTPUT_NAME "GameMath(debug)")`
- 산출물 위치: CMake 기본 (`cmake-build-debug/`, `cmake-build-release/`). working dir은 README에 안내.

### macOS (AppleClang)

- `set(CMAKE_OSX_ARCHITECTURES x86_64)`, `set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15)`
- Siv3D 위치: `$ENV{HOME}/Siv3D`. 미설정/미존재 시 `message(FATAL_ERROR …)`.
- `add_executable(GameMath MACOSX_BUNDLE GameMath/Main.cpp)`
- 번들 속성: `MACOSX_BUNDLE_INFO_PLIST` → `GameMath-macOS/Info.plist`, `MACOSX_BUNDLE_BUNDLE_NAME GameMath`, `MACOSX_BUNDLE_GUI_IDENTIFIER com.nyxrux62.GameMath`
- 아이콘: `target_sources(GameMath PRIVATE GameMath-macOS/icon.icns)` + `set_source_files_properties(... PROPERTIES MACOSX_PACKAGE_LOCATION Resources)` + `MACOSX_BUNDLE_ICON_FILE icon.icns`
- include: `${SIV3D}/include`, `${SIV3D}/include/ThirdParty`
- lib search: `${SIV3D}/lib/macOS` 및 boost/freetype/harfbuzz/libgif/libjpeg-turbo/libogg/libpng/libtiff/libvorbis/libwebp/opencv/opus/zlib (project.yml 그대로 이식)
- 링크: project.yml의 `OTHER_LDFLAGS` 21개 lib + AudioToolbox/AVFoundation/CoreAudio/CoreMedia frameworks (`-framework` 형태)
- 컴파일 옵션: `-fvisibility=hidden`
- C++ 표준: `c++2a` (`set_target_properties(... CXX_STANDARD 20)`)
- 포스트 빌드: `add_custom_command(TARGET GameMath POST_BUILD …)`로 `GameMath/App/engine/`과 `GameMath/App/example/`을 `$<TARGET_BUNDLE_CONTENT_DIR>/Resources/`에 `rsync -a --delete`로 복사 (project.yml의 postBuildScripts 그대로 이식)

## .gitignore

```
# Build outputs
cmake-build-*/
build/
out/
Intermediate/

# IDEs
.idea/
.vs/
.vscode/

# macOS
.DS_Store

# Windows
*.user
```

## CLAUDE.md 갱신

`## Build & Run` 섹션 전체를 다음으로 교체:

- 도구: CLion 2024.x 이상 (Win/macOS 공통). CMake 자동 감지.
- 의존성: Siv3D 0.6.16 — Windows는 `SIV3D_0_6_16` env var, macOS는 `~/Siv3D` 설치 경로.
- Windows: VS Build Tools v143+ 설치 후 CLion Toolchain에서 Visual Studio amd64 선택. Run Configuration의 Working directory를 `$PROJECT_DIR$/GameMath/App`로 설정.
- macOS: Xcode Command Line Tools 설치. .app 번들이 자체 리소스를 포함하므로 working dir 설정 불요.
- 빌드: CLion Build, 또는 CLI `cmake -S . -B build && cmake --build build`.
- 산출물: `cmake-build-{debug,release}/` (CLion 기본) 또는 `build/` (CLI).
- 테스트/린터/CI 없음 (기존 그대로).

## 위험 / 고려사항

- **Resource.rc 처리:** RC 파일이 `Siv3D/Windows/Resource.hpp`를 include하고 상대경로로 `engine/...`, `icon.ico`를 참조. CMake에서 RC 컴파일러의 include path와 working directory를 `${CMAKE_SOURCE_DIR}/GameMath/App`로 잡아야 한다. CMake는 `set_source_files_properties(... INCLUDE_DIRECTORIES ...)` 사용 또는 글로벌 `CMAKE_RC_FLAGS`에 `/I` 추가.
- **Static CRT vs Siv3D lib:** Siv3D Windows lib는 `/MT` (Release) / `/MTd` (Debug)로 빌드됨. CMake 기본은 `/MD`이므로 명시적 `CMAKE_MSVC_RUNTIME_LIBRARY` 설정 필수. 안 맞으면 LNK2038.
- **macOS Apple Silicon:** `ARCHS=x86_64` 강제 → CLion이 자동으로 Rosetta로 실행. CLion CMake profile에서 architecture override 안 되면 `CMAKE_OSX_ARCHITECTURES`가 우선.
- **Siv3D 환경 변수 부재 시:** FATAL_ERROR 메시지로 사용자에게 명확히 안내.
- **검증:** Windows에서 `cmake -S . -B build -G "Visual Studio 17 2022" -A x64 && cmake --build build --config Debug` 실행 후 산출 .exe 실행 가능 여부 확인. macOS는 이 머신에서 검증 불가 → 사용자가 별도 검증 필요.
