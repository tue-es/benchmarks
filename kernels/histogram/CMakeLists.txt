SET(HISTOGRAM_SRC_LIST
    histogram.c)

add_kernel_exe(histogram ${HISTOGRAM_SRC_LIST})

ADD_CUSTOM_TARGET(run-histogram histogram
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna.pgm
  DEPENDS histogram
  COMMENT "Running histogram kernel")

ADD_DEPENDENCIES(run-kernel run-histogram)
