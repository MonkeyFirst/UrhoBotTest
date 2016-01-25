#pragma once
#include "Urho3DAll.h"
#include <stack>

namespace Urho3D
{
	class Node;
	class Scene;
	class Plane;
	class RigidBody;
	class LogicComponent;
	class Drawable;
	class AnimationModel;
	class AnimationState;
};

using namespace Urho3D;

class BotLogic : public LogicComponent 
{
    URHO3D_OBJECT(BotLogic, LogicComponent);
public:
	/// Construct.
	BotLogic(Context* context);

	/// Register object factory and attributes.
	static void RegisterObject(Context* context);

	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();

	// ���������� ������ ���� ?
	void Update(float timeStep);
	
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);

	void DrawBotDebugInfo();

	void AddPath(Vector3 start_, Vector3 end_);
	void FollowPath(float timeStep);


	void ExecuteWayPointsStack(float timeStep);
	void AddWayPoints(Vector3 position);

private:
	void HandleNodeCollision(StringHash eventType, VariantMap& eventData);



	SharedPtr<RigidBody> rigidbody_;
	SharedPtr<Node> lasersNode_;

	SharedPtr<AnimatedModel> animModelBot_;
	SharedPtr<AnimationState> animStateWalk_;
	SharedPtr<AnimationState> animStateIdle_;

	SharedPtr<AnimatedModel> animModelLasers_;
	SharedPtr<AnimationState> animStateLasers_;

	SharedPtr<Node> wayPoints[4];
	std::stack<Vector3> ws;
	PODVector<Vector3> currentPath_;
	



};