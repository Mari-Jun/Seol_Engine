#pragma once
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	class StaticMeshComponent final : public MeshComponent
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent() = default;

		virtual void InitializeDetailFunction() override;

	public:
		template<typename T, typename ... Args>
		constexpr bool SetMesh(FileType type, std::string&& path, Args&& ... args)
		{
			//Mesh ��ü ���� Ȯ��
			if (m_Mesh != nullptr)
			{
				m_Mesh = nullptr;
				SetRenderState(RenderState::Ready);
			}

			//�̹� Load������ �ִ��� Cache�����Ϳ��� ã�´�. 
			const auto& factory = RenderComponentFactory::GetRenderComponentFactory();
			m_Mesh = factory->GetMesh(path);

			if (m_Mesh == nullptr)
			{
				m_Mesh = CreateSPtr<T>();
				switch (type)
				{
				case FileType::Obj:
					if (!std::reinterpret_pointer_cast<T>(m_Mesh)->LoadObj(path))
					{
						std::reinterpret_pointer_cast<T>(m_Mesh)->LoadObj(CONTENT_DIR + "Default/Box.obj");
						return false;
					}
					break;
				}

				factory->SaveMesh(path, m_Mesh);
				return true;
			}

			return true;
		}
	};
}


