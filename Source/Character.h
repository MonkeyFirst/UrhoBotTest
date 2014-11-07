#pragma once
#include "Common.h"
#include "LogicComponent.h"
#include "Controls.h"


namespace Urho3D
{
	class Node;
	class Scene;
	class Plane;
	class RigidBody;
	class LogicComponent;
	class Controls;
	class Drawable;

};

using namespace Urho3D;

class Character : public LogicComponent 
{
	OBJECT(Character);
public:
	/// Construct.
	Character(Context* context);

	/// Register object factory and attributes.
	static void RegisterObject(Context* context);

	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();

	// גûחûגאועסÿ ךאזהûי ךאהנ ?
	void Update(float timeStep);

	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);

	/// Movement controls. Assigned by the main program each frame.
	Controls controls_;

private:
	bool Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);
	void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

	SharedPtr<RigidBody> rigidbody_;
	Quaternion rotation_;
	SharedPtr<Node> cameraNode_;
	SharedPtr<Node> gunNode_;



};