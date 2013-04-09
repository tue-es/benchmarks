SET(VAN_HERK_SRC_LIST
    van_herk.c
    van_herk.drv.c)

add_kernel_exe(van_herk ${VAN_HERK_SRC_LIST})

ADD_CUSTOM_TARGET(run-van_herk van_herk
  ${CMAKE_CURRENT_SOURCE_DIR}/data/lenna.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/opening.pgm
  ${CMAKE_CURRENT_BINARY_DIR}/closing.pgm
  DEPENDS van_herk
  COMMENT "Running van herk opening/closing kernel")

ADD_DEPENDENCIES(run-kernel run-van_herk)
