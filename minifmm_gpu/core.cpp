#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include "bind_out.h"

static PyObject* py_myFunction(PyObject* self, PyObject* args)
{
    char *s = "Hello from C!";
    minifmm_no_args();
    return Py_BuildValue("s", s);
}

static PyMethodDef minifmm_methods[] =
{
  {"no_input", py_myFunction, METH_VARARGS},
  {NULL, NULL}
};

static struct PyModuleDef cModPyDem =
{
    PyModuleDef_HEAD_INIT,
    "no_input", "Some documentation",
    -1,
    minifmm_methods
};

PyMODINIT_FUNC
PyInit_minifmm(void)
{
    return PyModule_Create(&cModPyDem);
}
