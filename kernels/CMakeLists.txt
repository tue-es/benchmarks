ADD_CUSTOM_TARGET(run-kernel)
ADD_DEPENDENCIES(run run-kernel)
SUBDIRS(gaussian5x5int yuv2rgb conservativeSmooth median dilation erosion
	van_herk histogram)
