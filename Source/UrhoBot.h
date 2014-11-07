#pragma once

#include "Application.h"
#include "Plane.h"
#include "RigidBody.h"

namespace Urho3D
{
	class Node;
	class Scene;
	class Plane;

}

using namespace Urho3D;

class UrhoQuickStart : public Application
{
	OBJECT(UrhoQuickStart);

public:
	UrhoQuickStart(Context* context);
	virtual void Start();

protected:
	SharedPtr<Scene> scene_;
	SharedPtr<Node> cameraNode_;
	SharedPtr<Node> playerNode_;


private:
	void CreateConsole();
	void SubscribeToEvents();
	void LoadScene(Urho3D::String sceneFileName);
	void CameraSetup(Urho3D::String cameraNodeName);
	void OtherSetup();
	void CameraViewRotate(float timeStep);
	
	void HandleUpdate(StringHash eventType, VariantMap& eventData);
	void HandleKeyDown(StringHash eventType, VariantMap& eventData);
	void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);

	bool paused_;
	float yaw_;
	float pitch_;


};