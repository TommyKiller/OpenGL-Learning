#include "Model.h"

Graphics::Model::Model(const char* file_path)
	: RootNode(std::make_shared<Node>())
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
	{
		std::string error_msg("Failed to load a model at ");
		error_msg += file_path;
		error_msg += importer.GetErrorString();
		throw std::exception(error_msg.c_str());
	}

	ProcessNode(RootNode, scene->mRootNode, scene);
}

void Graphics::Model::Render(std::shared_ptr<Graphics::Shader>& shader)
{
	shader->SetUniform("model_mat", GetModelMat());
	shader->SetUniform("normal_mat", GetNormalMat(GetModelMat()));
	RootNode->Render(shader);
}

void Graphics::Model::Translate(glm::vec3 translation)
{
	Transformations.TranslationMat = glm::translate(glm::mat4(1.0f), translation);
}

void Graphics::Model::Scale(glm::vec3 scale)
{
	Transformations.ScaleMat = glm::scale(glm::mat4(1.0f), scale);
}

void Graphics::Model::Rotate(glm::vec3 rotation_axis, float rotation_angle)
{
	Transformations.RotationMat = glm::rotate(glm::mat4(1.0f), rotation_angle, glm::normalize(rotation_axis));
}

void Graphics::Model::ProcessNode(std::shared_ptr<Node>& node, aiNode* aiNode, const aiScene* scene)
{
	for (unsigned int i = 0; i < aiNode->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[aiNode->mMeshes[i]];
		node->Meshes.push_back(std::shared_ptr<Mesh>(ProcessMesh(mesh, scene)));
	}
	for (unsigned int i = 0; i < aiNode->mNumChildren; i++)
	{
		node->Children.push_back(std::make_shared<Node>());
		ProcessNode(node->Children.back(), aiNode->mChildren[i], scene);
	}
}

Graphics::Mesh* Graphics::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Material material;
	// Vertices processing
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		std::vector<glm::vec2> texturesCoords;
		for (unsigned int j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; j++)
		{
			glm::vec2 textureCoords;
			if (mesh->mTextureCoords[j])
			{
				textureCoords.x = mesh->mTextureCoords[j][i].x;
				textureCoords.y = mesh->mTextureCoords[j][i].y;
			}
			else
			{
				textureCoords = glm::vec2(0.0f);
			}
			texturesCoords.push_back(textureCoords);
		}

		vertices.push_back(Vertex(ProcessData(mesh->mVertices, i), ProcessData(mesh->mNormals, i),
			ProcessData(mesh->mTangents, i), ProcessData(mesh->mBitangents, i), texturesCoords));
	}
	// Indices processing
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	// Material processing
	aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];
	material = ProcessData(aiMaterial);

	return new Mesh(vertices, indices, material);
}

glm::vec3 Graphics::Model::ProcessData(aiVector3D* data, unsigned int index)
{
	glm::vec3 vector;
	vector.x = data[index].x;
	vector.y = data[index].y;
	vector.z = data[index].z;

	return vector;
}

Graphics::Material Graphics::Model::ProcessData(aiMaterial* data)
{
	Material material;
	if (AI_SUCCESS != aiGetMaterialFloat(data, AI_MATKEY_SHININESS, &material.Shininess))
	{
		throw std::exception("Cannot retrieve material`s shininess");
	}
	material.TexturesAmbient = ProcessData(data, aiTextureType_AMBIENT, "texture_ambient");
	material.TexturesDiffuse = ProcessData(data, aiTextureType_DIFFUSE, "texture_diffuse");
	material.TexturesSpecular = ProcessData(data, aiTextureType_SPECULAR, "texture_specular");
	return material;
}

std::vector<Graphics::Texture2D> Graphics::Model::ProcessData(aiMaterial* data, aiTextureType type, std::string texture_name)
{
	static std::vector<Texture2D> cachedTextures;
	std::vector<Graphics::Texture2D> textures;
	for (unsigned int i = 0; i < data->GetTextureCount(type); i++)
	{
		aiString path;
		data->GetTexture(type, i, &path);
		std::vector<Texture2D>::iterator result = std::find_if(cachedTextures.begin(), cachedTextures.end(),
			[&](const Texture2D texture) {return (texture.GetPath() == path.C_Str()); });

		if (result != cachedTextures.end())
		{
			textures.push_back(cachedTextures[std::distance(cachedTextures.begin(), result)]);
		}
		else
		{
			Texture2D texture(path.C_Str(), texture_name);
			textures.push_back(texture);
			cachedTextures.push_back(texture);
		}
	}
	return textures;
}

glm::mat4 Graphics::Model::GetModelMat()
{
	static glm::mat4 model_mat(1.0f);
	static Graphics::Transformations cached_data;

	if (cached_data == this->Transformations)
	{
		return model_mat;
	}
	else
	{
		cached_data = this->Transformations;
		model_mat = Transformations.ScaleMat * Transformations.RotationMat * Transformations.TranslationMat * glm::mat4(1.0f);
		return model_mat;
	}
}

glm::mat3 Graphics::Model::GetNormalMat(glm::mat4 model_mat)
{
	static glm::mat4 normal_mat(1.0f);
	static glm::mat4 cached_model_mat(1.0f);

	if (cached_model_mat == model_mat)
	{
		return normal_mat;
	}
	else
	{
		cached_model_mat = model_mat;
		normal_mat = glm::inverseTranspose(glm::mat3(model_mat));
		return normal_mat;
	}
}

void Graphics::Model::Node::Render(std::shared_ptr<Graphics::Shader>& shader) const
{
	for (const std::shared_ptr<Mesh>& mesh : Meshes)
	{
		mesh->Render(shader);
	}
	for (const std::shared_ptr<Model::Node>& node : Children)
	{
		node->Render(shader);
	}
}
