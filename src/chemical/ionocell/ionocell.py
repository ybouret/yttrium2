""" importing ctypes """
import ctypes as ct
import sys

""" IonoCell """
class IonoCell:

    def __init__(self):
        self.dll  = ct.cdll.LoadLibrary("./ionocell.dll")

        self.what = self.dll.IonoCell_What
        self.what.restype = ct.c_char_p

        self.when = self.dll.IonoCell_When
        self.when.restype = ct.c_char_p

        self.declare = self.dll.IonoCell_declare
        self.declare.restype = ct.c_bool
        self.declare.argtypes = [ct.c_char_p]

    def mustQuit(self):
        print("Error in IonoCell")
        print( "Reason   : ", str(self.what(), "utf-8") )
        print( "Location : ", str(self.when(), "utf-8") )
        sys.exit(1)

if __name__ == '__main__':
    chemsys = IonoCell()
    if not chemsys.declare(b"Na^+ Cl^- toto"):
        chemsys.mustQuit()