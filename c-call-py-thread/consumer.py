#!/usr/bin/python
import threading
import time
def do_task(name):
    print(name,"start...")
    time.sleep(1)
    print(name,"done")

def requests_ops(msg):
    print(msg)
    threads = []
    for i in range(10):
        thread = threading.Thread(target=do_task, args=(msg,))
        thread.start()
        threads.append(thread)
    for t in threads:
        t.join()
    return 0

