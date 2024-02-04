cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("NuCat")
set(BIT7Z_AUTO_FORMAT true)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
# 设置编译标记
# 设置 cpp标准同时 设置utf8
set(CMAKE_CXX_STANDARD 23)
# 设置W版API
add_definitions("-DUNICODE" "-D_UNICODE")
if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
add_subdirectory("Depend/bit7z")
add_subdirectory ("NuCat")

# 移动NUCAT资源文件进PACK
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Other/" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out/Pack/)
# 移动NUCAT资源文件进主程序 Debug目录
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Other/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/NuCat/)