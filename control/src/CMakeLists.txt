# cmake_minimum_required(VERSION <specify CMake version here>)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(drv)
include_directories(ui)

add_executable(src
        drv/b15f.cpp
        drv/b15f.h
        drv/dot.cpp
        drv/dot.h
        drv/driverexception.h
        drv/plottyfile.cpp
        drv/plottyfile.h
        drv/timeoutexception.h
        drv/usart.cpp
        drv/usart.h
        drv/usartexception.h
        ui/ui.cpp
        ui/ui.h
        ui/view.cpp
        ui/view.h
        ui/view_info.cpp
        ui/view_info.h
        ui/view_monitor.cpp
        ui/view_monitor.h
        ui/view_promt.cpp
        ui/view_promt.h
        ui/view_selection.cpp
        ui/view_selection.h
        cli.cpp)
