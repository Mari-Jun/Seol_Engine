#pragma once
#include "PARS/Actor/Light/Light.h"

namespace PARS
{
    class DirectionalLight : public Light
    {
	public:
		DirectionalLight(const std::string& name = "DirectionalLight");
		DirectionalLight(const Vec3& color, const std::string& name = "DirectionalLight");

		virtual void Initialize() override;
		virtual void Shutdown() override;
		//virtual void Update(float deltaTime) {}
    };
}


