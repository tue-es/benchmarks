SET(3DRS_SRC_LIST
    3DRS.c
    3DRS.drv.c
    bitmap.c)

set(CMAKE_C_FLAGS "-std=c99")

add_kernel_exe(3DRS ${3DRS_SRC_LIST})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/images/
#	${CMAKE_CURRENT_BINARY_DIR}/images/ COPYONLY)

file( MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/images/" ) 

ADD_CUSTOM_TARGET(run-3DRS 3DRS
  ${CMAKE_CURRENT_SOURCE_DIR}/images/renata
  ${CMAKE_CURRENT_BINARY_DIR}/images
  DEPENDS 3DRS
  COMMENT "Running 3DRS application")

ADD_DEPENDENCIES(run-application run-3DRS)
