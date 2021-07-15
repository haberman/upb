
#include <Python.h>

#include "descriptor.h"

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "google.protobuf",
                                        "Protobuf Module",
                                        -1,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

PyMODINIT_FUNC
PyInit_protobuf(void) {
  PyObject* m = PyModule_Create(&module_def);
  PyModule_AddObject(m, "descriptor", PyPB_CreateDescriptorModule());
  return m;
}
