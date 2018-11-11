#include "stdafx.h"
#include "PickUpManager.h"
#include "Pickup.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"
#include "GameObjectData.h"
#include "..\CommonUtilities\Rnd.hpp"
PickUpManager::PickUpManager()
{

}
void PickUpManager::Update(float aDeltaTime)
{
	if (mySpawnTimer <= 0 && myPickUps.size() <= 10 && isSpawning == true)
	{
		mySpawnTimer = mySpawnDelay;
		SpawnPickUp();
	}
	mySpawnTimer -= aDeltaTime;
	for (int i = 0; i < myPickUps.size(); ++i)
	{
		if (!myPickUps[i]->GetData().isMarkedForDelete)
		{
			myPickUps[i]->Update(aDeltaTime);
		}
		else
		{
			std::cout << "Removing PickUP!" << std::endl;
			ColliderManager::GetInstance()->RemoveCollider(myPickUps[i]->GetCollider());
			myPickUps.erase(myPickUps.begin() + i);
			if (i > 0)
			{
				i--;
			}
		}

}


}
void PickUpManager::Draw()
{
	for (int i = 0; i < myPickUps.size(); ++i)
	{
		if (!myPickUps[i]->GetData().isMarkedForDelete)
		{
			myPickUps[i]->Draw();
		}
	}
}
void PickUpManager::DeletePickUp(int aPickUpIndex)
{
	PickUp* thePickUpToDelete = myPickUps[aPickUpIndex];
	myPickUps.erase(myPickUps.begin() + aPickUpIndex);
	SAFE_DELETE(thePickUpToDelete);
}
void PickUpManager::SecondPhase()
{
	isSpawning = false;
	for (int i = 0; i < myPickUps.size(); ++i)
	{
			std::cout << "Removing PickUP!" << std::endl;
			ColliderManager::GetInstance()->RemoveCollider(myPickUps[i]->GetCollider());
			myPickUps.erase(myPickUps.begin() + i);
		}
}
void PickUpManager::SpawnPickUp( )
{
	Vector2f aPosition = { 0.f,0.f };
	Vector2f aDirection = { 0.f,0.f };
	int random = CommonUtilities::GenerateRandomNr(0,3);
	if (random == 0)
	{
		aPosition.x = 1.2f;
		aPosition.y = static_cast<float>(CommonUtilities::GenerateRandomNr(0, 10)) / 10;
		aDirection.x = -0.005f;
		aDirection.y = 0.f;
	}
	else if(random == 1)
	{
		aPosition.x = -0.2f;
		aPosition.y = static_cast<float>(CommonUtilities::GenerateRandomNr(0, 10)) / 10;
		aDirection.x = 0.005f;
		aDirection.y = 0.f;
	}
	else if (random == 2)
	{
		aPosition.y = -0.2f;
		aPosition.x = static_cast<float>(CommonUtilities::GenerateRandomNr(0, 10)) / 10;
		aDirection.y = 0.005f;
		aDirection.x = 0.f;
	}
	else
	{
		aPosition.y = 1.2f;
		aPosition.x = static_cast<float>(CommonUtilities::GenerateRandomNr(0, 10)) / 10;
		aDirection.y = -0.005f;
		aDirection.x = 0.f;
	}
	myPickUps.insert(myPickUps.begin(), new PickUp(aPosition, new Tga2D::CSprite("sprites/SpaceJunk.png"),{ aDirection.x, aDirection.y }));
}