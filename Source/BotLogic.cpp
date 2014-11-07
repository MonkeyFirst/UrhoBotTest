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
	SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(BotLogic, HandleNodeCollision));
	rigidbody_ = GetNode()->GetComponent<RigidBody>();

	animModelBot_ = GetComponent<AnimatedModel>();
	lasersNode_ = GetNode()->GetChild("lasersNode", true);
	animModelLasers_ = lasersNode_->GetComponent<AnimatedModel>();
	
	animStateIdle_ = animModelBot_->GetAnimationStates()[0];
	animStateWalk_ = animModelBot_->GetAnimationStates()[1];
	animStateLasers_ = animModelLasers_->GetAnimationStates()[0];

	
}

void BotLogic::Update(float timeStep) 
{

	RigidBody* rigidbody_ = GetComponent<RigidBody>();

	
	Vector3 vel = rigidbody_->GetLinearVelocity();
	float s = vel.Length();

	if (animStateWalk_)
	{
		
		animStateWalk_->SetWeight( s > 1.0f ? 1.0f : s );
		animStateWalk_->SetLooped(true);
		animStateWalk_->AddTime(timeStep);
		animStateWalk_->SetLayer(1);

	}

	if (animStateIdle_) 
	{
		animStateIdle_->SetWeight(1.0f);
		animStateIdle_->SetLooped(true);
		animStateIdle_->AddTime(timeStep);
		animStateIdle_->SetLayer(0);
	}

	if (animStateLasers_) 
	{
		animStateLasers_->SetWeight(1.0f);
		animStateLasers_->SetLooped(true);
		animStateLasers_->AddTime(timeStep);
		
		
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
