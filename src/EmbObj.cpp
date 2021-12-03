
#include "PyEmbUtils.h"
#include "EmbObj.h"

class EmbClass {
public:

	long val = 0;
	long val2 = 0;

	EmbClass() {
	}

	~EmbClass() {
	}


};

typedef struct {
	PyObject_HEAD
		EmbClass* m_ptr;  /* our const char* member */
} Py_EmbObj;


PyObject* PyEmbObject_New() {
	if (PyType_Ready(&Py_EmbObjType) < 0) {
		return NULL;
	}

	return Py_EmbObjType.tp_new(&Py_EmbObjType, NULL, NULL);
}

static PyObject* Emb_new(PyTypeObject* type, PyObject* args, PyObject* kwargs) {

	Py_EmbObj* out = (Py_EmbObj*)PyObject_Malloc(sizeof(Py_EmbObj));

	out->ob_base.ob_type = type;
	out->ob_base.ob_refcnt = 1;

	out->m_ptr = new EmbClass();

	return (PyObject*)out;
}

PyObject* Emb_vectorcall(PyObject* callable, PyObject* const* args, size_t nargsf, PyObject* kwnames) {
	return  PyEmbObject_New();
}

void Emb_dealloc(Py_EmbObj* self) {
	delete self->m_ptr;
}

PyObject* Emb_repr(PyObject* self) {
	return PyUnicode_FromString(self->ob_type->tp_name);
}

static PyObject* EmbObj_get_child(PyObject* self, PyObject* Py_UNUSED(args)) {
	return PyEmbObject_New();
}

static PyObject* EmbObj_set(PyObject* self, PyObject* args) {
	return PyLong_FromDouble(0);
}

static PyMethodDef Emb_methods[] = {
	{"get_child", EmbObj_get_child, METH_NOARGS, "doc get_info"},
	{"set", EmbObj_set, METH_NOARGS, "doc get_info"},
	{NULL, NULL},
};

static PyTypeObject Py_EmbObjType = {

		 PyVarObject_HEAD_INIT(&PyType_Type, 0)

		 "EmbObj",                                   /* tp_name */
		 sizeof(Py_EmbObj),                          /* tp_basicsize */
		 0,                                          /* tp_itemsize */
		 (destructor)Emb_dealloc,                    /* tp_dealloc */
		 0,                                          /* tp_print */
		 0,                                          /* tp_getattr */
		 0,                                          /* tp_setattr */
		 0,                                          /* tp_reserved */
		 (reprfunc)Emb_repr,                         /* tp_repr */
		 0,                                          /* tp_as_number */
		 0,                                          /* tp_as_sequence */
		 0,                                          /* tp_as_mapping */
		 0,                                          /* tp_hash */
		 0,                                          /* tp_call */
		 0,                                          /* tp_str */
		 0,                                          /* tp_getattro */
		 0,                                          /* tp_setattro */
		 0,                                          /* tp_as_buffer */
		 Py_TPFLAGS_DEFAULT,                         /* tp_flags */
		 "emb Obj doc",                              /* tp_doc */
		 0,                                          /* tp_traverse */
		 0,                                          /* tp_clear */
		 0,                                          /* tp_richcompare */
		 0,                                          /* tp_weaklistoffset */
		 0,                                          /* tp_iter */
		 0,                                          /* tp_iternext */
		 Emb_methods,                                /* tp_methods */
		 0,                                          /* tp_members */
		 0,                                          /* tp_getset */
		 0,                                          /* tp_base */
		 0,                                          /* tp_dict */
		 0,                                          /* tp_descr_get */
		 0,                                          /* tp_descr_set */
		 0,                                          /* tp_dictoffset */
		 0,                                          /* tp_init */
		 0,                                          /* tp_alloc */
		 (newfunc)Emb_new,                           /* tp_new */
		 0,                                          /* tp_free */
		 0,                                          /* tp_is_gc */
		 0,                                          /* tp_bases; */
		 0,                                          /* tp_mro; */
		 0,                                          /* tp_cache */
		 0,                                          /* tp_subclasses */
		 0,                                          /* tp_weaklist */
		 0,                                          /* tp_del */
		 0,                                          /* tp_version_tag */
		 0,																					 /* tp_finalize */
		 (vectorcallfunc)Emb_vectorcall,             /* vectorcallfunc */
};