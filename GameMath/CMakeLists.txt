cmake_minimum_required(VERSION 3.20)

# CMP0091 NEW: enable CMAKE_MSVC_RUNTIME_LIBRARY abstraction
cmake_policy(SET CMP0091 NEW)

project(GameMath CXX)

# Siv3D 0.6.16 uses std::byteswap (C++23) on Windows; mac historically built
# with c++2a but the headers compile fine under C++23, so use 23 everywhere.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Source
# ---------------------------------------------------------------------------
set(GAMEMATH_SOURCES
    GameMath/Main.cpp
)

# ---------------------------------------------------------------------------
# Platform: Windows (MSVC)
# ---------------------------------------------------------------------------
if(WIN32)
    if(NOT MSVC)
        message(FATAL_ERROR
            "Siv3D 0.6.16 on Windows requires MSVC. "
            "Configure CLion's toolchain to Visual Studio (amd64).")
    endif()

    set(SIV3D_ROOT "$ENV{SIV3D_0_6_16}")
    if(NOT SIV3D_ROOT OR NOT EXISTS "${SIV3D_ROOT}/include/Siv3D.hpp")
        message(FATAL_ERROR
            "Environment variable SIV3D_0_6_16 must point to the Siv3D 0.6.16 install root "
            "(directory containing include/Siv3D.hpp). Current value: '${SIV3D_ROOT}'.")
    endif()

    enable_language(RC)

    add_executable(GameMath WIN32
        ${GAMEMATH_SOURCES}
        GameMath/App/Resource.rc
    )

    # Match Siv3D's static CRT (the shipped Siv3D.lib is built /MT, Siv3D_d.lib /MTd)
    set_property(TARGET GameMath PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    target_include_directories(GameMath PRIVATE
        "${SIV3D_ROOT}/include"
        "${SIV3D_ROOT}/include/ThirdParty"
        # RC compiler resolves Resource(engine/...) entries relative to here
        "${CMAKE_SOURCE_DIR}/GameMath/App"
    )

    target_link_directories(GameMath PRIVATE
        "${SIV3D_ROOT}/lib/Windows"
    )

    # Siv3D headers contain #pragma comment(lib, ...) for transitive deps;
    # only the main lib needs to be named here. delayimp resolves
    # __delayLoadHelper2 used by /DELAYLOAD entries below.
    target_link_libraries(GameMath PRIVATE
        $<$<CONFIG:Debug>:Siv3D_d>
        $<$<NOT:$<CONFIG:Debug>>:Siv3D>
        delayimp
    )

    target_compile_definitions(GameMath PRIVATE
        _WINDOWS
        UNICODE
        _UNICODE
        _ENABLE_EXTENDED_ALIGNED_STORAGE
        _SILENCE_CXX20_CISO646_REMOVED_WARNING
        _SILENCE_ALL_CXX23_DEPRECATION_WARNINGS
        _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
    )

    # CMAKE_CXX_STANDARD=23 already injects /std:c++23; do not also set
    # /std:c++latest (cl warns D9025 about override).
    target_compile_options(GameMath PRIVATE
        /Zc:__cplusplus
        /utf-8
        /MP
        /permissive-
        /W4
        /wd26451
        /wd26812
    )

    target_link_options(GameMath PRIVATE
        /DELAYLOAD:advapi32.dll
        /DELAYLOAD:crypt32.dll
        /DELAYLOAD:dwmapi.dll
        /DELAYLOAD:gdi32.dll
        /DELAYLOAD:imm32.dll
        /DELAYLOAD:ole32.dll
        /DELAYLOAD:oleaut32.dll
        /DELAYLOAD:opengl32.dll
        /DELAYLOAD:shell32.dll
        /DELAYLOAD:shlwapi.dll
        /DELAYLOAD:user32.dll
        /DELAYLOAD:winmm.dll
        /DELAYLOAD:ws2_32.dll
    )

    set_target_properties(GameMath PROPERTIES
        OUTPUT_NAME_DEBUG "GameMath(debug)"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/GameMath/App"
    )

# ---------------------------------------------------------------------------
# Platform: macOS (AppleClang)
# ---------------------------------------------------------------------------
elseif(APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "" FORCE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "" FORCE)

    set(SIV3D_ROOT "$ENV{HOME}/Siv3D")
    if(NOT EXISTS "${SIV3D_ROOT}/include/Siv3D.hpp")
        message(FATAL_ERROR
            "Siv3D 0.6.16 must be installed at '~/Siv3D' "
            "(expected ${SIV3D_ROOT}/include/Siv3D.hpp).")
    endif()

    set(APP_ICON "${CMAKE_SOURCE_DIR}/GameMath-macOS/icon.icns")
    set(APP_INFO_PLIST "${CMAKE_SOURCE_DIR}/GameMath-macOS/Info.plist")

    add_executable(GameMath MACOSX_BUNDLE
        ${GAMEMATH_SOURCES}
        ${APP_ICON}
    )

    set_source_files_properties(${APP_ICON} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    set_target_properties(GameMath PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${APP_INFO_PLIST}"
        MACOSX_BUNDLE_BUNDLE_NAME "GameMath"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.nyxrux62.GameMath"
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
    )

    target_include_directories(GameMath PRIVATE
        "${SIV3D_ROOT}/include"
        "${SIV3D_ROOT}/include/ThirdParty"
    )

    target_link_directories(GameMath PRIVATE
        "${SIV3D_ROOT}/lib/macOS"
        "${SIV3D_ROOT}/lib/macOS/boost"
        "${SIV3D_ROOT}/lib/macOS/freetype"
        "${SIV3D_ROOT}/lib/macOS/harfbuzz"
        "${SIV3D_ROOT}/lib/macOS/libgif"
        "${SIV3D_ROOT}/lib/macOS/libjpeg-turbo"
        "${SIV3D_ROOT}/lib/macOS/libogg"
        "${SIV3D_ROOT}/lib/macOS/libpng"
        "${SIV3D_ROOT}/lib/macOS/libtiff"
        "${SIV3D_ROOT}/lib/macOS/libvorbis"
        "${SIV3D_ROOT}/lib/macOS/libwebp"
        "${SIV3D_ROOT}/lib/macOS/opencv"
        "${SIV3D_ROOT}/lib/macOS/opus"
        "${SIV3D_ROOT}/lib/macOS/zlib"
    )

    # Library list copied verbatim from GameMath-macOS/project.yml OTHER_LDFLAGS.
    target_link_libraries(GameMath PRIVATE
        Siv3D
        boost_filesystem
        opusfile
        opus
        zlib
        tiff
        opencv_imgcodecs
        opencv_objdetect
        opencv_imgproc
        opencv_core
        opencv_photo
        opencv_videoio
        webp
        vorbisfile
        vorbisenc
        vorbis
        harfbuzz
        freetype
        png16
        ogg
        turbojpeg
        libgif
        curl
        "-framework AudioToolbox"
        "-framework AVFoundation"
        "-framework CoreAudio"
        "-framework CoreMedia"
    )

    target_compile_options(GameMath PRIVATE
        -fvisibility=hidden
    )

    add_custom_command(TARGET GameMath POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo
            "Copying Siv3D engine resources into bundle"
        COMMAND rsync -a --delete
            "${CMAKE_SOURCE_DIR}/GameMath/App/engine/"
            "$<TARGET_BUNDLE_CONTENT_DIR:GameMath>/Resources/engine/"
        COMMAND ${CMAKE_COMMAND} -E echo
            "Copying example assets into bundle"
        COMMAND rsync -a --delete
            "${CMAKE_SOURCE_DIR}/GameMath/App/example/"
            "$<TARGET_BUNDLE_CONTENT_DIR:GameMath>/Resources/example/"
        VERBATIM
    )

else()
    message(FATAL_ERROR
        "GameMath supports Windows (MSVC) and macOS (AppleClang) only.")
endif()
