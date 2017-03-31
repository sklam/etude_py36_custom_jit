#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <frameobject.h>

#if PY_MAJOR_VERSION >= 3
  #define MOD_ERROR_VAL NULL
  #define MOD_SUCCESS_VAL(val) val
  #define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
  #define MOD_DEF(ob, name, doc, methods) { \
          static struct PyModuleDef moduledef = { \
            PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
          ob = PyModule_Create(&moduledef); }
  #define MOD_INIT_EXEC(name) PyInit_##name();
#else
  #define MOD_ERROR_VAL
  #define MOD_SUCCESS_VAL(val)
  #define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
  #define MOD_DEF(ob, name, doc, methods) \
          ob = Py_InitModule3(name, methods, doc);
  #define MOD_INIT_EXEC(name) init##name();
#endif

PyObject*
eval_frame(PyFrameObject *frame, int throwflag)
{
    printf("** myjit is evaluating frame=%p lasti=%d lineno=%d\n",
           frame, frame->f_lasti, frame->f_lineno);
    return _PyEval_EvalFrameDefault(frame, throwflag);
}

PyObject*
install_jit(PyObject *self)
{
    PyThreadState *tstate = PyThreadState_GET();
    tstate->interp->eval_frame = eval_frame;
    Py_RETURN_NONE;
}


static PyMethodDef ext_methods[] = {
    { "install_jit", (PyCFunction) install_jit, METH_NOARGS, NULL },
    { NULL },
};


MOD_INIT(_myjithook) {
    PyObject *m;
    MOD_DEF(m, "_myjithook", "No docs", ext_methods)
    if (m == NULL)
        return MOD_ERROR_VAL;

    return MOD_SUCCESS_VAL(m);
}
