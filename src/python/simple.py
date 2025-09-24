""" importing ctypes """
import ctypes as ct

class Simple:

    def __init__(self):
        print("-- init --")
        self.dll = ct.cdll.LoadLibrary("./simple.dll")


simple = Simple()
