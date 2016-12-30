cmake_minimum_required(VERSION 3.3)
project(ScrapDesigner)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Svg Widgets)

set(SOURCES
	src/main.cpp
    src/GateHandles.cpp src/GateHandles.hpp
    src/GraphicsScene.cpp src/GraphicsScene.hpp
    src/GraphicsGate.cpp src/GraphicsGate.hpp
)

qt5_add_resources(IMAGES images/images.qrc)


add_executable(ScrapDesigner "${SOURCES}" "${IMAGES}")
target_link_libraries(ScrapDesigner Qt5::Svg Qt5::Widgets)
set_target_properties(ScrapDesigner PROPERTIES COMPILE_FLAGS "-std=c++11 -pedantic -Wall")

