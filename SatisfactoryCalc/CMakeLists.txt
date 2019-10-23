cmake_minimum_required(VERSION 3.15)

set(This SatisfactoryCalc)

set(Headers
    Factory.hpp
    Recipe.hpp
    YamlReader.hpp
)
set(Sources
    Factory.cpp
    YamlReader.cpp
)

find_package( Boost 1.71.0 COMPONENTS REQUIRED )
find_package( yaml-cpp CONFIG REQUIRED )
include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

add_library(${This} STATIC ${Sources} ${Headers})

target_link_libraries(${This}
    ${Boost_LIBRARIES}
    ${YAML_CPP_LIBRARIES}
)