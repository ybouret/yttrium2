""" Spyndle  """

import ctypes as ct
import sys


class Spyndle:
    """ load C++ library and start its application """

    @staticmethod
    def c_to_p(c_string):
        """ C-string to python string """
        return str(c_string, "utf-8")

    @staticmethod
    def p_to_c(p_string):
        """  python string to C-string """
        return bytes(p_string, "utf-8")

    def __init__(self, library_name):
        self.dll = ct.cdll.LoadLibrary(library_name)

        # init application
        self.init = self.dll.Spyndle_Init
        self.init.argtypes = []
        self.init.restype = ct.c_bool

        # quit application
        self.quit = self.dll.Spyndle_Quit
        self.quit.argtypes = []

        # report error reason, need to be converted
        self.what_ = self.dll.Spyndle_What
        self.what_.argtypes = []
        self.what_.restype = ct.c_char_p

        # report error location, need to be converted
        self.when_ = self.dll.Spyndle_When
        self.when_.argtypes = []
        self.when_.restype = ct.c_char_p

        # auto-create application
        if not self.init():
            self.must_quit()

        # and done

    def __del__(self):
        self.quit()

    def what(self):
        """ C++ reason to python string """
        return self.c_to_p(self.what_())

    def when(self):
        """ C++ location to python string """
        return self.c_to_p(self.when_())

    def must_quit(self):
        """ print error and exit """
        print("Error in IonoCell")
        print("Reason   : ", self.what())
        print("Location : ", self.when())
        sys.exit(1)
