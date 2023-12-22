include(FetchContent)
#### webview2 dependencies start
# Microsoft.Windows.ImplementationLibrary 
# The Windows Implementation Libraries (wil) were created to improve productivity and solve problems commonly seen by Windows developers. by: Microsoft WindowsImplementationLibraryTeam
FetchContent_Declare(
  wil
  URL  https://www.nuget.org/api/v2/package/Microsoft.Windows.ImplementationLibrary/1.0.231216.1
)
# Microsoft.Web.WebView2
FetchContent_Declare(
  webview2
  URL  https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/1.0.2210.55
)
FetchContent_MakeAvailable(wil webview2)

include_directories(SYSTEM "${wil_SOURCE_DIR}/include/")
include_directories(SYSTEM "${webview2_SOURCE_DIR}/build/native/include/")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM "x86")
endif()

link_libraries("${webview2_SOURCE_DIR}/build/native/${PLATFORM}/WebView2LoaderStatic.lib")

#### webview2 dependencies end
# 将源代码添加到此项目的可执行文件。
add_executable (NaCat WIN32 "NaCat.cpp"  "src/Uilt.cpp" "include/Uilt.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NaCat PROPERTY CXX_STANDARD 20)
endif()

file (GLOB EMBED_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../Resource/*.*")
file(COPY ${EMBED_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resource/)
