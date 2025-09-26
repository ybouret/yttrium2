""" importing ctypes """
import ctypes as ct

class Simple:

    def __init__(self):
        print("-- init --")
        self.dll = ct.cdll.LoadLibrary("./simple.dll")
        self.sine = self.dll.sine
        self.sine.argtypes = [ct.c_double]
        self.sine.restype = ct.c_double

simple = Simple()
print( simple.sine(0.1) )