SET(GAU_SRC_LIST
    gaussian5x5int.c
    gaussian5x5int.drv.c)

add_kernel_exe(gaussian5x5int ${GAU_SRC_LIST})

ADD_CUSTOM_TARGET(run-gaussian5x5int gaussian5x5int
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/out.pgm
  DEPENDS gaussian5x5int
  COMMENT "Running Gaussian 5x5 filter (integer) kernel")

ADD_DEPENDENCIES(run-kernel run-gaussian5x5int)
