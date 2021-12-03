
#include "PyEmbUtils.h"

PyObject* PyClass_Create(const char* name, PyMethodDef methods[], PyObject* pClassBases) {

  PyObject* classDict = PyDict_New();
  PyObject* className = PyUnicode_FromString(name);

  // add methods to class 
  PyMethodDef* def;
  for (def = methods; def->ml_name != NULL; def++) {

    PyObject* func = PyCFunction_New(def, NULL);
    PyObject* method = PyInstanceMethod_New(func);
    PyDict_SetItemString(classDict, def->ml_name, method);
    Py_DECREF(func);
    Py_DECREF(method);
  }
  
  PyObject* pClass = PyObject_CallFunctionObjArgs((PyObject*)&PyType_Type, className, pClassBases, classDict, NULL);

  Py_DECREF(className);
  Py_DECREF(pClassBases);
  Py_DECREF(classDict);

  return pClass;
}