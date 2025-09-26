""" importing ctypes """
import ctypes as ct

class Simple:

    def __init__(self):
        print("-- create --")
        self.dll = ct.cdll.LoadLibrary("./simple.dll")
        self.sine = self.dll.sine
       
        self.sine.argtypes = [ct.c_double]
        self.sine.restype = ct.c_double

        self.Init = self.dll.Simple_Init
        self.Init.argtypes = []
        self.Init.restype = ct.c_bool

        self.Quit = self.dll.Simple_Quit
        self.Quit.argtypes = []

        assert self.Init()

    def __del__(self):
        print("-- delete --")
        self.Quit()

print("-- main --")
simple = Simple()
print( simple.sine(0.1) )
print("-- done --")
