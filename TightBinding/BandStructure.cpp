#include "BandStructure.h"
#include "Hamiltonian.h"

namespace TightBinding
{

	void BandStructure::Initialize(std::vector<std::string> path, unsigned int nrPoints)
	{
		kpoints.clear();
		results.clear();

		kpoints.reserve(nrPoints);
		results.reserve(nrPoints);

		m_path.swap(path);

		kpoints = symmetryPoints.GeneratePoints(m_path, nrPoints, symmetryPointsPositions);
	}


	std::vector<std::vector<double>> BandStructure::Compute(const Material& material, unsigned int startPoint, unsigned int endPoint, std::atomic_bool& terminate) const
	{	
		std::vector<std::vector<double>> res;

		Hamiltonian hamiltonian(material);

		for (unsigned int i = startPoint; i < endPoint && !terminate; ++i)
		{
			hamiltonian.SetMatrix(kpoints[i]);
			hamiltonian.Diagonalize();

			const Eigen::VectorXd& eigenvals = hamiltonian.eigenvalues();

			res.emplace_back();
			res.back().reserve(eigenvals.rows());

			for (unsigned int level = 0; level < eigenvals.rows(); ++level)
				res.back().push_back(eigenvals(level));
		}

		return res;
	}

}