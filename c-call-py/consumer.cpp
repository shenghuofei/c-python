#include <Python.h>
#include <iostream>
#include <string>

using namespace std;

int great_function_from_python(char *a) {
    cout << a << endl;
    int res = 0;
    //使用python之前，要调用Py_Initialize();这个函数进行初始化
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject *pModule,*pFunc;
    PyObject *pArgs, *pValue;
    //这里是要调用的文件名
    pModule = PyImport_ImportModule("consumer");
    /* build args */
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs,0,PyString_FromString(a));
    //这里是要调用的函数名
    pFunc = PyObject_GetAttrString(pModule, "requests_ops");
    pValue = PyObject_CallObject(pFunc, pArgs);
    //PyObject_CallFunction(pFunc, "s", "zhengji"); 参数说明:pFunc要调用的函数对象, s参数类型(string), 后面是具体参数
    //Py_DECREF(pFunc);

    res = PyInt_AsLong(pValue);
    //cout << res << endl;
    //调用Py_Finalize，这个根Py_Initialize相对应的。
    Py_Finalize();
    return res;
}
int main(int argc, char *argv[]) {
   return great_function_from_python('{"a":"b"}');
}
