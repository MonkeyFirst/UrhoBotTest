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


}

void BotLogic::Update(float timeStep) 
{
	AnimatedModel* model = GetComponent<AnimatedModel>();
	if (model->GetNumAnimationStates())
	{
		AnimationState* state = model->GetAnimationStates()[1];
		// Enable full blending weight and looping
		state->SetWeight(1.0f);
		state->SetLooped(true);
		state->AddTime(timeStep);
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
