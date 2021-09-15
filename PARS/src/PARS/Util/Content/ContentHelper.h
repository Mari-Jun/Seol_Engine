#pragma once
#include <unordered_map>
#include <vector>
#include <string>

namespace PARS
{
	struct ContentInfo
	{
		std::string name;
		std::string path;
		std::string extension;

		friend bool operator<(const ContentInfo& lhs, const ContentInfo& rhs)
		{
			if (lhs.name != rhs.name)
				return lhs.name < rhs.name;
			else
				return lhs.path < rhs.path;
		}
	};
	
	using LoadContent = std::unordered_map<std::string, std::set<ContentInfo>>;	// originalPath, AssetInfoµé
}