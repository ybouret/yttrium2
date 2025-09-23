""" importing ctypes """
import ctypes as ct

""" Application Prototype """
class Application:

    def __init__(self):
        self.dll = ct.cdll.LoadLibrary("./typyc.so")

        # example of sine function
        self.sine = self.dll.sine
        self.sine.argtypes = [ct.c_double]
        self.sine.restype = ct.c_double

        self.what = self.dll.ApplicationWhat
        self.what.restype = ct.c_char_p

        self.was_init = self.dll.ApplicationInit
        self.was_init.restype = ct.c_bool
        assert self.was_init()
        print( self.what() )

        self.norm = self.dll.ApplicationNorm
        self.norm.restype = ct.c_double
        self.norm.argtypes = [ct.c_double,ct.c_double]

app = Application()
print( app.sine(0.1) )
print( app.norm(3,4) )