#!/usr/bin/python
import ctypes
dll=ctypes.cdll.LoadLibrary
lib=dll("./cpp_dll.so") #in windows use dll
print "python call cpp dll:"
lib.add_func(2,3)
lib.msg_func('{"a":"b"}')
