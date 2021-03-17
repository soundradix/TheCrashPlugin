cmake_minimum_required(VERSION 3.19)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(APPLE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        execute_process(COMMAND xcrun --sdk macosx --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
    endif()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    set(CMAKE_XCODE_ATTRIBUTE_ARCHS "$(ARCHS_STANDARD)")
    set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
    set(CMAKE_XCODE_ATTRIBUTE_COPY_PHASE_STRIP "NO")
    set(CMAKE_XCODE_ATTRIBUTE_DEAD_CODE_STRIPPING "NO")
endif()

if(MSVC)
    #static linking in Windows
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(TheCrashPlugin VERSION 0.0.1)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/JUCE)

juce_add_plugin(TheCrashPlugin
    COMPANY_NAME "Xidar Dnuos"
    BUNDLE_ID com.XidarDnuos.TheCrashPlugin
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    NEEDS_CURL FALSE
    NEEDS_WEB_BROWSER FALSE
    IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE Srdx
    PLUGIN_CODE CrsH
    AAX_IDENTIFIER "com.XidarDnuos.TheCrashPlugin"
    DESCRIPTION "TheCrashPlugin"
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "TheCrashPlugin"
    VST3_CATEGORIES "Fx"
    AU_SANDBOX_SAFE FALSE
    HARDENED_RUNTIME_ENABLED TRUE
    HARDENED_RUNTIME_OPTIONS "com.apple.security.device.audio-input"
)

juce_generate_juce_header(TheCrashPlugin)

target_sources(TheCrashPlugin
    PRIVATE
    src/PluginProcessor.h
    src/PluginProcessor.cpp
    src/PluginEditor.h
    src/PluginEditor.cpp
)

target_compile_definitions(TheCrashPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(TheCrashPlugin
    PRIVATE
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_utils
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
)