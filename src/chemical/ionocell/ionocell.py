""" IonoCell """

import ctypes as ct
from spyndle import Spyndle


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
