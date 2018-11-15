#include "krome.hpp"
#include "krome_user.cpp"

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	krome_init();

	// Set the radiation field bins to logspacing, and the field itself to a blackbody
	double low_eV = 1;
	double high_eV = 24;
	double Tc = 30000;
	krome_set_photobin_bblog(low_eV, high_eV, Tc);

	int ie = krome_idx_E;
	int ih = krome_idx_H;
	int ih2 = krome_idx_H2;
	int ip = krome_idx_Hj;
	int numSpecies = krome_nmols;
	std::cout << "krome hydrogen at index " << krome_idx_H << "out of " << numSpecies << std::endl;

	// Initial densities in cm-3. The indices are accessible from krome_user.h
	std::vector<double> x(4, 0);
	x[ih] = 1e4;
	int verbosity = 0;

	// Output file
	std::ofstream outfile("equilibrium_densities");
	for (double T = 10; T < 100000; T *= 1.1)
	{
		krome_equilibrium(x.data(), T, &verbosity);
		outfile << T;
		for (int i = 0; i < numSpecies; i++)
			outfile << " " << x[i];
		outfile << '\n';
	}
	outfile.close();
}
