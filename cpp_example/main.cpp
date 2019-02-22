#include "krome.hpp"
#include "krome_user.hpp"

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	krome_init();

	// Set the radiation field bins to logspacing, and the field itself to a blackbody
	double low_eV = 1;
	double high_eV = 24;
	double Tc = 2950;
	krome_set_photobin_bblog(low_eV, high_eV, Tc);
	// Myflux should be the radiation background at 12.87 eV
	double flux12_87 = krome_get_photointensity(12.87);
	krome_set_user_myfluxuv(flux12_87);
	std::cout << "myfluxuv = " << flux12_87 << std::endl;

	// Write out the radiation field in eV / cm2 / sr / eV
	std::vector<double> ev(krome_nPhotoBins);
	std::vector<double> jv(krome_nPhotoBins);
	krome_get_photobine_mid(ev.data());
	krome_get_photobinj(jv.data());

	std::ofstream radf("photobinj.dat");
	radf << "# Emid (eV)\tJ (eV / cm2 / sr)\n";
	for (int i = 0; i < krome_nPhotoBins; i++)
		radf << ev[i] << '\t' << jv[i] << '\n';
	radf.close();

	// Set a fixed H2 formation rate (per H)
	double kGrainH2 = 2e-15;
	krome_set_user_grainh2_rate(kGrainH2);

	int ie = krome_idx_E;
	int ih = krome_idx_H;
	int ih2 = krome_idx_H2;
	int ip = krome_idx_Hj;
	int numSpecies = krome_nmols;
	for (int i = 0; i < krome_nmols; i++)
	{
		std::cout << i << " " << krome_names[i] << " | ";
	}
	std::cout << std::endl;
	std::cout << "krome hydrogen at index " << krome_idx_H << " out of " << numSpecies << std::endl;

	// Initial densities in cm-3. The indices are accessible from krome_user.h
	std::vector<double> x(4, 0);
	x[ih] = 1e4;
	int verbosity = 0;

	// Output file
	std::string outfname = "equilibrium_densities";
	std::ofstream outfile(outfname);
	outfile << "# T densities heat cool rates\n";
	for (double T = 10; T < 100000; T *= 1.1)
	{
		krome_equilibrium(x.data(), T, &verbosity);
		double heat = krome_get_heating(x.data(), T);
		double cool = krome_get_cooling(x.data(), T);
		std::vector<double> coefs(krome_nrea);
		krome_get_coef(T, x.data(), coefs.data());
		// krome_get_photobin_rates(photoRates.data());

		outfile << T;
		for (int i = 0; i < numSpecies; i++)
			outfile << " " << x[i];
		outfile << " " << heat << " " << cool;
		for (double c : coefs)
			outfile << " " << c;
		outfile << '\n';
	}
	outfile.close();
	std::cout << "wrote to " << outfname << std::endl;
}
