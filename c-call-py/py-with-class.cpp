#include <Python.h>
#include <iostream>
#include <string>

int main () {

    //使用python之前，要调用Py_Initialize();这个函数进行初始化
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject * pModule = NULL;
    PyObject * pFunc = NULL;
    PyObject * pClass = NULL;
    PyObject * pInstance = NULL;
        PyObject *pArgs, *pValue;
    //这里是要调用的文件名
    pModule = PyImport_ImportModule("py-with-class");
    //这里是要调用的函数名
    pFunc= PyObject_GetAttrString(pModule, "hello");
    //调用函数
    PyEval_CallObject(pFunc, NULL);
    Py_DECREF(pFunc);

        /* build args */
        pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs,0, PyString_FromString("asdfasf"));
    pFunc = PyObject_GetAttrString(pModule, "world");
        pValue = PyObject_CallObject(pFunc, pArgs);
    //PyObject_CallFunction(pFunc, "zhengji");
    //Py_DECREF(pFunc);

    //测试调用python的类
    pClass = PyObject_GetAttrString(pModule, "Student");
    if (!pClass) {
        printf("Can't find Student class.\n");
        return -1;
    }
    pInstance = PyInstance_New(pClass, NULL, NULL);
    if (!pInstance) {
        printf("Can't create Student instance.\n");
        return -1;
    }
    PyObject_CallMethod(pInstance, "SetName", "s","my family");
    PyObject_CallMethod(pInstance, "PrintName",NULL,NULL);
    //调用Py_Finalize，这个根Py_Initialize相对应的。
    Py_Finalize();
    return 0;
}
