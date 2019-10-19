#ifndef MODEL_H
#define MODEL_H
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>
#include <GLM/gtc/matrix_inverse.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <algorithm>
#include <memory>
#include "Transformations.h"
#include "Mesh.h"

namespace Graphics
{
	class Model
	{
	public:
		Model(const char* file_path);

		void Render(std::shared_ptr<Graphics::Shader>& shader);

		// Transformations
		void Translate(glm::vec3 translation);
		void Scale(glm::vec3 scale);
		void Rotate(glm::vec3 rotation_axis, float rotation_angle);

	private:
		struct Node
		{
			std::vector<std::shared_ptr<Mesh>> Meshes;
			std::vector<std::shared_ptr<Node>> Children;

			void Render(std::shared_ptr<Graphics::Shader>& shader) const;
		};
		std::shared_ptr<Node> RootNode;
		Transformations Transformations;

		// Loading
		void ProcessNode(std::shared_ptr<Node>& node, aiNode* aiNode, const aiScene* scene);
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
		glm::vec3 ProcessData(aiVector3D* data, unsigned int index);
		Material ProcessData(aiMaterial* data);
		std::vector<Texture2D> ProcessData(aiMaterial* data, aiTextureType type, std::string texture_name);

		// Get matrices
		glm::mat4 GetModelMat();
		glm::mat3 GetNormalMat(glm::mat4 model_mat);

		Model(Model& model) = delete;
		Model& operator=(const Model&) = delete;
	};
}

#endif
