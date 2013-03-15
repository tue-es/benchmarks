SET(GAU_SRC_LIST
    median.c
    median.drv.c)

add_kernel_exe(median ${GAU_SRC_LIST})

ADD_CUSTOM_TARGET(run-median median
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna-noise.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/out.pgm
  DEPENDS median
  COMMENT "Running median filter kernel")

ADD_DEPENDENCIES(run-kernel run-median)
