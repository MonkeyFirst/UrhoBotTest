#include "Common.h"
#include "BotLogic.h"

BotLogic::BotLogic(Context* context) : LogicComponent(context)
{
	// Only the physics update event is needed: unsubscribe from the rest for optimization
	SetUpdateEventMask(USE_FIXEDUPDATE | USE_UPDATE);
}

void BotLogic::RegisterObject(Context* context)
{
	context->RegisterFactory<BotLogic>();
}

void BotLogic::Start()
{
	// Component has been inserted into its scene node. Subscribe to events now
	SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(BotLogic, HandleNodeCollision));
	rigidbody_ = GetNode()->GetComponent<RigidBody>();

	animModelBot_ = GetComponent<AnimatedModel>();
	lasersNode_ = GetNode()->GetChild("lasersNode", true);
	animModelLasers_ = lasersNode_->GetComponent<AnimatedModel>();

	animStateIdle_ = animModelBot_->GetAnimationStates()[0];
	animStateIdle_->SetLooped(true);
	animStateIdle_->SetLayer(0);

	animStateWalk_ = animModelBot_->GetAnimationStates()[1];
	animStateWalk_->SetLooped(true);
	animStateWalk_->SetLayer(1);


	animStateLasers_ = animModelLasers_->GetAnimationStates()[0];
	animStateLasers_->SetWeight(1.0f);
	animStateLasers_->SetLooped(true);
	animStateLasers_->AddTime(0.0f);


	wayPoints[0]= GetScene()->GetChild("wayPoint0", true);
	wayPoints[1]= GetScene()->GetChild("wayPoint1", true);
	wayPoints[2]= GetScene()->GetChild("wayPoint2", true);
	wayPoints[3]= GetScene()->GetChild("wayPoint3", true);
	AddWayPoints(wayPoints[0]->GetWorldPosition());
	AddWayPoints(wayPoints[1]->GetWorldPosition());
	AddWayPoints(wayPoints[2]->GetWorldPosition());
	AddWayPoints(wayPoints[3]->GetWorldPosition());

}

void BotLogic::AddPath(Vector3 start_, Vector3 end_)
{
	currentPath_.Clear();
	NavigationMesh* navMesh = GetNode()->GetScene()->GetComponent<NavigationMesh>();
	navMesh->FindPath(currentPath_, start_, end_);
}

void BotLogic::FollowPath(float timeStep)
{
	if (currentPath_.Size())
	{
		Vector3 nextWaypoint = currentPath_[0]; // NB: currentPath[0] is the next waypoint in order

		// Rotate Jack toward next waypoint to reach and move. Check for not overshooting the target
		float SPEED = 20.0f;
		float distance = (GetNode()->GetWorldPosition() - nextWaypoint).Length();

		Vector3 dir = nextWaypoint - GetNode()->GetWorldPosition();
		Vector3 lookAt = nextWaypoint;

		dir.y_ = GetNode()->GetWorldPosition().y_;
		lookAt.y_ = GetNode()->GetWorldPosition().y_;

		dir.Normalize();
		GetNode()->LookAt(lookAt, Vector3::UP, TS_WORLD);

		RigidBody* rigidbody_ = GetComponent<RigidBody>();
		Vector3 vel = rigidbody_->GetLinearVelocity();
		if (vel.Length() < 5.0f) rigidbody_->ApplyForce(dir * SPEED);

		//GetNode()->Translate(Vector3::FORWARD * move);

		// Remove waypoint if reached it
		if ((GetNode()->GetWorldPosition() - nextWaypoint).Length() < 3.0f)
			currentPath_.Erase(0);
	}
}

void BotLogic::DrawBotDebugInfo()
{
	DebugRenderer* debug = GetNode()->GetScene()->GetComponent<DebugRenderer>();
	if (!ws.empty())
		debug->AddLine(GetNode()->GetWorldPosition(), ws.top(), Color(1.0f, 1.0f, 1.0f));


	if (currentPath_.Size() > 0)
	{
		Vector3 offset(0.0f,0.5f,0.0f);

		debug->AddLine(GetNode()->GetPosition() + offset, currentPath_[0] + offset, Color(1.0f, 1.0f, 1.0f));


		for (unsigned i = 0; i < currentPath_.Size() - 1; ++i)
			debug->AddLine(currentPath_[i] + offset, currentPath_[i + 1]+offset, Color(1.0f, 1.0f, 1.0f));
	}

}

void BotLogic::ExecuteWayPointsStack(float timeStep)
{
	static bool isEndPath = false;
	const float SPEED = 20.0f;

	if (ws.empty())
		isEndPath = true;
	else
	{
		isEndPath = false;

		Vector3 wp = GetNode()->GetWorldPosition();
		float distance = Vector3(ws.top() - wp).Length();

		if (distance < 10.0f)
		{
			if (!ws.empty())
			{
				ws.pop();
			}
			else
			{
				isEndPath = true;
			}
		}
		else
		{
			Vector3 direction(ws.top()- wp);
			direction.y_ = 0.0f;

			direction.Normalize();
			RigidBody* rigidbody_ = GetComponent<RigidBody>();
			Vector3 target = ws.top();

			target.y_ = wp.y_; // fix horizont bot see by it self y

			GetNode()->LookAt(target, Vector3::UP, TS_WORLD);
			Vector3 vel = rigidbody_->GetLinearVelocity();

			if (vel.Length() < 5.0) rigidbody_->ApplyForce(direction * SPEED);
			//rigidbody_->SetLinearVelocity(direction * SPEED * timeStep);

		}
	}



}

void BotLogic::AddWayPoints(Vector3 position)
{
	ws.push(position);
}


void BotLogic::Update(float timeStep)
{

	RigidBody* rigidbody_ = GetComponent<RigidBody>();
	Vector3 vel = rigidbody_->GetLinearVelocity();
	float s = vel.Length();

	if (animStateWalk_)
	{

		animStateWalk_->SetWeight( s > 1.0f ? 1.0f : s );
		animStateWalk_->AddTime(timeStep);


	}

	if (animStateIdle_)
	{
		animStateIdle_->SetWeight(1.0f);
		animStateIdle_->AddTime(timeStep);
	}

	if (animStateLasers_)
	{
		if (s > 0.1f)
		{
			animStateLasers_->AddTime(timeStep);
			// set normal speed animation
			//animStateLasers_->SetSpeed(1.0f);
		}else
		{
			animStateLasers_->AddTime(timeStep / 2.0f);
			//slowdown animation speed by half
			//animStateLasers_->SetSpeed(0.5f);
		}

	}

}

void BotLogic::FixedUpdate(float timeStep)
{
	RigidBody* rigidbody_ = GetComponent<RigidBody>();

	const float MOVE_SPEED = 400.0f;

	Input* input = GetSubsystem<Input>();

	Quaternion worldRotation = GetNode()->GetWorldRotation();
	worldRotation.z_ = 0.0f;

	static bool isUpPressed = false;
	static bool isDownPressed = false;
	static bool isLeftPressed = false;
	static bool isRightPressed = false;

	if (input->GetKeyDown(KEY_UP) && isUpPressed == false)
	{
		isUpPressed = true;
		GetNode()->LookAt(Vector3::FORWARD, Vector3::UP, TS_LOCAL);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::FORWARD * MOVE_SPEED * timeStep);
	}
	else if(!input->GetKeyDown(KEY_UP))
	{
		isUpPressed = false;
	}

	if (input->GetKeyDown(KEY_DOWN) && isDownPressed == false)
	{
		isDownPressed = true;
		GetNode()->LookAt(Vector3::BACK, Vector3::UP, TS_LOCAL);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::BACK * (MOVE_SPEED / 2.0f) * timeStep);
	}
	else if (!input->GetKeyDown(KEY_DOWN))
	{
		isDownPressed = false;
	}

	if (input->GetKeyDown(KEY_LEFT) && isLeftPressed == false)
	{
		isLeftPressed = true;
		GetNode()->LookAt(Vector3::LEFT, Vector3::UP, TS_LOCAL);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::LEFT * (MOVE_SPEED / 2.0f) * timeStep);
	}
	else if (!input->GetKeyDown(KEY_LEFT))
	{
		isLeftPressed = false;
	}

	if (input->GetKeyDown(KEY_RIGHT) && isRightPressed == false)
	{
		isRightPressed = true;
		GetNode()->LookAt(Vector3::RIGHT, Vector3::UP, TS_LOCAL);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::RIGHT * MOVE_SPEED * timeStep);
	}
	else if (!input->GetKeyDown(KEY_RIGHT))
	{
		isRightPressed = false;
	}

	if (currentPath_.Size() == 0)
		ExecuteWayPointsStack(timeStep);
	else
		FollowPath(timeStep);
}

void BotLogic::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
	// Check collision contacts and see if character is standing on ground (look for a contact that has near vertical normal)
	using namespace NodeCollision;

	Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
	VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
	Vector3 pos = contacts.ReadVector3(); // точка столкновения

	Variant myAttr = contact_node->GetVar("type");
	if ( myAttr.GetString() == "value")
	{

	}

}
