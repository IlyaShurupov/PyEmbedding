
#include "Interp.h"

#include"PyEmbUtils.h"

#include "EmbClass.h"


static PyMethodDef ModuleMethods[] = { {NULL, NULL} };
static struct PyModuleDef cModPyDem = { PyModuleDef_HEAD_INIT, "EmbMod", "", -1, ModuleMethods };

PyMODINIT_FUNC PyInit_cModPyDem(void) {
	return PyModule_Create(&cModPyDem);
}

PyInterp::PyInterp() {

	PyImport_AppendInittab("EmbMod", PyInit_cModPyDem);

	EmbObj_PreInitialize();
	Py_Initialize();
	EmbObj_PostInitialize();
}

void PyInterp::exec(std::string cmd) {
	PyRun_SimpleString(cmd.c_str());
}

PyInterp::~PyInterp() {
	Py_Finalize();
}

