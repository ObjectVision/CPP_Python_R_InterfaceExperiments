#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

int add(int i, int j) 
{
    return i + j;
}

PYBIND11_MODULE(PythonBindings, m) 
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");
}