#include "stdafx.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"
#include <tga2d/drawers/debug_drawer.h>
#include <cmath>

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
#ifdef _DEBUG
	myShouldRenderColliders = true;
#else
	myShouldRenderColliders = true;
#endif // _DEBUG
}

void ColliderManager::Update(float aDt)
{
	aDt;
	for (unsigned short i = 0; i < myColliders.Size(); i++)
	{
		if (myShouldRenderColliders)
			Tga2D::CDebugDrawer::DrawCircle({ myColliders[i]->myPos.x, myColliders[i]->myPos.y }, myColliders[i]->myRadius);
		for (unsigned short j = 0; j < myColliders.Size(); j++)
		{
			if (myColliders[i] != myColliders[j])
			{
				if (myColliders[i]->CollidesWith(*myColliders[j]))
				{
					for (int a = 0; a < myColliders[i]->myCanCollideWith.size(); a++)
						if (myColliders[i]->myCanCollideWith[a] == myColliders[j]->myFlag)
						{
							myColliders[i]->CollisionEvent(myColliders[j]->myFlag);

							if (myColliders[i]->myFlag == CollisionFlag::ePlayer &&
								myColliders[j]->myFlag == CollisionFlag::eGravitationField)
							{
								Vector2f delta = myColliders[j]->myObjectData->myPosition - myColliders[i]->myObjectData->myPosition;

							}
							if (myColliders[i]->myFlag == CollisionFlag::ePlayer &&
								myColliders[j]->myFlag == CollisionFlag::ePlayer)
							{
								myColliders[j]->myObjectData->myVelocity += myColliders[i]->myObjectData->myVelocity;
								myColliders[i]->myObjectData->myVelocity *= -1.3f;
							}
						}
					
					for (int a = 0; a < myColliders[j]->myCanCollideWith.size(); a++)
						if (myColliders[j]->myCanCollideWith[a] == myColliders[i]->myFlag)
						{
							myColliders[j]->CollisionEvent(myColliders[i]->myFlag);
							myColliders[j]->myObjectData->latestCollideObjectPosition = myColliders[i]->myPos;
							myColliders[i]->myObjectData->latestCollideObjectPosition = myColliders[j]->myPos;
						}
				}
			}
		}
	}
}

void ColliderManager::RegisterCollider(CircleCollider * aCollider)
{
	myColliders.Add(aCollider);
}

void ColliderManager::RemoveCollider(CircleCollider * aCollider)
{
	myColliders.RemoveCyclic(aCollider);
}
