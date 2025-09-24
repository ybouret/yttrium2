""" importing ctypes """
import ctypes as ct

""" IonoCell """
class IonoCell:

    def __init__(self):
        self.dll  = ct.cdll.LoadLibrary("./ionocell.dll")
        self.decl = self.dll.IonoCell_decl
        self.decl.restype = ct.c_bool
        self.decl.argtypes = [ct.c_char_p]

if __name__ == '__main__':
    chemsys = IonoCell()
    chemsys.decl(b"Na^+")