#include <string>
#include "Components.h"

class Entity
{
	friend class entityManager;
	std::string m_tag;
	size_t m_id;
	bool m_active;

public:
	CTransform* cTransform = nullptr;
	CShape* cShape = nullptr;
	CCollision* cCollision = nullptr;
	CInput* cInput = nullptr;
	CScore* cScore = nullptr;
	CLifespan* cLifespan = nullptr;
	CUlt* cUlt = nullptr;
	Entity(const std::string& tag, size_t id)
	{
		m_tag = tag;
		m_id = id;
		m_active = true;
	}
	void destroy();
	bool isActive()
	{
		return m_active;
	}
	std::string& getTag()
	{
		return m_tag;
	}
	size_t getId()
	{
		return m_id;
	}
	~Entity()
	{
		if (cTransform != nullptr)
		{
			delete cTransform;
			cTransform = nullptr;
		}
		if (cShape != nullptr)
		{
			delete cShape;
			cShape = nullptr;
		}
		if (cCollision != nullptr)
		{
			delete cCollision;
			cCollision = nullptr;
		}
		if (cInput != nullptr)
		{
			delete cInput;
			cInput = nullptr;
		}
		if (cScore != nullptr)
		{
			delete cScore;
			cScore = nullptr;
		}
		if (cLifespan != nullptr)
		{
			delete cLifespan;
			cLifespan = nullptr;
		} 
		if (cUlt != nullptr)
		{
			delete cUlt;
			cUlt = nullptr;
		}
	}
};

