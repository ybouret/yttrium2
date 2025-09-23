""" importing ctypes """
import ctypes as ct

""" IonoCell """
class IonoCell:

    def __init__(self):
        self.dll = ct.cdll.LoadLibrary("./ionocell.dll")


if __name__ == '__main__':
    chemsys = IonoCell()
    