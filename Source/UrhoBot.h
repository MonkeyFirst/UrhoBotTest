#pragma once

#include "Urho3D/Engine/Application.h"
#include "Urho3D/Math/Plane.h"
#include "Urho3D/Physics/RigidBody.h"
#include "Character.h"
#include "BotLogic.h"

namespace Urho3D
{
	class Node;
	class Scene;
	class Plane;

}

using namespace Urho3D;

class UrhoQuickStart : public Application
{
	URHO3D_OBJECT(UrhoQuickStart, Application);

public:
	UrhoQuickStart(Context* context);
	virtual void Start();

protected:
	SharedPtr<Scene> scene_;
	SharedPtr<Node> cameraNode_;
	SharedPtr<Node> playerNode_;
	WeakPtr<Character> playerScript_;

	SharedPtr<Node> botNode_;
	WeakPtr<BotLogic> botScript_;


private:
	void CreateConsole();
	void SubscribeToEvents();
	void LoadScene(Urho3D::String sceneFileName);
	void CameraSetup(Urho3D::String cameraNodeName);
	void OtherSetup();
	void CameraViewRotate(float timeStep);
	void GenerateNavMesh();
	bool Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);

	void HandleUpdate(StringHash eventType, VariantMap& eventData);
	void HandleKeyDown(StringHash eventType, VariantMap& eventData);
	void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
	void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

	bool paused_;
	float yaw_;
	float pitch_;

	bool drawDebug_;


};
