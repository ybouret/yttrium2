""" importing ctypes """
import ctypes as ct

""" Application Prototype """
class Application:

    def __init__(self):
        self.dll = ct.cdll.LoadLibrary("./typyc.so")
        self.sine = self.dll.sine
        self.sine.argtypes = [ct.c_double]
        self.sine.restype = ct.c_double
        #self.was_init = self.dll.ApplicationInit
        #self.was_init.restype = ct.c_bool
        #print( self.was_init() )

app = Application()
