
#include <Python.h>

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "google.protobuf.descriptor",
                                        "Protobuf Module",
                                        -1,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

PyObject* PyPB_CreateDescriptorModule() {
  return PyModule_Create(&module_def);
}
