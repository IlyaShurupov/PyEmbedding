
#include "PyEmbUtils.h"

#include "EmbClass.h"

#include "EmbObj.h"

static PyObject* Foo_init(PyObject* self, PyObject* args) {
  printf("Foo._ _init_ _ called\n");
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Foo_doSomething(PyObject* self, PyObject* args) {
  printf("Foo.doSomething called\n");

  PyObject** classDict = _PyObject_GetDictPtr(self);

  PyFloatObject* value = (PyFloatObject*)PyDict_GetItemString(*classDict, "ref");

  value->ob_fval = 100;

  //PyLong_FromLong();

  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef FooMethods[] = {
  {"_ _init_ _", Foo_init, METH_VARARGS, "doc string"},
  {"foo", Foo_doSomething, METH_VARARGS, "doc string"},
  {NULL, NULL},
};


// ---------------------------------- Emb Initialization ---------------------------------- 

void EmbObj_PreInitialize() {
}

void EmbObj_PostInitialize() {

  PyObject* fooClass = PyClass_Create("embClass", FooMethods, PyTuple_New(0));

  PyObject** classDict = _PyObject_GetDictPtr(fooClass);

  //PyDict_SetItemString(*classDict, "ref", PyFloat_FromDouble(10));
  PyDict_SetItemString(*classDict, "ref", PyEmbObject_New());

  PyObject* module = PyImport_ImportModule("EmbMod");
  PyObject* moduleDict = PyModule_GetDict(module);
  PyDict_SetItemString(moduleDict, "embClass", fooClass);
  Py_DECREF(fooClass);
}
