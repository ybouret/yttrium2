""" importing ctypes """
import ctypes as ct


class Application:

    def __init__(self):
        self.dll = ct.cdll.LoadLibrary("./typyc.so")
        self.dll.sine.argtypes = [ct.c_double]
        self.dll.sine.restype = ct.c_double
        self.sine = self.dll.sine


app = Application()
