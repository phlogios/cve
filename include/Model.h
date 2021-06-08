#pragma once
#include <string>
#include <vector>

namespace CVE {
	struct Vertex;

	class Model {
	public:
		Model();
		~Model();

		static Model loadModel(const std::string& path);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}