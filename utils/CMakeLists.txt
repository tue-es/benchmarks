SET(UTILS_SRC_LIST 
    pgm.c 
    driver_common.c)

ADD_LIBRARY(utils ${UTILS_SRC_LIST})
ADD_EXECUTABLE(dmem_init dmem_init.c)
ADD_EXECUTABLE(dmem_dump dmem_dump.c)
TARGET_LINK_LIBRARIES(dmem_init utils)
TARGET_LINK_LIBRARIES(dmem_dump utils)
