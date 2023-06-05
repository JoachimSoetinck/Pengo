#pragma once
#include "GameObject.h"
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		Scene(const std::string& name);
		virtual ~Scene();

		void Add(const std::shared_ptr<GameObject>& object);
		
		virtual void Update();
		void FixedUpdate();
		void Render() const;
		virtual void Initialize();
		void ResetScene();

		std::string	GetName() const;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void DeleteObjects();


		std::vector <std::shared_ptr<GameObject>>GetObjects()const { return m_Objects; };

	protected:
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;

	
	};

}
