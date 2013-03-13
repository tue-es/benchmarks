MACRO(add_kernel_exe name)
  ADD_EXECUTABLE(${name} ${ARGN})
  TARGET_LINK_LIBRARIES(${name} utils)
ENDMACRO(add_kernel_exe name)
