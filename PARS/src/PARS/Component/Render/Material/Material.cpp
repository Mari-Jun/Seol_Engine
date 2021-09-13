#include "stdafx.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Component/Render/Texture/Texture.h"
#include "PARS/Util/Content/AssetStore.h"

namespace PARS
{
	namespace MTL
	{
		std::vector<SPtr<Material>> LoadMtl(const std::string& path)
		{
			std::ifstream mtlFile(path);

			std::vector<SPtr<Material>> materials;

			if (!mtlFile.is_open())
			{
				PARS_ERROR("MTL file could not be found : {0}", path);
			}
			else
			{
				std::stringstream ss;
				std::string line;
				std::string prefix;
				std::string name;

				SPtr<Material> material = nullptr;

				Vec4 tempVec4;

				auto AddMaterial([&]() {
					if (material != nullptr)
						materials.emplace_back(std::move(material));
					material = nullptr;
					});

				while (std::getline(mtlFile, line))
				{
					ss.clear();
					ss.str(line);
					ss >> prefix;

					if (prefix == "newmtl")
					{
						AddMaterial();
						material = CreateSPtr<Material>();
						ss >> name;
						material->SetName(name);
					}
					else if (prefix == "Kd")
					{
						ss >> tempVec4.x >> tempVec4.y >> tempVec4.z;
						tempVec4.w = 1.0f;
						material->SetDiffuseAlbedo(tempVec4);
					}
					else if (prefix == "map_Kd")
					{
						ss >> name;
						std::string tPath = FILEHELP::GetRelativePathFromAbsolute(name);
						tPath = FILEHELP::GetParentPathFromPath(tPath) + "\\" + FILEHELP::GetStemFromPath(tPath);
						const auto& texture = GraphicsAssetStore::GetAssetStore()->GetTexture(tPath);
						if (texture != nullptr)
						{
							material->SetDiffuseTexture(texture);
						}
					}
				}

				AddMaterial();
			}

			return materials;
		}
	}
}
