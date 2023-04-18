#include "MiniginPCH.h"
#include "Scene.h"

#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name)
{}

Scene::~Scene()
{

}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for (size_t idx = 0; idx < m_Objects.size(); ++idx)
		m_Objects[idx]->Update();
}

void dae::Scene::FixedUpdate()
{
	for (const auto& object : m_Objects)
		object->FixedUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}

void Scene::Initialize()
{
	for (const auto& object : m_Objects)
		object->Initalize();
}

void Scene::ResetScene()
{
	m_Objects.clear();

	Initialize();
}


std::string Scene::GetName() const
{
	return m_Name;
}

void dae::Scene::DeleteObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(),
		m_Objects.end(),
		[](std::shared_ptr<GameObject> object) {return object->GetMarkedForDelete(); }),
		m_Objects.end());
}


