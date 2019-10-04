#include <Python.h> 
// #include <python3.7/Python.h>
#include <stdio.h>
#include "ACSearch.h"

PyObject* find_all(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* py_patterns;
    PyObject* py_text;
    static char* kwlist[] = { (char*)"patterns", (char*)"text", nullptr };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", kwlist, &py_patterns, &py_text)) {
        std::cout << "PyArg Error" << std::endl;
        return nullptr;
    }
    std::vector<std::string> cpp_patterns;
    Py_ssize_t patterns_len = PyList_Size(py_patterns);
    for (int i=0; i<patterns_len; i++) {
        PyObject* py_pattern = PyList_GetItem(py_patterns, i);
        char* pattern_str = PyBytes_AsString(PyUnicode_AsUTF8String(py_pattern));
        cpp_patterns.push_back(pattern_str);
    }
    
    const char* text_str = PyBytes_AsString(PyUnicode_AsUTF8String(py_text));
    std::string cpp_text(text_str);
    zsh::ACSearchor searchor(cpp_patterns);
    std::map<std::string, std::vector<int>> cpp_ret = searchor.find(cpp_text);
    // 构建ret
    PyObject* py_ret = PyDict_New();
    for (auto pair: cpp_ret) {
        int len = pair.second.size();
        PyObject* py_index_list = PyList_New(len);
        for (int i=0; i<len; i++) {
            int index = pair.second[i];
            PyObject* py_index = Py_BuildValue("i", index);
            PyList_SetItem(py_index_list, i, py_index);
        }
        PyObject* py_key = PyUnicode_FromString(pair.first.c_str());
        PyDict_SetItem(py_ret, py_key, py_index_list);
    }
    return py_ret;
}

static PyMethodDef ACSearch_methods[] = {
    // The first property is the name exposed to Python, fast_tanh, the second is the C++
    // function name that contains the implementation.
    { "find_all", (PyCFunction)find_all, METH_VARARGS | METH_KEYWORDS, nullptr },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
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