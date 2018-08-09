cmake_minimum_required(VERSION 2.6)

SET(PROJECT DataExportService)
IF(DEFINED  OPS_SOFT_VERSION )
	ADD_DEFINITIONS(-DOPS_VER_NUM="${OPS_SOFT_VERSION}")
	MESSAGE("OPS_VER_NUM  is " ${OPS_SOFT_VERSION})
	ELSE()
	MESSAGE("OPS_VER_NUM  is not set")
ENDIF()

# 库文件的输出路径
#源码
#aux_source_directory(. SRC_LIST)
FILE(GLOB_RECURSE SRC_LIST 
			"*.c" 
			"*.cpp" 
			"*.h" 
			"*.hpp" 
			"*.inl" 
			)

# 头文件

include_directories(
	.
	${DIR_INCLUDE}
	)



#连接的动态库
SET(COMMON_LIBS
	debug IVECommonObjectd 
    debug IVE_CORE_SDKd   
	debug SCUtilsd  
	debug SCVasNetd  
				
	optimized IVECommonObject
	optimized IVE_CORE_SDK
	optimized SCUtils
	optimized SCVasNet

	pthread
	iconv
	xml2
	ini
	ghttp
	z
	)

#if(PLAT STREQUAL "TK1")
SET(PLATFORM_LIBS 
  debug  asound
  debug  VdoSqlited
  debug  VdoPostgresd
  debug  SCVdod

  optimized asoun
  optimized VdoSqlite
  optimized VdoPostgres
  optimized SCVdod
 )
#endif
#编译
add_executable(${PROJECT} ${SRC_LIST})

#连接
target_link_libraries(${PROJECT}  ${COMMON_LIBS})

#Debug版本输出文件名后缀
set_target_properties(${PROJECT} PROPERTIES DEBUG_POSTFIX "d")
