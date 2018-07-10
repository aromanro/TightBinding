#include "Material.h"


namespace TightBinding
{


	Material::Material(const std::string& Name, double Esa, double Epa, double Esc, double Epc, double Esstara, double Esstarc, double Vss, double Vxx, double Vxy, double Vsapc, double Vscpa, double Vsstarapc, double Vpasstarc)
		: name(Name), m_Esa(Esa), m_Epa(Epa), m_Esc(Esc), m_Epc(Epc), m_Esstara(Esstara), m_Esstarc(Esstarc), m_Vss(Vss), m_Vxx(Vxx), m_Vxy(Vxy), m_Vsapc(Vsapc), m_Vscpa(Vscpa), m_Vsstarapc(Vsstarapc), m_Vpasstarc(Vpasstarc)
	{
	}


	Materials::Materials()
	{
		// complete with all compounds params from Table 1 from P. Vogl et al.
		materials["C"] = Material("C",  -4.545,  3.84, -4.545, 3.84, 11.37, 11.37, -22.7250, 3.8400, 11.6700, 15.2206, 15.2206, 8.2109, 8.2109);
		materials["Si"] = Material("Si", -4.2, 1.715, -4.2, 1.715, 6.685, 6.685, -8.3, 1.715, 4.575, 5.7292, 5.7292, 5.3749, 5.3749);
		materials["Ge"] = Material("Ge", -5.88, 1.61, -5.88, 1.61, 6.39, 6.39, -6.78, 1.61, 4.9, 5.4649, 5.4649, 5.2191, 5.2191);
		materials["Sn"] = Material("Sn", -5.67, 1.33, -5.67, 1.33, 5.9, 5.9, -5.67, 1.33, 4.08, 4.5116, 4.5116, 5.8939, 5.8939);
		materials["SiC"] = Material("SiC", -8.4537, 2.1234, -4.8463, 4.3466, 9.6534, 9.3166, -12.4197, 3.038, 5.9216, 9.49, 9.2007, 8.7138, 4.4051);
		materials["AlP"] = Material("AlP", -7.8466, 1.3169, -1.2534, 4.2831, 8.7069, 7.4231, -7.4535, 2.3749, 4.8378, 5.2451, 5.2775, 5.2508, 4.6388);
		materials["AlAs"] = Material("AlAs", -7.5273, 0.9833, -1.1627, 3.5867, 7.4833, 6.7267, -6.6642, 1.878, 4.2919, 5.1106, 5.4965, 4.5216, 4.995);
		materials["AlSb"] = Material("AlSb", -6.1714, 0.9807, -2.0716, 3.0163, 6.7607, 6.1543, -5.6448, 1.7199, 3.6648, 4.9121, 4.2137, 4.3662, 3.0739);
		materials["GaP"] = Material("GaP", -8.1124, 1.125, -2.1976, 4.115, 8.515, 7.185, -7.4709, 2.1516, 5.1369, 4.2771, 6.319, 4.6541, 5.095);
		materials["GaAs"] = Material("GaAs", -8.3431, 1.0414, -2.6569, 3.6686, 8.5914, 6.7386, -6.4513, 1.9546, 5.0779, 4.48, 5.7839, 4.8422, 4.8077);
		materials["GaSb"] = Material("GaSb", -7.3207, 0.8554, -3.8993, 2.9146, 6.6354, 5.9846, -6.1567, 1.5789, 4.1285, 4.9601, 4.6675, 4.9895, 4.218);
		materials["InP"] = Material("InP", -8.5274, 0.8735, -1.4826, 4.0465, 8.2635, 7.0665, -5.3614, 1.8801, 4.2324, 2.2265, 5.5825, 3.4623, 4.4814);
		materials["InAs"] = Material("InAs", -9.5381, 0.9099, -2.7219, 3.7201, 7.4099, 6.7401, -5.6052, 1.8398, 4.4693, 3.0354, 5.4389, 3.3744, 3.9097);
		materials["InSb"] = Material("InSb", -8.0157, 0.6738, -3.4643, 2.9162, 6.453, 5.9362, -5.5193, 1.4018, 3.8761, 3.788, 4.59, 3.5666, 3.4048);
		materials["ZnSe"] = Material("ZnSe", -11.8383, 1.5072, 0.0183, 5.9928, 7.5872, 8.9928, -6.2163, 3.0054, 5.9942, 3.498, 6.3191, 2.5891, 3.9533);
		materials["ZnTe"] = Material("ZnTe", -9.8150, 1.4834, 0.935, 5.2666, 7.0834, 8.2666, -6.5765, 2.7951, 5.467, 5.9827, 5.8199, 1.3196, 0.);
	}


}