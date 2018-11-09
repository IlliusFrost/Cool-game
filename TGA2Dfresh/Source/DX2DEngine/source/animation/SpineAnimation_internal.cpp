#include "stdafx.h"
#include <tga2d/animation/SpineAnimation_internal.h>
#include <tga2d/primitives/custom_shape.h>
#include <tga2d/texture/texture.h>
#include <tga2d/engine.h>
#include <tga2d/drawers/debug_drawer.h>
#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

typedef unsigned char Uint8;

_SP_ARRAY_IMPLEMENT_TYPE(spColorArray, spColor)

using namespace Tga2D;
void _AtlasPage_createTexture(AtlasPage* self, const char* path, void* aData)
{
	CSpineAnimation_Internal* anim = static_cast<CSpineAnimation_Internal*>(aData);
	anim->myShape->SetTexture(path);
	
	anim->myShape->SetSamplerState(ESamplerFilter_Bilinear, ESamplerAddressMode_Clamp);
	if (self->uWrap == SP_ATLAS_REPEAT && self->vWrap == SP_ATLAS_REPEAT)  anim->myShape->SetSamplerState(ESamplerFilter_Bilinear, ESamplerAddressMode_Wrap);

	self->rendererObject = anim->myShape;
	Tga2D::Vector2ui size = anim->myShape->GetTexture()->myImageSize;
	self->width = size.x;
	self->height = size.y;
}

void _AtlasPage_disposeTexture(AtlasPage* self) 
{
	delete self->rendererObject; // myShape
}

char* _Util_readFile(const char* path, int* length) 
{
	return _spReadFile(path, length);
}


SkeletonData* readSkeletonJsonData(const char* filename, Atlas* atlas, float scale)
{
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, filename);
	if (!skeletonData)
	{
		printf("%s\n", json->error);
		exit(0);
	}
	SkeletonJson_dispose(json);
	return skeletonData;
}


CSpineAnimation_Internal::CSpineAnimation_Internal(const char* aAtlasPath, const char* aBonePath) :
	timeScale(1),
	vertexEffect(0),
	worldVertices(0), 
	clipper(0)
{
	myShape = new Tga2D::CCustomShape();
	Atlas* atlas = Atlas_createFromFile(aAtlasPath, 0, this);

	SkeletonData* skeletonData = readSkeletonJsonData(aBonePath, atlas, 1.0f);
	myStateData = AnimationStateData_create(skeletonData);


	Bone_setYDown(true);
	worldVertices = MALLOC(float, SPINE_MESH_VERTEX_COUNT_MAX);
	skeleton = Skeleton_create(skeletonData);
	tempUvs = spFloatArray_create(16);
	tempColors = spColorArray_create(16);

	ownsAnimationStateData = myStateData == 0;
	if (ownsAnimationStateData) myStateData = AnimationStateData_create(skeletonData);

	myAnimationState = AnimationState_create(myStateData);



	clipper = spSkeletonClipping_create();

	myNumBones = skeletonData->bonesCount;
	
}

CSpineAnimation_Internal::~CSpineAnimation_Internal() 
{
	FREE(worldVertices);
	if (ownsAnimationStateData) AnimationStateData_dispose(myAnimationState->data);
	AnimationState_dispose(myAnimationState);
	Skeleton_dispose(skeleton);
	spSkeletonClipping_dispose(clipper);
	spFloatArray_dispose(tempUvs);
	spColorArray_dispose(tempColors);
}

void CSpineAnimation_Internal::update(float deltaTime) 
{
	Skeleton_update(skeleton, deltaTime);
	AnimationState_update(myAnimationState, deltaTime * timeScale);
	AnimationState_apply(myAnimationState, skeleton);
	Skeleton_updateWorldTransform(skeleton);
}

struct SVertexForSpine
{
	Tga2D::CColor color;
	Tga2D::Vector2f position;
	Tga2D::Vector2f texCoords;
};


void CSpineAnimation_Internal::draw(/*RenderTarget& target, RenderStates states*/) const 
{
	
	myShape->Reset();

	if (vertexEffect != 0) vertexEffect->begin(vertexEffect, skeleton);
	unsigned short quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

	
	Tga2D::CCustomShape* texture = 0;
	
	SVertexForSpine vertex;
	Tga2D::Vector2ui winSize = Tga2D::CEngine::GetInstance()->GetWindowSize();
	for (int slotIndex = 0; slotIndex < skeleton->slotsCount; ++slotIndex)
	{
		Slot* slot = skeleton->drawOrder[slotIndex];
		Attachment* attachment = slot->attachment;
		if (!attachment) continue;

		float* vertices = worldVertices; 
		int verticesCount = 0;
		float* uvs = 0;
		unsigned short* indices = 0;
		int indicesCount = 0;
		spColor* attachmentColor;

		if (attachment->type == ATTACHMENT_REGION) {
			RegionAttachment* regionAttachment = (RegionAttachment*)attachment;
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, vertices, 0, 2);
			verticesCount = 4;
			uvs = regionAttachment->uvs;
			indices = quadIndices;
			indicesCount = 6;
			texture = (Tga2D::CCustomShape*)((AtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
			attachmentColor = &regionAttachment->color;

		}
		else if (attachment->type == ATTACHMENT_MESH) 
		{
			MeshAttachment* mesh = (MeshAttachment*)attachment;
			if (mesh->super.worldVerticesLength > SPINE_MESH_VERTEX_COUNT_MAX) continue;
			texture = (Tga2D::CCustomShape*)((AtlasRegion*)mesh->rendererObject)->page->rendererObject;
			spVertexAttachment_computeWorldVertices(SUPER(mesh), slot, 0, mesh->super.worldVerticesLength, worldVertices, 0, 2);
			verticesCount = mesh->super.worldVerticesLength >> 1;
			uvs = mesh->uvs;
			indices = mesh->triangles;
			indicesCount = mesh->trianglesCount;
			attachmentColor = &mesh->color;
		}
		else if (attachment->type == SP_ATTACHMENT_CLIPPING) {
			spClippingAttachment* clip = (spClippingAttachment*)slot->attachment;
			spSkeletonClipping_clipStart(clipper, slot, clip);
			continue;
		}
		else continue;

		Uint8 r = static_cast<Uint8>(skeleton->color.r * slot->color.r * attachmentColor->r * 255);
		Uint8 g = static_cast<Uint8>(skeleton->color.g * slot->color.g * attachmentColor->g * 255);
		Uint8 b = static_cast<Uint8>(skeleton->color.b * slot->color.b * attachmentColor->b * 255);
		Uint8 a = static_cast<Uint8>(skeleton->color.a * slot->color.a * attachmentColor->a * 255);
		vertex.color.myR = r / 255.0f;
		vertex.color.myG = g / 255.0f;
		vertex.color.myB = b / 255.0f;
		vertex.color.myA = a / 255.0f;

		spColor light;
		light.r = r / 255.0f;
		light.g = g / 255.0f;
		light.b = b / 255.0f;
		light.a = a / 255.0f;

		EBlendState blend;
		if (!usePremultipliedAlpha) 
		{
			switch (slot->data->blendMode) {
			case BLEND_MODE_NORMAL:
				blend = EBlendState_Alphablend;
				break;
			case BLEND_MODE_ADDITIVE:
				blend = EBlendState_Additiveblend;
				break;
			default:
				blend = EBlendState_Alphablend;
			}
		}
		else 
		{
			switch (slot->data->blendMode) 
			{
			case BLEND_MODE_NORMAL:
				blend = EBlendState_Alphablend;
				break;
			case BLEND_MODE_ADDITIVE:
				blend = EBlendState_Additiveblend;
				break;
			default:
				blend = EBlendState_Alphablend;
			}
		}

		texture->SetBlendState(blend);
		if (spSkeletonClipping_isClipping(clipper)) 
		{
			spSkeletonClipping_clipTriangles(clipper, vertices, verticesCount << 1, indices, indicesCount, uvs, 2);
			vertices = clipper->clippedVertices->items;
			verticesCount = clipper->clippedVertices->size >> 1;
			uvs = clipper->clippedUVs->items;
			indices = clipper->clippedTriangles->items;
			indicesCount = clipper->clippedTriangles->size;
		}

		Tga2D::Vector2ui size = texture->GetTexture()->myImageSize;
		if (vertexEffect != 0) 
		{
			spFloatArray_clear(tempUvs);
			spColorArray_clear(tempColors);
			for (int i = 0; i < verticesCount; i++)
			{
				spColor vertexColor = light;
				spColor dark;
				dark.r = dark.g = dark.b = dark.a = 0;
				int index = i << 1;
				float x = vertices[index];
				float y = vertices[index + 1];
				float u = uvs[index];
				float v = uvs[index + 1];
				vertexEffect->transform(vertexEffect, &x, &y, &u, &v, &vertexColor, &dark);
				vertices[index] = x;
				vertices[index + 1] = y;
				spFloatArray_add(tempUvs, u);
				spFloatArray_add(tempUvs, v);
				spColorArray_add(tempColors, vertexColor);
			}
			
			for (int i = 0; i < indicesCount; ++i)
			{
				int index = indices[i] << 1;
				vertex.position.x = vertices[index] / (float)winSize.x;
				vertex.position.y = vertices[index + 1] / (float)winSize.y;
				vertex.texCoords.x = uvs[index] * size.x;
				vertex.texCoords.y = uvs[index + 1] * size.y;
				spColor vertexColor = tempColors->items[index >> 1];
				vertex.color.myR = static_cast<Uint8>(vertexColor.r) * myColor.myR;
				vertex.color.myG = static_cast<Uint8>(vertexColor.g) * myColor.myB;
				vertex.color.myB = static_cast<Uint8>(vertexColor.b) * myColor.myB;
				vertex.color.myA = static_cast<Uint8>(vertexColor.a) * myColor.myA;
				texture->AddPoint(vertex.position, vertex.color, vertex.texCoords);
			}
		}
		else 
		{
			vertex.color.myR *= myColor.myR;
			vertex.color.myG *= myColor.myB;
			vertex.color.myB *= myColor.myB;
			vertex.color.myA *= myColor.myA;
			for (int i = 0; i < indicesCount; ++i) 
			{
				int index = indices[i] << 1;
				vertex.position.x = vertices[index] / (float)winSize.x;
				vertex.position.y = vertices[index + 1] / (float)winSize.y;
				vertex.texCoords.x = (uvs[index] );
				vertex.texCoords.y = (uvs[index + 1] );

				texture->AddPoint(vertex.position, vertex.color, vertex.texCoords);
			}
		}

		spSkeletonClipping_clipEnd(clipper, slot);
	}

	texture->BuildShape();
	texture->Render();
	spSkeletonClipping_clipEnd2(clipper);

	if (vertexEffect != 0) vertexEffect->end(vertexEffect);
}

void Tga2D::CSpineAnimation_Internal::DrawDebug()
{
	Tga2D::Vector2ui winSize = Tga2D::CEngine::GetInstance()->GetWindowSize();
	spBone** bones = skeleton->bones;

	for (int i=0; i< skeleton->bonesCount; i++)
	{
		spBone* bone = bones[i];


		Vector2f bonePos = Vector2f(bone->worldX / (float)winSize.x, bone->worldY / (float)winSize.y);
		Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle(bonePos, 0.01f, CColor(1, 1, 1, 1));

		for (int j = 0; j< bone->childrenCount; j++)
		{
			spBone* child = bone->children[j];

			Vector2f bonePosChild = Vector2f(child->worldX / (float)winSize.x, child->worldY / (float)winSize.y);
			Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawArrow(bonePos, bonePosChild, CColor(1, 1, 1, 1), 1.0f);

		}
	}


}

void Tga2D::CSpineAnimation_Internal::DoMixAnimation(std::string aFrom, std::string aTo, float aDelay)
{
	if (!myStateData)
	{
		return;
	}
	AnimationStateData_setMixByName((spAnimationStateData*)myStateData, aFrom.c_str(), aTo.c_str(), aDelay);
}
void Tga2D::CSpineAnimation_Internal::AddAnimationToQueue(int aTrackIndex, std::string aName, bool aLoop, float aDelay)
{
	AnimationState_addAnimationByName(myAnimationState, aTrackIndex, aName.c_str(), aLoop, aDelay);
}


void Tga2D::CSpineAnimation_Internal::ClearQueue()
{
	spAnimationState_clearTracks(myAnimationState);
}

void Tga2D::CSpineAnimation_Internal::SetCurrentAnimation(int aTrackIndex, std::string aName, bool aLoop)
{
	if (aName.empty())
	{
		spAnimationState_addEmptyAnimation(myAnimationState, aTrackIndex, 0.1f, 0);
		return;
	}
	
	AnimationState_setAnimationByName(myAnimationState, aTrackIndex, aName.c_str(), aLoop);
}

const char* Tga2D::CSpineAnimation_Internal::GetCurrentAnimation(int aTrackIndex)
{
	spTrackEntry* state = AnimationState_getCurrent(myAnimationState, aTrackIndex);
	const char* animationName = (state && state->animation) ? state->animation->name : nullptr;
	return animationName;
}