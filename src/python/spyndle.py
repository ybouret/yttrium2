""" importing ctypes """
import ctypes as ct

class Application:

    def __init__(self):
        print("-- create --")
        self.dll = ct.cdll.LoadLibrary("./spyndle.dll")
        self.sine = self.dll.sine
       
        self.sine.argtypes = [ct.c_double]
        self.sine.restype = ct.c_double

        self.What = self.dll.Application_What
        self.What.argtypes = []
        self.What.restype = ct.c_char_p

        self.When = self.dll.Application_When
        self.When.argtypes = []
        self.When.restype = ct.c_char_p

        self.Init = self.dll.Application_Init
        self.Init.argtypes = []
        self.Init.restype = ct.c_bool

        self.Quit = self.dll.Application_Quit
        self.Quit.argtypes = []

        assert self.Init(), self.what()

        self.norm = self.dll.Application_norm
        self.norm.argtypes = [ct.c_double,ct.c_double]
        self.norm.restype = ct.c_double

        self.name_ = self.dll.Application_callSign
        self.name_.argtypes = []
        self.name_.restype = ct.c_char_p

        self.crc = self.dll.Application_crc
        self.crc.argtypes = [ct.c_char_p]
        self.crc.restype = ct.c_uint32

    def __del__(self):
        print("-- delete --")
        self.Quit()

    def what(self):
        return str(self.What(),"utf-8")
    
    def what(self):
        return str(self.When(),"utf-8")
    
    def callSign(self):
        return str(self.name_(),"utf-8")

print("-- main --")
app = Application()
print( app.sine(0.1) )
print( app.norm(3,4) )
print( app.callSign() )
print( app.crc( bytes("Hello","utf-8") ) )
print("-- done --")
