#pragma once

#include <unordered_map>
#include <string>

namespace TightBinding
{

	class Material
	{
	public:
		Material() : m_Esa(0), m_Epa(0), m_Esc(0), m_Epc(0), m_Esstara(0), m_Esstarc(0), m_Vss(0), m_Vxx(0), m_Vxy(0), m_Vsapc(0), m_Vscpa(0), m_Vsstarapc(0), m_Vpasstarc(0) {}

		Material(const std::string& Name, double Esa, double Epa, double Esc, double Epc, double Esstara, double Esstarc, double Vss, double Vxx, double Vxy, double Vsapc, double Vscpa, double Vsstarapc, double Vpasstarc);

		std::string name;


		// initialized with values from table 1 in P. Vogl et al.

		// a - anion, c - cation, s, p, sstar - the s, p and excited s orbitals, respectively
		double m_Esa;
		double m_Epa;
		double m_Esc;
		double m_Epc;
		double m_Esstara;
		double m_Esstarc;

		double m_Vss;
		double m_Vxx;
		double m_Vxy;
		double m_Vsapc;
		double m_Vscpa;
		double m_Vsstarapc;
		double m_Vpasstarc;
	};


	class Materials
	{
	public:
		Materials();

		const Material& getMaterial(const std::string& matName) const;

	private:
		std::unordered_map<std::string, Material> materials;
	};

}