SET(GAU_SRC_LIST
    gaussian5x5int.c
    gaussian5x5int.drv.c)

add_kernel_exe(gaussian5x5int ${GAU_SRC_LIST})

configure_file(data/lenna.pgm ${CMAKE_CURRENT_BINARY_DIR}/data/lenna.pgm COPYONLY)
configure_file(run.sh ${CMAKE_CURRENT_BINARY_DIR}/run.sh COPYONLY)

