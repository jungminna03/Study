# macOS Build Support Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `GameMath` buildable and runnable on macOS alongside the existing Windows build, sharing a single `Main.cpp`.

**Architecture:** Remove the MSVC PCH so both platforms use identical source. Add a new `GameMath-macOS/` folder with an `xcodegen`-managed Xcode project that references the shared `Main.cpp`, links Siv3D static libs from `$SIV3D_0_6_16_MACOS`, and builds the `.app` directly into `GameMath/App/` (matching Siv3D's `empty` template, so runtime asset paths resolve).

**Tech Stack:** Siv3D 0.6.16 (macOS distro at `~/Siv3D`), Xcode toolchain, xcodegen (Homebrew), clang C++20, MSVC v145 (Windows, unchanged).

**Spec:** `docs/superpowers/specs/2026-04-18-macos-build-design.md`

---

## File Inventory

| Path | Action |
|---|---|
| `GameMath/Main.cpp` | No change (already has `# include <Siv3D.hpp>`) |
| `GameMath/stdafx.h` | Delete |
| `GameMath/stdafx.cpp` | Delete |
| `GameMath/GameMath.vcxproj` | Remove PCH/ForcedInclude/stdafx refs |
| `GameMath/GameMath.vcxproj.filters` | Remove stdafx entries |
| `GameMath-macOS/project.yml` | Create (xcodegen spec) |
| `GameMath-macOS/Info.plist` | Create (copied from empty template, edited) |
| `GameMath-macOS/icon.icns` | Create (copied from empty template) |
| `.gitignore` | Create (root-level) with macOS/Xcode entries |
| `CLAUDE.md` | Update PCH section, add macOS build section |

---

## Task 1: Install xcodegen

**Files:** none (tool install)

- [ ] **Step 1.1: Check if xcodegen is already installed**

Run:
```bash
which xcodegen && xcodegen --version
```

Expected: either a version prints (e.g. `Version: 2.x.x`) → skip to Task 2, or `xcodegen not found` → continue.

- [ ] **Step 1.2: Install via Homebrew**

Run:
```bash
brew install xcodegen
```

Expected: Homebrew downloads and installs. Finishes with `🍺  /opt/homebrew/Cellar/xcodegen/...`.

- [ ] **Step 1.3: Verify**

Run:
```bash
xcodegen --version
```

Expected: prints a version number.

---

## Task 2: Remove PCH from Windows build

Siv3D's macOS Xcode template has no force-include mechanism. Dropping the PCH on Windows makes the source identical across platforms.

**Files:**
- Delete: `GameMath/stdafx.h`
- Delete: `GameMath/stdafx.cpp`
- Modify: `GameMath/GameMath.vcxproj`
- Modify: `GameMath/GameMath.vcxproj.filters`

- [ ] **Step 2.1: Delete stdafx files**

Run:
```bash
rm GameMath/stdafx.h GameMath/stdafx.cpp
```

Expected: no output, files gone.

- [ ] **Step 2.2: Remove `<PrecompiledHeader>Use</PrecompiledHeader>` and `<ForcedIncludeFiles>` from Debug `ClCompile` item-definition in `GameMath/GameMath.vcxproj`**

Edit `GameMath/GameMath.vcxproj`. Inside the Debug `ItemDefinitionGroup` (starts around `<ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">`), find the `<ClCompile>` block and delete these two lines:

```xml
      <PrecompiledHeader>Use</PrecompiledHeader>
      <ForcedIncludeFiles>stdafx.h;%(ForcedIncludeFiles)</ForcedIncludeFiles>
```

- [ ] **Step 2.3: Same removal from the Release `ItemDefinitionGroup`**

In the `<ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">` section, delete the same two lines:

```xml
      <PrecompiledHeader>Use</PrecompiledHeader>
      <ForcedIncludeFiles>stdafx.h;%(ForcedIncludeFiles)</ForcedIncludeFiles>
```

- [ ] **Step 2.4: Remove the `stdafx.cpp` compile entry**

In `GameMath/GameMath.vcxproj`, delete this entire block:

```xml
    <ClCompile Include="stdafx.cpp">
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Release|x64'">Create</PrecompiledHeader>
    </ClCompile>
```

The surrounding `<ItemGroup>` should now contain only the `Main.cpp` entry. Keep the `<ItemGroup>` itself.

- [ ] **Step 2.5: Remove the `stdafx.h` ClInclude entry**

In `GameMath/GameMath.vcxproj`, delete the entire `<ItemGroup>` block containing:

```xml
  <ItemGroup>
    <ClInclude Include="stdafx.h" />
  </ItemGroup>
```

- [ ] **Step 2.6: Remove stdafx references from `GameMath/GameMath.vcxproj.filters`**

In `GameMath/GameMath.vcxproj.filters`, delete this block:

```xml
    <ClCompile Include="stdafx.cpp">
      <Filter>Source Files</Filter>
    </ClCompile>
```

And this entire `<ItemGroup>`:

```xml
  <ItemGroup>
    <ClInclude Include="stdafx.h">
      <Filter>Header Files</Filter>
    </ClInclude>
  </ItemGroup>
```

- [ ] **Step 2.7: Sanity-check — grep for leftover stdafx references**

Run:
```bash
grep -l stdafx GameMath/*.vcxproj GameMath/*.filters GameMath/*.cpp GameMath/*.h 2>/dev/null
```

Expected: no output. If anything matches, remove remaining references.

- [ ] **Step 2.8: Commit**

```bash
git add -A GameMath/
git commit -m "[REMOVE] PCH (stdafx) for cross-platform source parity

Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
```

- [ ] **Step 2.9: (USER, on Windows) Verify Windows build still succeeds**

User runs on Windows after pulling:
```
msbuild GameMath.sln /p:Configuration=Debug /p:Platform=x64
```

Expected: build succeeds, `GameMath/App/GameMath(debug).exe` produced, program runs as before. If it fails, user reports error; we investigate before continuing.

This step is manual because we have no Windows environment here. Assume success and proceed — revert path is a single `git revert`.

---

## Task 3: Create GameMath-macOS scaffold

**Files:**
- Create: `GameMath-macOS/Info.plist`
- Create: `GameMath-macOS/icon.icns`
- Create: `GameMath-macOS/project.yml`

- [ ] **Step 3.1: Create the directory**

Run:
```bash
mkdir -p GameMath-macOS
```

- [ ] **Step 3.2: Copy `Info.plist` and `icon.icns` from Siv3D empty template**

Run:
```bash
cp ~/Siv3D/examples/empty/Info.plist GameMath-macOS/Info.plist
cp ~/Siv3D/examples/empty/icon.icns GameMath-macOS/icon.icns
```

Verify:
```bash
ls GameMath-macOS/
```

Expected: `Info.plist` and `icon.icns` present.

- [ ] **Step 3.3: Update `Info.plist` — change `CFBundleExecutable` and `CFBundleName` from `empty` to `GameMath`**

Open `GameMath-macOS/Info.plist`. Replace any occurrence of `empty` with `GameMath` in the `CFBundleExecutable` and `CFBundleName` values. If `CFBundleName` uses `$(PRODUCT_NAME)` or similar, leave it — it resolves at build time. Only hard-coded `empty` strings need replacement.

Quick check command:
```bash
grep -n "empty" GameMath-macOS/Info.plist
```

If matches appear, edit by hand or with `sed -i '' 's/empty/GameMath/g' GameMath-macOS/Info.plist` (macOS sed syntax). Then re-grep to confirm no matches.

- [ ] **Step 3.4: Write `GameMath-macOS/project.yml`**

Create `GameMath-macOS/project.yml` with exactly this content:

```yaml
name: GameMath
options:
  bundleIdPrefix: com.nyxrux62
  createIntermediateGroups: true
  deploymentTarget:
    macOS: "10.15"

settings:
  base:
    ALWAYS_SEARCH_USER_PATHS: NO
    ARCHS: x86_64
    CLANG_CXX_LANGUAGE_STANDARD: "c++2a"
    CLANG_CXX_LIBRARY: "libc++"
    CLANG_ENABLE_OBJC_ARC: YES
    CODE_SIGN_IDENTITY: "-"
    COMBINE_HIDPI_IMAGES: YES
    GCC_C_LANGUAGE_STANDARD: gnu99
    ONLY_ACTIVE_ARCH: YES
    SDKROOT: macosx
    LD_RUNPATH_SEARCH_PATHS:
      - $(inherited)
      - "@executable_path/../Frameworks"
    HEADER_SEARCH_PATHS:
      - $(SIV3D_0_6_16_MACOS)/include
      - $(SIV3D_0_6_16_MACOS)/include/ThirdParty
    LIBRARY_SEARCH_PATHS:
      - $(SIV3D_0_6_16_MACOS)/lib/macOS
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/boost
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/freetype
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/harfbuzz
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libgif
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libjpeg-turbo
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libogg
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libpng
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libtiff
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libvorbis
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/libwebp
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/opencv
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/opus
      - $(SIV3D_0_6_16_MACOS)/lib/macOS/zlib
    OTHER_CPLUSPLUSFLAGS:
      - $(OTHER_CFLAGS)
      - -fvisibility=hidden

  configs:
    Debug:
      GCC_OPTIMIZATION_LEVEL: "0"
      GCC_PREPROCESSOR_DEFINITIONS:
        - DEBUG=1
        - $(inherited)
      DEBUG_INFORMATION_FORMAT: dwarf
      MTL_ENABLE_DEBUG_INFO: YES
      ENABLE_TESTABILITY: YES
    Release:
      DEBUG_INFORMATION_FORMAT: "dwarf-with-dsym"
      ENABLE_NS_ASSERTIONS: NO
      MTL_ENABLE_DEBUG_INFO: NO

targets:
  GameMath:
    type: application
    platform: macOS
    sources:
      - path: ../GameMath/Main.cpp
    info:
      path: Info.plist
    settings:
      base:
        PRODUCT_NAME: GameMath
        PRODUCT_BUNDLE_IDENTIFIER: com.nyxrux62.GameMath
        INFOPLIST_FILE: Info.plist
        CONFIGURATION_BUILD_DIR: $(SRCROOT)/../GameMath/App
        OTHER_LDFLAGS:
          - -lSiv3D
          - -lboost_filesystem
          - -lopusfile
          - -lopus
          - -lzlib
          - -ltiff
          - -lopencv_imgcodecs
          - -lopencv_objdetect
          - -lopencv_imgproc
          - -lopencv_core
          - -lopencv_photo
          - -lopencv_videoio
          - -lwebp
          - -lvorbisfile
          - -lvorbisenc
          - -lvorbis
          - -lharfbuzz
          - -lfreetype
          - -lpng16
          - -logg
          - -lturbojpeg
          - -llibgif
          - -lcurl
    dependencies:
      - sdk: AudioToolbox.framework
      - sdk: AVFoundation.framework
      - sdk: CoreAudio.framework
      - sdk: CoreMedia.framework
```

Verify the file exists:
```bash
ls GameMath-macOS/
```

Expected: `Info.plist`, `icon.icns`, `project.yml`.

---

## Task 4: Generate Xcode project and first build

**Files:**
- Create (generated, gitignored): `GameMath-macOS/GameMath.xcodeproj/`
- Build artifact: `GameMath/App/GameMath.app` (not committed)

- [ ] **Step 4.1: Ensure `SIV3D_0_6_16_MACOS` env var is available in current shell**

Run:
```bash
echo "$SIV3D_0_6_16_MACOS"
```

Expected: `/Users/nyxrux62/Siv3D` (or similar). If empty, run `source ~/.zshrc` first.

- [ ] **Step 4.2: Generate the Xcode project**

Run:
```bash
cd GameMath-macOS && xcodegen generate && cd ..
```

Expected output ends with: `Generated project to: .../GameMath-macOS/GameMath.xcodeproj`. If xcodegen complains about YAML syntax, fix `project.yml` inline and retry.

- [ ] **Step 4.3: First build via xcodebuild**

Run:
```bash
xcodebuild -project GameMath-macOS/GameMath.xcodeproj \
           -scheme GameMath \
           -configuration Debug \
           build
```

Expected final line: `** BUILD SUCCEEDED **`.

- [ ] **Step 4.4: If BUILD FAILED with "Library not found for -lX" or "framework not found"**

This is the most likely failure. Inspect the error line to identify which `-l` flag doesn't match a file on disk.

Run:
```bash
ls ~/Siv3D/lib/macOS/
ls ~/Siv3D/lib/macOS/*/
```

Compare against the `OTHER_LDFLAGS` list in `project.yml`. Typical fixes:
- Flag is `-lzlib` but file is `libz.a` → change flag to `-lz`.
- Flag is `-llibgif` but file is `libgif.a` → change flag to `-lgif`.
- A subdirectory is missing from `LIBRARY_SEARCH_PATHS`.

Edit `project.yml`, re-run `xcodegen generate`, re-run `xcodebuild build`. Loop until `BUILD SUCCEEDED`.

- [ ] **Step 4.5: If BUILD FAILED with undefined symbols**

Likely a missing framework. Inspect `Undefined symbols for architecture x86_64` — look at the symbol names:
- `_OBJC_CLASS_$_NSView`, `_NSApp`, etc. → add `- sdk: AppKit.framework` to `dependencies`.
- `_glClear`, `_glBegin` → add `- sdk: OpenGL.framework`.
- `_MTLCreateSystemDefaultDevice` → add `- sdk: Metal.framework`.
- `_CGColorSpaceCreateDeviceRGB` → add `- sdk: CoreGraphics.framework`.

Edit `project.yml`, re-run `xcodegen generate`, re-run `xcodebuild build`. Loop.

- [ ] **Step 4.6: Verify the .app is produced in the shared App/ folder**

Run:
```bash
ls -la GameMath/App/GameMath.app/
```

Expected: directory listing with `Contents/` inside. If it's somewhere else (e.g. `DerivedData`), `CONFIGURATION_BUILD_DIR` in `project.yml` is wrong — fix and rebuild.

---

## Task 5: Launch and visually verify

- [ ] **Step 5.1: Launch the app**

Run:
```bash
open GameMath/App/GameMath.app
```

Expected: window titled "GameMath" or similar opens.

- [ ] **Step 5.2: Verify the visual**

Look at the window. Expected:
- Scene-centered grid of thin gray lines spaced every 20 pixels.
- One green vertical axis and one red horizontal axis through the center.
- A ball (Circle) visible somewhere on the grid.
- Pressing the arrow keys (Left/Right/Up/Down) moves the ball.

If the window is blank or crashes immediately, check for a Siv3D runtime error — usually asset path related. Run from terminal to see stderr:
```bash
GameMath/App/GameMath.app/Contents/MacOS/GameMath
```

Asset-path errors indicate CWD isn't `GameMath/App/`. When launched from Finder or `open`, macOS sets CWD to `/`, but Siv3D resolves `engine/` relative to the bundle's `MacOS/` dir. If this breaks, the fix is to either (a) set Xcode scheme's `customWorkingDirectory: ../GameMath/App`, or (b) change build output to place the app binary directly with assets. The spec's approach assumes (b) via `CONFIGURATION_BUILD_DIR`. Verify this held by running the executable with explicit CWD:

```bash
cd GameMath/App && ./GameMath.app/Contents/MacOS/GameMath
```

If that works but `open` doesn't, add to the scheme in `project.yml`:

```yaml
schemes:
  GameMath:
    build:
      targets:
        GameMath: all
    run:
      customWorkingDirectory: $(SRCROOT)/../GameMath/App
```

Re-run `xcodegen generate` and retry.

- [ ] **Step 5.3: Quit the app (Cmd+Q)**

---

## Task 6: Update .gitignore

**Files:**
- Create: `.gitignore` (at repo root — verify none exists; if one exists, append)

- [ ] **Step 6.1: Check if a root `.gitignore` exists**

Run:
```bash
cat .gitignore 2>/dev/null || echo "NO_GITIGNORE"
```

If `NO_GITIGNORE`, create a new file in step 6.2. Otherwise append.

- [ ] **Step 6.2: Create or append `.gitignore`**

Content to ensure is present (create or append — do not duplicate existing lines):

```
# macOS
.DS_Store

# Xcode / xcodegen
GameMath-macOS/GameMath.xcodeproj/
GameMath-macOS/build/
*.xcodeproj/xcuserdata/
*.xcworkspace/xcuserdata/

# macOS .app build artifacts (built into shared App/)
GameMath/App/GameMath.app/
GameMath/App/*.dSYM/

# Rider / JetBrains
.idea/
```

- [ ] **Step 6.3: Verify ignored files are no longer tracked**

Run:
```bash
git status --short
```

The generated `.xcodeproj/`, any `.DS_Store`, and `.idea/` should not appear. `project.yml`, `Info.plist`, `icon.icns`, and the `.gitignore` itself should appear as untracked/new.

- [ ] **Step 6.4: Commit scaffold + gitignore**

```bash
git add .gitignore GameMath-macOS/project.yml GameMath-macOS/Info.plist GameMath-macOS/icon.icns
git commit -m "[ADD] macOS build via xcodegen

Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
```

---

## Task 7: Update CLAUDE.md

**Files:**
- Modify: `CLAUDE.md`

- [ ] **Step 7.1: Remove the PCH paragraph from the Architecture section**

Open `CLAUDE.md`. Find the paragraph that starts with "`stdafx.h` is the precompiled header and is **force-included**…". Delete that entire bullet.

- [ ] **Step 7.2: Add a macOS build section under "Build & Run"**

After the existing Windows build bullets, insert:

```markdown
### macOS build

- Project: `GameMath-macOS/` — `project.yml` (xcodegen, committed) generates `GameMath.xcodeproj` (gitignored).
- Dependency: Siv3D 0.6.16 macOS distribution at `$SIV3D_0_6_16_MACOS` (set in `~/.zshrc`). Contains `include/`, `lib/macOS/`, `examples/`.
- Tool: [xcodegen](https://github.com/yonaskolb/XcodeGen) — install with `brew install xcodegen`. Regenerate the Xcode project whenever `project.yml` changes: `cd GameMath-macOS && xcodegen generate`.
- Build (CLI): `xcodebuild -project GameMath-macOS/GameMath.xcodeproj -scheme GameMath -configuration Debug build`.
- Run: the `.app` bundle is built into `GameMath/App/GameMath.app`. Launch via `open GameMath/App/GameMath.app` or from Xcode/Rider.
- Target arch: `x86_64` only (Siv3D's shipped libs are not fat). On Apple Silicon, the app runs under Rosetta 2.
- Deployment target: macOS 10.15.
```

- [ ] **Step 7.3: Update the "Architecture" section to reflect PCH removal**

Replace any remaining mention of `stdafx.h` with a note that `Main.cpp` includes Siv3D directly (`# include <Siv3D.hpp>` at the top). Update the "New `.cpp` files must `#include "stdafx.h"` first" note to instead say: "New `.cpp` files should `#include <Siv3D.hpp>` directly."

- [ ] **Step 7.4: Commit**

```bash
git add CLAUDE.md
git commit -m "[UPDATE] CLAUDE.md: macOS build + PCH removal

Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
```

---

## Definition of Done (from spec)

After all tasks complete, all of these must hold:

1. `cd GameMath-macOS && xcodegen generate` runs cleanly.
2. `xcodebuild ... build` produces `GameMath/App/GameMath.app`.
3. Launching the `.app` shows the centered grid with red/green axes and keyboard-movable ball — same behavior as Windows.
4. Opening `GameMath-macOS/GameMath.xcodeproj` in Rider shows the source and activates the run action.
5. (USER, on Windows) `msbuild GameMath.sln /p:Configuration=Debug /p:Platform=x64` still produces `GameMath/App/GameMath(debug).exe` that runs as before.

## Rollback

Each task is a single commit. Any failure in later tasks can be rolled back via `git revert` of the specific commit without affecting earlier successful work.
