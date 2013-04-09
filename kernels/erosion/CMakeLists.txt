SET(EROSION_SRC_LIST
    erosion.c
    erosion.drv.c)

add_kernel_exe(erosion ${EROSION_SRC_LIST})

ADD_CUSTOM_TARGET(run-erosion erosion
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/out.pgm
  DEPENDS erosion
  COMMENT "Running erosion 3x3 filter kernel")

ADD_DEPENDENCIES(run-kernel run-erosion)
