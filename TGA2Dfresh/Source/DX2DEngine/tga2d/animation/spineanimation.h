#pragma once
#include <unordered_map>

namespace Tga2D
{
	using anim_callback_function = std::function<void(int, std::string)>;
	using anim_callback_function_event = std::function<void(int, std::string, std::string,int, float, std::string)>;

	class CSpineAnimation_Internal;
	class CSpineAnimation 
	{
	public:
		CSpineAnimation();
		~CSpineAnimation();
		void Init(const char* aAtlasPath, const char* aBonePath);
		void Update(float aTimeDelta);
		void Render();
		void RenderDebug();

		void SetPosition(const Vector2f& aPosition) { myPosition = aPosition; }
		const Vector2f& GetPosition() const { return myPosition; }

		void SetRotation(const float aRotationInRadians) { myRotation = aRotationInRadians; }
		float GetRotation() const { return myRotation; }

		void SetScale(const Tga2D::Vector2f aScale) { myScale = aScale; }
		Tga2D::Vector2f GetScale() const { return myScale; }

		void SetFlipX(bool aFlipX) { myFlipX = aFlipX; }
		void SetFlipY(bool aFlipY) { myFlipY = aFlipY; }
		
		void SetColor(const Tga2D::CColor& aColor) { myColor = aColor; }
		const Tga2D::CColor& GetColor() const { return myColor; }

		/*For events that is build in such as start, end, interrupt*/
		void RegisterAnimationCallback(anim_callback_function aAnimCallback, int aRegisterID);

		/*For custom events that is build via the animation*/
		void RegisterAnimationEventCallback(anim_callback_function_event aAnimEvent, int aRegisterID);


		void RemoveCallback(int aRegisterID);
		void RemoveEventCallback(int aRegisterID);

		void SetMixTimings(std::string aFrom, std::string aTo, float aDelay);
		void AddAnimationToQueue(int aTrackIndex, std::string aName, bool aLoop, float aDelay);
		void SetCurrentAnimation(int aTrackIndex, std::string aName, bool aLoop);
		const char* GetCurrentAnimation(int aTrackIndex);
		void ClearQueue();

		/*Internal*/
		void OnCallback(int aTrackIndex, std::string aName);
		void OnEventCallback(int aTrackIndex, std::string aName, std::string aEventName, int aIntVal, float aFloatVal, std::string aStringVal);

	private:

		Tga2D::CSpineAnimation_Internal* myInternalAnimation;
		Tga2D::Vector2f myPosition;
		Tga2D::Vector2f myScale;
		float myRotation;
		bool myFlipX;
		bool myFlipY;
		Tga2D::CColor myColor;

		std::unordered_map<int, anim_callback_function> myAnimCallbacks;
		std::unordered_map<int, anim_callback_function_event> myAnimationCallbackEvents;
		
	};
}