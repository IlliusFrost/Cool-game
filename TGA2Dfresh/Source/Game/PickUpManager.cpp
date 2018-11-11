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
void PickUpManager::SpawnPickUp(Vector2f aPosition)
{
	myPickUps.insert(myPickUps.begin(), new PickUp(aPosition, new Tga2D::CSprite("sprites/SpaceJunk.png"), 
		{ static_cast<float>(CommonUtilities::GenerateRandomNr(0,1))/10, static_cast<float>(CommonUtilities::GenerateRandomNr(0,1)) / 10 }));
}