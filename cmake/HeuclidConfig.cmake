set(LIB_NAME Heuclid)
set(PATH_NAME Heuclid)
set(${LIB_NAME}_DIR ${ROOT_PATH}/${PATH_NAME})

message("--[${LIB_NAME}]:Hello! I'm in ${${LIB_NAME}_DIR}")

include_directories(${${LIB_NAME}_DIR}/include)
include_directories(${${LIB_NAME}_DIR}/include/Heuclid)
include_directories(${${LIB_NAME}_DIR}/include/Heuclid/euclid)
include_directories(${${LIB_NAME}_DIR}/include/Heuclid/geometry)
include_directories(${${LIB_NAME}_DIR}/include/Heuclid/title)


aux_source_directory(${${LIB_NAME}_DIR}/src/Heuclid/euclid/orientation ALL_SRC_FILES)
aux_source_directory(${${LIB_NAME}_DIR}/src/Heuclid/euclid/tools ALL_SRC_FILES)