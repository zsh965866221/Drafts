#include <Python.h> 
// #include <python3.7/Python.h>
#include <stdio.h>
#include "ACSearch.h"


PyObject* find_all(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* py_patterns;
    PyObject* py_text;
    static char* kwlist[] = { (char*)"patterns", (char*)"text", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", kwlist, &py_patterns, &py_text)) {
        printf("PyArg Error\n");
        return NULL;
    }
    Vector* c_patterns = Vector_New();
    Py_ssize_t patterns_len = PyList_Size(py_patterns);
    for (int i=0; i<patterns_len; i++) {
        PyObject* py_pattern = PyList_GetItem(py_patterns, i);
        char* pattern_str = PyBytes_AsString(PyUnicode_AsUTF8String(py_pattern));
        Vector_Push(c_patterns, pattern_str);
    }
    
    char* text_str = PyBytes_AsString(PyUnicode_AsUTF8String(py_text));
    ACSearch* search = ACSearch_New(c_patterns);
    Map* ret = ACSearch_FindAll(search, text_str);
    // 构建ret
    PyObject* py_ret = PyDict_New();
    for (int i=0; i<ret->max_size; i++) {
        Map_Node* base = ret->values[i];
        Map_Node* p = base->right;
        while (p != NULL) {
            char* key = p->key;
            void* value = p->value;
            // begin
            Vector* vector = (Vector*)value;
            int len = vector->size;
            PyObject* py_index_list = PyList_New(len);
            for (int i=0; i<len; i++) {
                int index = Vector_Get_Int_Index(vector, i);
                PyObject* py_index = Py_BuildValue("i", index);
                PyList_SetItem(py_index_list, i, py_index);
            }
            PyObject* py_key = PyUnicode_FromString(key);
            PyDict_SetItem(py_ret, py_key, py_index_list);
            // end
            p = p->right;
        }
    }
    return py_ret;
}

static PyMethodDef ACSearch_methods[] = {
    // The first property is the name exposed to Python, fast_tanh, the second is the C++
    // function name that contains the implementation.
    { "find_all", (PyCFunction)find_all, METH_VARARGS | METH_KEYWORDS, NULL },

    // Terminate the array with an object containing nulls.
    { NULL, NULL, 0, NULL }
};

static PyModuleDef ACSearch_module = {
    PyModuleDef_HEAD_INIT,
    "ACSearch",                        // Module name to use with Python import statements
    "ACSearch",  // Module description
    0,
    ACSearch_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_ACSearch() {
    return PyModule_Create(&ACSearch_module);
}