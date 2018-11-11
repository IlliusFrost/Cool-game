#include "stdafx.h"
#include "PickUpManager.h"
#include "Pickup.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"
#include "GameObjectData.h"
PickUpManager::PickUpManager()
{

}
void PickUpManager::Update()
{
	

		for (int i = 0; i < myPickUps.size(); ++i)
		{
			if (myPickUps[i]->GetData().isMarkedForDelete)
			{
				std::cout << "Removing PickUP!" << std::endl;
				ColliderManager::GetInstance()->RemoveCollider(myPickUps[i]->GetCollider());
				myPickUps.erase(myPickUps.begin() + i);
				myPickUps.shrink_to_fit();
				i--;
			}
			//myPickUps[i]->Update();
		}


}
void PickUpManager::Draw()
{
	for (int i = 0; i < myPickUps.size(); ++i)
	{
		myPickUps[i]->Draw();
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
	myPickUps.insert(myPickUps.begin(),new PickUp(aPosition, new Tga2D::CSprite("sprites/power.png")));
}