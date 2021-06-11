#pragma once
#include <string>
#include <vector>

namespace CVE {
	struct Vertex;

	class Model {
	public:
		Model();
		~Model();

		bool operator<(const Model& other) const {
			return std::hash<std::string>()(name) < std::hash<std::string>()(other.name);
		}

		static Model loadModel(const std::string& path);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::string name;
	};
}

namespace std {
	template<> struct hash<CVE::Model> {
		size_t operator()(CVE::Model const& model) const {
			return hash<std::string>()(model.name);
		}
	};

}