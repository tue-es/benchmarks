SET(GAU_SRC_LIST
    gaussian5x5int.c
    gaussian5x5int.drv.c)
add_kernel_exe(gaussian5x5int ${GAU_SRC_LIST})

