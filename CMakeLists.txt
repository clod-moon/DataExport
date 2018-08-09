# 最顶层的cmake

# 需要定义：
# CMAKE_BUILD_TYPE=Debug/Release
# PLAT=TK1/S2 (windows不必)

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)	
ENDIF()

cmake_minimum_required(VERSION 2.6)
#project(OperationsCenter)
project(data_export)

message(STATUS "project dir:" ${PROJECT_SOURCE_DIR})
message(STATUS "build type is:" ${CMAKE_BUILD_TYPE})
message(STATUS "platform is:" ${PLAT})

# 指定编译

if(PLAT STREQUAL "TK1")
	set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc-4.6)
	set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++-4.6)
	ADD_DEFINITIONS(-DTK1)
elseif(PLAT STREQUAL "TX1")
	set(CMAKE_C_COMPILER aarch64-unknown-linux-gnu-gcc)
	set(CMAKE_CXX_COMPILER aarch64-unknown-linux-gnu-g++)
	ADD_DEFINITIONS(-DTX1)
elseif(PLAT STREQUAL "X86")	
	add_definitions(-m32)
	set(CMAKE_C_COMPILER gcc)
	set(CMAKE_CXX_COMPILER g++)
	set(CMAKE_SHARED_LINKER_FLAGS 	"${CMAKE_SHARED_LINKER_FLAGS} -m32")
	set(CMAKE_EXE_LINKER_FLAGS 		"${CMAKE_EXE_LINKER_FLAGS} -m32")
elseif(PLAT STREQUAL "LINUX-X86_64")	
	add_definitions(-m64 -fpermissive)
	add_definitions(-DLINUX-X86_64)
	set(CMAKE_C_COMPILER gcc)
	set(CMAKE_CXX_COMPILER g++)
	set(CMAKE_SHARED_LINKER_FLAGS 	"${CMAKE_SHARED_LINKER_FLAGS} -m64")
	set(CMAKE_EXE_LINKER_FLAGS 		"${CMAKE_EXE_LINKER_FLAGS} -m64")
	ADD_DEFINITIONS(-DLINUX_X86_64)
endif()




#指定debug的共同选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
	if(NOT WIN32)
		add_definitions(-g)
	endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-O2)
else()
	message(FATAL_ERROR "请定义 CMAKE_BUILD_TYPE=Debug/Release")		
endif()

#设定全局选项
SET(CMAKE_SKIP_RPATH ON)

# TK1/TX1的专用宏
if(PLAT STREQUAL "TK1")
	add_definitions(-DTK1)
elseif(PLAT STREQUAL "TX1")
	add_definitions(-DTX1)	
endif()

# 设置目录
set(DIR_INCLUDE ${PROJECT_SOURCE_DIR}/code/include)
set(DIR_3RD_PARTY ${PROJECT_SOURCE_DIR}/3rdparty)


if(PLAT STREQUAL "TK1")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		link_directories(${PROJECT_SOURCE_DIR}/lib_d/linux-tk1 ${PROJECT_SOURCE_DIR}/bin_d/linux-tk1)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-tk1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-tk1")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-tk1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-tk1")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib_d/linux-tk1)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-tk1)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-tk1)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")		
		link_directories(${PROJECT_SOURCE_DIR}/lib/linux-tk1 ${PROJECT_SOURCE_DIR}/bin/linux-tk1)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-tk1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-tk1")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-tk1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-tk1")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/linux-tk1)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-tk1)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-tk1)
	endif()
elseif(PLAT STREQUAL "TX1")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		link_directories(${PROJECT_SOURCE_DIR}/lib_d/linux-tx1 ${PROJECT_SOURCE_DIR}/bin_d/linux-tx1)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-tx1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-tx1")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-tx1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-tx1")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib_d/linux-tx1)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-tx1)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-tx1)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")		
		link_directories(${PROJECT_SOURCE_DIR}/lib/linux-tx1 ${PROJECT_SOURCE_DIR}/bin/linux-tx1)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-tx1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-tx1")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-tx1 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-tx1")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/linux-tx1) 
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-tx1)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-tx1)
	endif()
elseif(PLAT STREQUAL "X86")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		link_directories(${PROJECT_SOURCE_DIR}/lib_d/linux-x86 ${PROJECT_SOURCE_DIR}/bin_d/linux-x86)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-x86 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-x86")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-x86 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-x86")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib_d/linux-x86)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-x86)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-x86)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")		
		link_directories(${PROJECT_SOURCE_DIR}/lib/linux-x86 ${PROJECT_SOURCE_DIR}/bin/linux-x86)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-x86 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-x86")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-x86 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-x86")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/linux-x86)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-x86)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-x86)
	endif()
elseif(PLAT STREQUAL "LINUX-X86_64")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		link_directories(${PROJECT_SOURCE_DIR}/lib_d/linux-x64 ${PROJECT_SOURCE_DIR}/bin_d/linux-x86_64)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-x64 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-x86_64")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib_d/linux-x64 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin_d/linux-x86_64")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib_d/linux-x86_64)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-x86_64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin_d/linux-x86_64)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")		
		link_directories(${PROJECT_SOURCE_DIR}/lib/linux-x64 ${PROJECT_SOURCE_DIR}/bin/linux-x86_64)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-x64 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-x86_64")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/linux-x64 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/bin/linux-x86_64")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/linux-x86_64)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-x86_64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/linux-x86_64)
	endif()
endif()






message(STATUS " Include dir: " ${DIR_INCLUDE})
message(STATUS " Build lib dir " ${LIBRARY_OUTPUT_PATH})
message(STATUS " Build exe dir" ${EXECUTABLE_OUTPUT_PATH})

# 代码所在子目录
add_subdirectory(code/src/)






