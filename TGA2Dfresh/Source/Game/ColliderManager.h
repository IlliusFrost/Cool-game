#pragma once
class CircleCollider;
class ColliderManager
{
public:
	static void Create();
	static void Destroy();
	static ColliderManager* GetInstance();

	void Init();
	void Update(float aDt);

	void RegisterCollider(CircleCollider* aCollider);

private:
	ColliderManager();
	~ColliderManager();

	static ColliderManager* ourInstance;

	bool myShouldRenderColliders;
	GrowingArray<CircleCollider*> myColliders;
};

