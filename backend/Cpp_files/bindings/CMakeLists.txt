cmake_minimum_required(VERSION 3.15)

project(myengine)

set(PYBIND11_FINDPYTHON ON)

set(Python_ROOT_DIR
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE UPDATED/backend/venv"
)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

set(pybind11_DIR
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE UPDATED/venv/Lib/site-packages/pybind11/share/cmake/pybind11"
)

find_package(pybind11 REQUIRED)

pybind11_add_module(myengine
    bindings.cpp
    ../core/MatchingEngine.cpp
    ../core/OrderBook.cpp
    ../core/Order.cpp
)