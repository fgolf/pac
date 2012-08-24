#ifndef AT_CONSTANTS_H
#define AT_CONSTANTS_H

// physics contants

namespace at
{
	// Z constants
	// Mass m  = (91.1876 ± 0.0021) GeV    
	const double MZ     = 91.1876;
	const double MZ_err = 0.0021;

	// Full width Γ  = (2.4952 ± 0.0023) GeV    
	const double GammaZ     = 2.4952;
	const double GammaZ_err = 0.0023;

	// W constants
	// Mass m  = (80.399 ± 0.023) GeV    
	const double MW     = 80.399;
	const double MW_err = 0.023;

	//Full width Γ  = (2.085 ± 0.042) GeV    
	const double GammaW     = 2.085;
	const double GammaW_err = 0.042;

} // namespace at

// dummy function for linking
void AT__dummy_function_for_linking();


#endif // #define AT_CONSTANTS_H
