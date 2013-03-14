SET(GAU_SRC_LIST
    yuv2rgb.c
    yuv2rgb.drv.c)

add_kernel_exe(yuv2rgb ${GAU_SRC_LIST})

#configure_file(data/lenna.pgm ${CMAKE_CURRENT_BINARY_DIR}/data/lenna.pgm COPYONLY)
#configure_file(run.sh ${CMAKE_CURRENT_BINARY_DIR}/run.sh COPYONLY)

