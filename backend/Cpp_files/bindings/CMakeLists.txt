cmake_minimum_required(VERSION 3.15)

project(myengine)

set(PYBIND11_FINDPYTHON ON)

set(Python_EXECUTABLE
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE/matching-engine/backend/ME_Venv/Scripts/python.exe"
)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

set(pybind11_DIR
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE/matching-engine/backend/ME_Venv/Lib/site-packages/pybind11/share/cmake/pybind11"
)

find_package(pybind11 REQUIRED)

pybind11_add_module(myengine bindings.cpp)