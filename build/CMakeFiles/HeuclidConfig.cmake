# - Config file for the Heuclid package
# It defines the following variables
#  HEUCLID_INCLUDE_DIRS - include directory
#  HEUCLID_LINK_DIRS    - link library

# compute paths
set(HEUCLID_INCLUDE_DIRS    "c:/usr/local/include")  
set(HEUCLID_LINK_DIRS       "c:/usr/local/lib"   )

# include paths
include_directories(${HEUCLID_INCLUDE_DIRS} Include ${HEUCLID_INCLUDE_DIRS} and ${HEUCLID_LINK_DIRS})
link_directories(${HEUCLID_LINK_DIRS})
message("--[Heuclid]: Package found!")
