cmake_minimum_required(VERSION 3.30)
project(e_912_914_hidanvlad)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)

# Qt Setup
set(CMAKE_PREFIX_PATH "D:/QT/6.5.3/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(e_912_914_hidanvlad main.cpp
        Biologist.cpp Biologist.h
        Bacterium.cpp Bacterium.h
        Repository.cpp Repository.h
        Service.cpp Service.h
        Observer.h
        BacteriumTableModel.cpp BacteriumTableModel.h
        BiologistWindow.cpp BiologistWindow.h
        SpeciesVisualizer.cpp SpeciesVisualizer.h

)

target_link_libraries(e_912_914_hidanvlad Qt6::Widgets)