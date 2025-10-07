""" importing ctypes """
import ctypes as ct
import sys


class Spyndle:
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


class Species:
    """ contains constitutive information """

    def __init__(self, sp_name, sp_z, sp_latex):
        self.name = sp_name
        self.z = sp_z
        self.latex = sp_latex

    def __str__(self):
        return self.name

    def as_conc(self):
        """ return [name] """
        return '[' + self.name + ']'


class IonoCell(Spyndle):
    """ interface to C++ code """

    def __init__(self):
        super().__init__("./ionocell.dll")

        # parse species/equilibria...
        self.parse_ = self.dll.IonoCell_parse
        self.parse_.restype = ct.c_bool
        self.parse_.argtypes = [ct.c_char_p]

        # number of species
        self.num_species = self.dll.IonoCell_numSpecies
        self.num_species.argtypes = []
        self.num_species.restype = ct.c_size_t

        # name of species
        self.get_species_name_ = self.dll.IonoCell_getSpeciesName
        self.get_species_name_.restype = ct.c_char_p
        self.get_species_name_.argstype = []

        # charge of species
        self.get_species_z = self.dll.IonoCell_getSpeciesZ
        self.get_species_z.restype = ct.c_int
        self.get_species_z.argstype = []

        # latex code for species
        self.get_species_latex_ = self.dll.IonoCell_getSpeciesLaTeX
        self.get_species_latex_.restype = ct.c_char_p
        self.get_species_latex_.argstype = []

        # query coefficient of diffusion
        self.get_diff_coef_ = self.dll.IonoCell_getD
        self.get_diff_coef_.restype = ct.c_double
        self.get_diff_coef_.argstype = [ct.c_char_p]

        self.species = []

    def parse(self, some_code):
        """ send code to C++ to declare species and equilibria """

        # first: compile code
        if not self.parse_(self.p_to_c(some_code)):
            self.must_quit()

        # second: collect species
        self.collect_species()

    def must_quit(self):
        """ print error and exit """
        print("Error in IonoCell")
        print("Reason   : ", self.what())
        print("Location : ", self.when())
        sys.exit(1)

    def get_species_name(self, i):
        """ get name of i-th species """
        return self.c_to_p(self.get_species_name_(i))

    def get_species_latex(self, i):
        """ get LaTeX formula for i-th species """
        return self.c_to_p(self.get_species_latex_(i))

    def get_diffusion_coefficient(self, name):
        """ query diffusion coefficient for given name, -1 if unknown """
        return self.get_diff_coef_(self.p_to_c(name))

    def collect_species(self):
        """ collect existing species from populated library """
        self.species = []
        for i in range(self.num_species()):
            the_name = self.get_species_name(i)
            the_z = self.get_species_z(i)
            the_tex = self.get_species_latex(i)
            the_species = Species(the_name, the_z, the_tex)
            self.species.append(the_species)


if __name__ == '__main__':
    chemsys = IonoCell()
    chemsys.parse('Na^+ Cl^- %acetic')
    print(len(chemsys.species))
    for sp in chemsys.species:
        print(sp, "D=", chemsys.get_diffusion_coefficient(sp.name))
