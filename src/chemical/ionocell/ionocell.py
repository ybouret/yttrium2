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
        self.dll = ct.cdll.LoadLibrary("./ionocell.dll")

        self.what_ = self.dll.IonoCell_What
        self.what_.argtypes = []
        self.what_.restype = ct.c_char_p

        self.when_ = self.dll.IonoCell_When
        self.when_.argtypes = []
        self.when_.restype = ct.c_char_p

        self.init = self.dll.IonoCell_Init
        self.init.argtypes = []
        self.init.restype = ct.c_bool

        self.quit = self.dll.IonoCell_Quit
        self.quit.argtypes = []

        if not self.init():
            self.must_quit()

        self.declare_ = self.dll.IonoCell_declare
        self.declare_.restype = ct.c_bool
        self.declare_.argtypes = [ct.c_char_p]

    def __del__(self):
        self.quit()

    def what(self):
        """ C reason to python string """
        return self.c_to_p(self.what_())

    def when(self):
        """ C location to python string """
        return self.c_to_p(self.when_())

    def declare(self, some_code):
        if not self.declare_(self.p_to_c(some_code)):
            self.must_quit()

    def must_quit(self):
        """ print error and exit """
        print("Error in IonoCell")
        print("Reason   : ", self.what())
        print("Location : ", self.when())
        sys.exit(1)


if __name__ == '__main__':
    chemsys = IonoCell()
    chemsys.declare('Na^+ Cl^- %acetic')
