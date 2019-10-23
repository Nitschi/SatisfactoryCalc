cmake_minimum_required(VERSION 3.15)

set(This SatisfactoryCalcMain)
set(Sources
    SatisfactoryCalcMain.cpp
)

add_executable(${This} ${Sources})

find_package( Boost 1.71.0 COMPONENTS REQUIRED )
find_package( yaml-cpp CONFIG REQUIRED )
include_directories(${YAML_CPP_INCLUDE_DIR})

target_link_libraries(${This}
    ${YAML_CPP_LIBRARIES}
    SatisfactoryCalc
)
