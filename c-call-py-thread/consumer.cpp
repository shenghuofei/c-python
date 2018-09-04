#include <Python.h>
#include <iostream>
#include <string>

using namespace std;

int great_function_from_python(char *a) {
    cout << a << endl;
    int res = 0;
    int nHold = PyGILState_Check() ;   //检测当前线程是否拥有GIL,python 3+可以用
    PyGILState_STATE gstate;
    if ( !nHold )
    {
        gstate = PyGILState_Ensure();   //如果没有GIL，则申请获取GIL
    }
    Py_BEGIN_ALLOW_THREADS;
    Py_BLOCK_THREADS;
   
    // If my MyPython.py file is in "/Users/xx/code", set the working path to "/Users/xx/code"
    // string path = "/Users/xx/code";
    // PySys_SetPath(&path[0u]); 
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
   
    PyObject *pModule,*pFunc; 
    PyObject *pArgs, *pValue;
    //这里是要调用的文件名
    pModule = PyImport_ImportModule("consumer");
    if (!pModule) // 加载模块失败
    {
        cout << "[ERROR] Python get module failed." << endl;
        return 1;
    }
    /* build args */
    pArgs = PyTuple_New(1);
    //PyTuple_SetItem(pArgs,0,PyString_FromString(a));
    //PyTuple_SetItem(pArgs,0,PyBytes_FromString(a));
    PyTuple_SetItem(pArgs,0,PyUnicode_FromString(a));
    //这里是要调用的函数名
    pFunc = PyObject_GetAttrString(pModule, "requests_ops");
    if (!pFunc || !PyCallable_Check(pFunc))  // 验证是否加载成功
    {
        cout << "[ERROR] Can't find funftion " << endl;
        return 2;
    }
    pValue = PyObject_CallObject(pFunc, pArgs);
    //PyObject_CallFunction(pFunc, "zhengji");
    //PyObject_CallFunction(pFunc,"s", pArgs);
    if (pValue)  // 验证是否调用成功
    {
        res = PyLong_AsLong(pValue);
        cout << "result:" << res << endl;
    } 
    //cout << res << endl; 
    Py_DECREF(pArgs); 
    Py_DECREF(pFunc); 
    Py_DECREF(pModule);
    
    Py_UNBLOCK_THREADS;
    Py_END_ALLOW_THREADS;
    if (!nHold)
    {
        PyGILState_Release(gstate);    //释放当前线程的GIL
    } 
    return res;
}
int main(int argc, char *argv[]) {
    //使用python之前，要调用Py_Initialize();这个函数进行初始化
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        cout << "Python initialization failed!" << endl;
        return 3;
    }
    else {
        PyEval_InitThreads();     //开启多线程支持
        int nInit = PyEval_ThreadsInitialized();  //检测线程支持是否开启成功
        if ( nInit )
        {
            PyEval_SaveThread();  //因为调用PyEval_InitThreads成功后，当前线程就拥有了GIL，释放当前线程的GIL，
        }
    }
    return great_function_from_python("{'a':'b'}"); 
    //调用Py_Finalize，这个根Py_Initialize相对应的,必须在python调用完以后执行,否则找不到python module
    Py_Finalize();
}
