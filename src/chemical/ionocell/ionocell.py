""" importing ctypes """
import ctypes as ct
import sys


class IonoCell:
    """ interface to C++ code """

    @staticmethod
    def c_to_p(c_string):
        """ C-string to python string """
        return str(c_string, "utf-8")

    @staticmethod
    def p_to_c(p_string):
        """  python string to C-string """
        return bytes(p_string, "utf-8")

    def __init__(self):
        # loading code
        self.dll = ct.cdll.LoadLibrary("./ionocell.dll")

        # report error reason, need to be converted
        self.what_ = self.dll.IonoCell_What
        self.what_.argtypes = []
        self.what_.restype = ct.c_char_p

        # report error location, need to be converted
        self.when_ = self.dll.IonoCell_When
        self.when_.argtypes = []
        self.when_.restype = ct.c_char_p

        # init application
        self.init = self.dll.IonoCell_Init
        self.init.argtypes = []
        self.init.restype = ct.c_bool

        # quit application
        self.quit = self.dll.IonoCell_Quit
        self.quit.argtypes = []

        # auto-create application
        if not self.init():
            self.must_quit()

        # parse species/equilibria...
        self.parse_ = self.dll.IonoCell_parse
        self.parse_.restype = ct.c_bool
        self.parse_.argtypes = [ct.c_char_p]

        # number of species
        self.numSpecies = self.dll.IonoCell_numSpecies
        self.numSpecies.argtypes = []
        self.numSpecies.restype = ct.c_size_t

    def __del__(self):
        self.quit()

    def what(self):
        """ C++ reason to python string """
        return self.c_to_p(self.what_())

    def when(self):
        """ C++ location to python string """
        return self.c_to_p(self.when_())

    def parse(self, some_code):
        """ send code to C++ to declare species and equilibria """
        if not self.parse_(self.p_to_c(some_code)):
            self.must_quit()

    def must_quit(self):
        """ print error and exit """
        print("Error in IonoCell")
        print("Reason   : ", self.what())
        print("Location : ", self.when())
        sys.exit(1)


if __name__ == '__main__':
    chemsys = IonoCell()
    chemsys.parse('Na^+ Cl^- %acetic')
    M = chemsys.numSpecies()
    print("M =",M)
