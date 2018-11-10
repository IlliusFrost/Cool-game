#include "stdafx.h"
#include "PickUpManager.h"
#include "Pickup.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"
PickUpManager::PickUpManager()
{

}
void PickUpManager::Update()
{
	

		for (int i = 0; i < myPickUps.size(); ++i)
		{
			std::cout << myPickUps.size() << " " << i << std::endl;
			if (myPickUps[i]->GetIfIsRemoved())
			{
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
void PickUpManager::SpawnPickUp()
{
	myPickUps.insert(myPickUps.begin(),new PickUp(Vector2f{ 0.5f,0.5f }, new Tga2D::CSprite("sprites/power.png")));
}