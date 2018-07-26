#include "Hamiltonian.h"


#define _USE_MATH_DEFINES 1
#include <math.h>

namespace TightBinding
{

	Hamiltonian::Hamiltonian(const Material& material)
		: m_material(material)
	{

	}


	inline std::complex<double> Hamiltonian::g0(const Vector3D<double>& k)
	{
		const Vector3D<double> v = k * M_PI / 2.;

		return std::complex<double>(cos(v.X) * cos(v.Y) * cos(v.Z), -sin(v.X) * sin(v.Y) * sin(v.Z));
	}
	
	inline std::complex<double> Hamiltonian::g1(const Vector3D<double>& k)
	{
		const Vector3D<double> v = k * M_PI / 2.;

		return std::complex<double>(-cos(v.X) * sin(v.Y) * sin(v.Z), sin(v.X) * cos(v.Y) * cos(v.Z));
	}
	

	inline std::complex<double> Hamiltonian::g2(const Vector3D<double>& k)
	{
		const Vector3D<double> v = k * M_PI / 2.;

		return std::complex<double>(-sin(v.X) * cos(v.Y) * sin(v.Z), cos(v.X) * sin(v.Y) * cos(v.Z));
	}
	

	inline std::complex<double> Hamiltonian::g3(const Vector3D<double>& k)
	{
		const Vector3D<double> v = k * M_PI / 2.;

		return std::complex<double>(-sin(v.X) * sin(v.Y) * cos(v.Z), cos(v.X) * cos(v.Y) * sin(v.Z));
	}

	void Hamiltonian::SetMatrix(const Vector3D<double>& k)
	{
		const std::complex<double> g0v = g0(k);
		const std::complex<double> g1v = g1(k);
		const std::complex<double> g2v = g2(k);
		const std::complex<double> g3v = g3(k);

		const std::complex<double> g0vc = std::conj(g0v);
		const std::complex<double> g1vc = std::conj(g1v);
		const std::complex<double> g2vc = std::conj(g2v);
		const std::complex<double> g3vc = std::conj(g3v);

		// only the lower triangular of matrix is set because the diagonalization method only needs that

		// first column - 0 - for sa
		matrix(0, 0) = m_material.m_Esa;
		matrix(1, 0) = m_material.m_Vss * g0vc;
		matrix(2, 0) = 0;
		matrix(3, 0) = 0;
		matrix(4, 0) = 0;
		matrix(5, 0) = m_material.m_Vsapc * g1vc;
		matrix(6, 0) = m_material.m_Vsapc * g2vc;
		matrix(7, 0) = m_material.m_Vsapc * g3vc;
		matrix(8, 0) = 0;
		matrix(9, 0) = 0;

		// col 1 - for sc
		matrix(1, 1) = m_material.m_Esc;
		matrix(2, 1) = -m_material.m_Vscpa * g1v;
		matrix(3, 1) = -m_material.m_Vscpa * g2v;
		matrix(4, 1) = -m_material.m_Vscpa * g3v;
		matrix(5, 1) = 0;
		matrix(6, 1) = 0;
		matrix(7, 1) = 0;
		matrix(8, 1) = 0;
		matrix(9, 1) = 0;

		// col 2 - for pxa
		matrix(2, 2) = m_material.m_Epa;
		matrix(3, 2) = 0;
		matrix(4, 2) = 0;
		matrix(5, 2) = m_material.m_Vxx * g0vc;
		matrix(6, 2) = m_material.m_Vxy * g3vc;
		matrix(7, 2) = m_material.m_Vxy * g2vc;
		matrix(8, 2) = 0;
		matrix(9, 2) = -m_material.m_Vpasstarc * g1vc;

		// col 3 - for pya
		matrix(3, 3) = m_material.m_Epa;
		matrix(4, 3) = 0;
		matrix(5, 3) = m_material.m_Vxy * g3vc;
		matrix(6, 3) = m_material.m_Vxx * g0vc;
		matrix(7, 3) = m_material.m_Vxy * g1vc;
		matrix(8, 3) = 0;
		matrix(9, 3) = -m_material.m_Vpasstarc * g2vc;

		// col 4 - for pza
		matrix(4, 4) = m_material.m_Epa;
		matrix(5, 4) = m_material.m_Vxy * g2vc;
		matrix(6, 4) = m_material.m_Vxy * g1vc;
		matrix(7, 4) = m_material.m_Vxx * g0vc;
		matrix(8, 4) = 0;
		matrix(9, 4) = -m_material.m_Vpasstarc * g3vc;


		// col 5 - for pxc
		matrix(5, 5) = m_material.m_Epc;
		matrix(6, 5) = 0;
		matrix(7, 5) = 0;
		matrix(8, 5) = m_material.m_Vsstarapc * g1v;
		matrix(9, 5) = 0;

		// col 6 - for pyc
		matrix(6, 6) = m_material.m_Epc;
		matrix(7, 6) = 0;
		matrix(8, 6) = m_material.m_Vsstarapc * g2v;
		matrix(9, 6) = 0;

		// col 7 - for pzc
		matrix(7, 7) = m_material.m_Epc;
		matrix(8, 7) = m_material.m_Vsstarapc * g3v;
		matrix(9, 7) = 0;

		// col 8 - for s*a
		matrix(8, 8) = m_material.m_Esstara;
		matrix(9, 8) = 0. * g0vc; // it's set to 0

		// col 9 - for s*c
		matrix(9, 9) = m_material.m_Esstarc;
	}

	void Hamiltonian::Diagonalize()
	{
		solver.compute(matrix, Eigen::DecompositionOptions::EigenvaluesOnly);

		assert(solver.info() == Eigen::ComputationInfo::Success);
	}


}