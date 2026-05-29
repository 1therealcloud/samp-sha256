cmake_minimum_required(VERSION 3.10)

project(SHA256 C CXX)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_SOURCE_DIR}/bin")
endforeach()

if(MSVC)
    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
        message(FATAL_ERROR "Error: Build is possible ONLY for x86 (32-bit) architecture. Use '-A Win32' (for MSVC).")
    endif()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SHA256 SHARED
    src/main.cpp
    samp-plugin-sdk/amxplugin2.cpp
    samp-plugin-sdk/amxplugin.cpp
    samp-plugin-sdk/amx/getch.c
)

set_target_properties(SHA256 PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_include_directories(SHA256 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/PicoSHA2
    ${CMAKE_CURRENT_SOURCE_DIR}/samp-plugin-sdk
)

if(MSVC)
    target_compile_options(SHA256 PRIVATE /wd4005 /arch:IA32)
    target_compile_definitions(SHA256 PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _WINSOCK_DEPRECATED_NO_WARNINGS
        HAVE_STDINT_H
    )
    set_target_properties(SHA256 PROPERTIES SUFFIX ".dll")
else()
    target_compile_definitions(SHA256 PRIVATE LINUX)
    target_compile_options(SHA256 PRIVATE 
        -m32 
        -fPIC 
        -fno-stack-protector 
        -Wno-write-strings 
        -Wno-attributes
    )
    target_link_options(SHA256 PRIVATE -m32 -shared -static-libgcc -static-libstdc++)
    set_target_properties(SHA256 PROPERTIES SUFFIX ".so")
endif()
