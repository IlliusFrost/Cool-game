#include "stdafx.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"

ColliderManager* ColliderManager::ourInstance = nullptr;

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::Create()
{
	assert(!ourInstance && "Instance already created");
	ourInstance = new ColliderManager();
}

void ColliderManager::Destroy()
{
	assert(ourInstance && "Instance already destroyed");
	SAFE_DELETE(ourInstance);
}

ColliderManager* ColliderManager::GetInstance()
{
	assert(ourInstance && "Instance was nullptr");
	return ourInstance;
}

void ColliderManager::Init()
{
	myColliders.Init(50);
}

void ColliderManager::Update(float aDt)
{
	aDt;
	for (unsigned short i = 0; i < myColliders.Size(); i++)
	{
		for (unsigned short j = 0; j < myColliders.Size(); j++)
		{
			if (myColliders[i] != myColliders[j])
			{
				if (myColliders[i]->CollidesWith(*myColliders[j]))
				{
					myColliders[i]->CollisionEvent();
					myColliders[j]->CollisionEvent();
				}
			}
		}
	}
}

void ColliderManager::RegisterCollider(CircleCollider * aCollider)
{
	myColliders.Add(aCollider);
}
