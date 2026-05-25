cmake_minimum_required(VERSION 3.15)

project(myengine)

set(PYBIND11_FINDPYTHON ON)

# Updated path to the Python executable in the new directory's virtual environment
set(Python_EXECUTABLE
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE UPDATED/backend/venv/Scripts/python.exe"
)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Updated path to the pybind11 CMake directory in the new directory's virtual environment
set(pybind11_DIR
    "C:/Users/manu1/OneDrive/Desktop/MATCHING ENGINE UPDATED/backend/venv/Lib/site-packages/pybind11/share/cmake/pybind11"
)

find_package(pybind11 REQUIRED)

pybind11_add_module(myengine bindings.cpp)