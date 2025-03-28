#pragma once

#include <glm/vec4.hpp>
#include <string>
#include <tiny_gltf/tiny_gltf.h>

// Important: all texture indies here are not OpenGL IDs. They are indices into the scene's texture array
struct PBRMaterial
{
	std::string name;
	glm::vec4 baseColorFactor;
	int baseColorTextureIdx; // guaranteed >= 0
	float metallicFactor;
	float roughnessFactor;
	int metallicRoughnessTextureIdx; // guaranteed >= 0
	int normalTextureIdx;
	float normalScale;
	float occlusionStrength;
	int occlusionTextureIdx; // guaranteed >= 0

	// TODO: add support emissive textures and other missing gltf material values
};

PBRMaterial FromGltfMaterial(const tinygltf::Material& gltfMaterial, const tinygltf::Model& model, int white1x1RGBATextureIndex, int max1x1RedTextureIndex);
