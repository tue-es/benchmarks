SET(GAU_SRC_LIST
    conservativeSmooth.c
    conservativeSmooth.drv.c)

add_kernel_exe(conservativeSmooth ${GAU_SRC_LIST})

ADD_CUSTOM_TARGET(run-conservativeSmooth conservativeSmooth
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna-noise.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/out.pgm
  DEPENDS conservativeSmooth
  COMMENT "Running conservative smoothing kernel")

ADD_DEPENDENCIES(run-kernel run-conservativeSmooth)
