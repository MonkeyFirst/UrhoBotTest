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
	
	animStateWalk_ = animModelBot_->GetAnimationStates()[0];
	animStateIdle_ = animModelBot_->GetAnimationStates()[1];
	animStateLasers_ = animModelLasers_->GetAnimationStates()[0];


	
}

void BotLogic::Update(float timeStep) 
{
	if (animStateWalk_)
	{
		animStateWalk_->SetWeight(1.0f);
		animStateWalk_->SetLooped(true);
		animStateWalk_->AddTime(timeStep);
	}

	if (animStateIdle_) 
	{
		animStateIdle_->SetWeight(1.0f);
		animStateIdle_->SetLooped(true);
		animStateIdle_->AddTime(timeStep);
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
