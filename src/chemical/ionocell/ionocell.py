""" importing ctypes """
import ctypes as ct
import sys

""" IonoCell """
class IonoCell:

    def __init__(self):
        self.dll  = ct.cdll.LoadLibrary("./ionocell.dll")

        self.what = self.dll.IonoCell_What
        self.what.argtypes = []
        self.what.restype = ct.c_char_p

        self.when = self.dll.IonoCell_When
        self.when.argtypes = []
        self.when.restype = ct.c_char_p

        self.Init = self.dll.IonoCell_Init
        self.Init.argtypes = []
        self.Init.restype = ct.c_bool

        self.Quit = self.dll.IonoCell_Quit
        self.Quit.argtypes = []

        if not self.Init():
            self.mustQuit()


        self.declare_ = self.dll.IonoCell_declare
        self.declare_.restype = ct.c_bool
        self.declare_.argtypes = [ct.c_char_p]

        #self.numSpecies = self.dll.IonoCell_numSpecies
        #self.numSpecies.restype = ct.c_size_t
        #self.numSpecies.argtypes = []

        #self.getSpeciesName_ = self.dll.IonoCell_getSpeciesName
        #self.getSpeciesName_.restype = ct.c_char_p
        #self.getSpeciesName_.argtypes = [ct.c_size_t]

        #self.getSpeciesCharge = self.dll.IonoCell_getSpeciesCharge
        #self.getSpeciesCharge.restype = ct.c_int
        #self.getSpeciesCharge.argtypes = [ct.c_size_t]

    def __del__(self):
        self.Quit()

    def declare(self,python_string):
        if not self.declare_( bytes(python_string,"utf-8")):
            self.mustQuit()

    def getSpeciesName(self,i):
        return str( self.getSpeciesName_(i), "utf-8")

    def mustQuit(self):
        print("Error in IonoCell")
        print( "Reason   : ", str(self.what(), "utf-8") )
        print( "Location : ", str(self.when(), "utf-8") )
        sys.exit(1)

if __name__ == '__main__':
    chemsys = IonoCell()
    chemsys.declare('Na^+ Cl^- %acetic')
    #if not chemsys.declare(b"Na^+ Cl^-"):
    #    chemsys.mustQuit()
    #M = chemsys.numSpecies()
    #print("numSpecies = ", M )
    #for i in range(M):
    #    spName = chemsys.getSpeciesName(i)
    #    spCharge = chemsys.getSpeciesCharge(i)
    #    print("#",i," : ", spName, ":", "z=", spCharge)
