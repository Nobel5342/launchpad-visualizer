cmake_minimum_required(VERSION 3.10)
project(LaunchpadVisualizer VERSION 0.1.0 LANGUAGES CXX)

# C++標準の設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt設定
set(CMAKE_AUTOMOC ON)  # Qt MOC自動化を有効化
set(CMAKE_AUTORCC ON)  # Qt リソースコンパイラを有効化
set(CMAKE_AUTOUIC ON)  # Qt UIコンパイラを有効化
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# RtMidiの検出 - クロスプラットフォーム対応
option(USE_BUNDLED_RTMIDI "Use the bundled RtMidi library" OFF)

if(USE_BUNDLED_RTMIDI)
    # バンドルされたRtMidiを使用する場合の設定
    message(STATUS "Using bundled RtMidi library")
    set(RTMIDI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/rtmidi")
    set(RTMIDI_LIBRARIES rtmidi)
    add_subdirectory(external/rtmidi)
else()
    # システムのRtMidiを探す
    if(WIN32)
        # Windowsの場合、find_packageで探す
        find_package(RtMidi QUIET)
        if(RtMidi_FOUND)
            set(RTMIDI_INCLUDE_DIRS ${RTMIDI_INCLUDE_DIR})
            set(RTMIDI_LIBRARIES ${RTMIDI_LIBRARIES})
        else()
            # 見つからない場合はfind_libraryで探す
            find_library(RTMIDI_LIBRARY rtmidi)
            find_path(RTMIDI_INCLUDE_DIR RtMidi.h)
            if(RTMIDI_LIBRARY AND RTMIDI_INCLUDE_DIR)
                set(RTMIDI_LIBRARIES ${RTMIDI_LIBRARY})
                set(RTMIDI_INCLUDE_DIRS ${RTMIDI_INCLUDE_DIR})
                message(STATUS "Found RtMidi: ${RTMIDI_LIBRARY}")
            else()
                message(FATAL_ERROR "RtMidi library not found. Please install RtMidi or enable USE_BUNDLED_RTMIDI.")
            endif()
        endif()
    else()
        # Linux/MacOSの場合はpkg-configを使用
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(RTMIDI rtmidi)
        if(NOT RTMIDI_FOUND)
            message(FATAL_ERROR "RtMidi library not found. Please install RtMidi or enable USE_BUNDLED_RTMIDI.")
        endif()
    endif()
endif()

# ソースファイル
set(SOURCES
    src/main.cpp
    src/LaunchpadVisualizer.cpp
    src/midi/MidiManager.cpp
    src/midi/LaunchpadProtocol.cpp
    src/gui/MainWindow.cpp
    src/gui/LaunchpadGrid.cpp
)

# ヘッダーファイル
set(HEADERS
    src/LaunchpadVisualizer.h
    src/midi/MidiManager.h
    src/midi/LaunchpadProtocol.h
    src/gui/MainWindow.h
    src/gui/LaunchpadGrid.h
)

# Windows固有のリソースファイル追加
if(WIN32)
    set(RESOURCES
        resources/windows/app.rc
    )
endif()

# 実行可能ファイルの作成
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# インクルードディレクトリ
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${RTMIDI_INCLUDE_DIRS}
)

# 基本リンクライブラリ
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Widgets
    ${RTMIDI_LIBRARIES}
)

# プラットフォーム依存のライブラリリンク
if(UNIX AND NOT APPLE)
    # Linux固有のライブラリ
    target_link_libraries(${PROJECT_NAME} PRIVATE
        pthread
        asound
        jack
    )
elseif(WIN32)
    # Windows固有のライブラリ
    target_link_libraries(${PROJECT_NAME} PRIVATE
        winmm
    )
    # Windows用のフラグ
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# インストール設定
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# コンパイルオプション
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    # Visual Studioでのマルチプロセッサコンパイルを有効に
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
    # Windows.hによる不要なインクルードを減らす
    add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
endif()