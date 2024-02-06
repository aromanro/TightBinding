#pragma once

#include <vector>
#include <atomic>

#include "Vector3D.h"

#include "Material.h"
#include "SymmetryPoints.h"

namespace TightBinding
{

	class BandStructure
	{
	public:
		Materials materials;
		SymmetryPoints symmetryPoints;

		std::vector<std::vector<double>> results;
		std::vector<unsigned int> symmetryPointsPositions;

		void Initialize(std::vector<std::string> path, unsigned int nrPoints = 600);
		std::vector<std::vector<double>> Compute(const Material& material, unsigned int startPoint, unsigned int endPoint, std::atomic_bool& terminate) const;

		unsigned int GetPointsNumber() const { return static_cast<unsigned int>(kpoints.size()); }

		const std::vector<std::string>& GetPath() const { return m_path; }

	private:
		std::vector<std::string> m_path;

		std::vector<Vector3D<double>> kpoints;
	};

}

