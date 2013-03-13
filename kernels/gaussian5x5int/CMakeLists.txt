SET(GAU_SRC_LIST
    gaussian5x5int.c
    gaussian5x5int.drv.c)

add_kernel_exe(gaussian5x5int ${GAU_SRC_LIST})
add_kernel_exe(gaussian5x5int_dmem_init dmem_init.c)
add_kernel_exe(gaussian5x5int_dmem_dump dmem_dump.c)

configure_file(dmem/gaussian5x5int.dmem_init ${CMAKE_CURRENT_BINARY_DIR}/dmem/gaussian5x5int.dmem_init COPYONLY)
configure_file(dmem/gaussian5x5int.dmem_meta ${CMAKE_CURRENT_BINARY_DIR}/dmem/gaussian5x5int.dmem_meta COPYONLY)
configure_file(dmem/lenna.pgm ${CMAKE_CURRENT_BINARY_DIR}/dmem/lenna.pgm COPYONLY)
configure_file(run.sh ${CMAKE_CURRENT_BINARY_DIR}/run.sh COPYONLY)

