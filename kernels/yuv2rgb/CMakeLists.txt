SET(GAU_SRC_LIST
    yuv2rgb.c
    yuv2rgb.drv.c)

add_kernel_exe(yuv2rgb ${GAU_SRC_LIST})

ADD_CUSTOM_TARGET(run-yuv2rgb yuv2rgb
  ${CMAKE_CURRENT_SOURCE_DIR}/dmem/yuv2rgb.dmem_init
  ${CMAKE_CURRENT_BINARY_DIR}/out.dmem_out
  DEPENDS yuv2rgb
  COMMENT "Running YUV2RGB kernel")

ADD_DEPENDENCIES(run-kernel run-yuv2rgb)
