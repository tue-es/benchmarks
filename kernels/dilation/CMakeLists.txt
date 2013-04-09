SET(DILATION_SRC_LIST
    dilation.c
    dilation.drv.c)

add_kernel_exe(dilation ${DILATION_SRC_LIST})

ADD_CUSTOM_TARGET(run-dilation dilation
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/out.pgm
  DEPENDS dilation
  COMMENT "Running dilation 5x5 filter kernel")

ADD_DEPENDENCIES(run-kernel run-dilation)
