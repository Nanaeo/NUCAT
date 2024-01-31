message("-----------------NUCAT_START---------------")
add_definitions("-DBIT7Z_AUTO_FORMAT")

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/Depend/wil/include/")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/Depend/webview2/build/native/include/")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM "x86")
endif()
link_libraries("${PROJECT_SOURCE_DIR}/Depend/webview2/build/native/${PLATFORM}/WebView2LoaderStatic.lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# 编译全部代码
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable (NuCat WIN32 ${SOURCES} "src/yyjson.c" "NuCat.cpp")
target_link_libraries(NuCat PRIVATE bit7z )
message("-----------------NUCAT_END---------------")