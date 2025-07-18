set(MAA_VERSION v4.4.0-beta.1)

if(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-macos-aarch64-${MAA_VERSION}.zip")
    else()
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-macos-x86_64-${MAA_VERSION}.zip")
    endif()
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-linux-aarch64-${MAA_VERSION}.zip")
    else()
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-linux-x86_64-${MAA_VERSION}.zip")
    endif()
elseif(WIN32)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-win-aarch64-${MAA_VERSION}.zip")
    else()
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-win-x86_64-${MAA_VERSION}.zip")
    endif()
elseif(ANDROID)
    if(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-android-aarch64-${MAA_VERSION}.zip")
    else()
        set(MAA_URL "https://github.com/MaaXYZ/MaaFramework/releases/download/${MAA_VERSION}/MAA-android-x86_64-${MAA_VERSION}.zip")
    endif()
endif()
message(STATUS "Using MaaFramework from: ${MAA_URL}")

include(FetchContent)
FetchContent_Declare(
    MaaFramework
    URL ${MAA_URL}
)
FetchContent_MakeAvailable(MaaFramework)
message(STATUS "MaaFramework dir: ${maaframework_SOURCE_DIR}")

list(APPEND CMAKE_PREFIX_PATH "${maaframework_SOURCE_DIR}/share/cmake")
