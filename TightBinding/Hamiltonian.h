#pragma once

#include <Eigen/eigen>

#include <complex>
#include "Vector3D.h"

#include "Material.h"

namespace TightBinding
{


	class Hamiltonian
	{
	public:
		Hamiltonian(const Material& material);

		void SetMatrix(const Vector3D<double>& k);
		void Diagonalize();

		const Eigen::VectorXd& eigenvalues() const { return solver.eigenvalues(); }
	protected:
		static std::complex<double> g0(const Vector3D<double>& k);
		static std::complex<double> g1(const Vector3D<double>& k);
		static std::complex<double> g2(const Vector3D<double>& k);
		static std::complex<double> g3(const Vector3D<double>& k);

		const Material& m_material;

		Eigen::Matrix<std::complex<double>, 10, 10> matrix;

		Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> solver;
	};

}

