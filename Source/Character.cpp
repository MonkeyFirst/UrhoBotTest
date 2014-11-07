#include "Common.h"
#include "Character.h"


Character::Character(Context* context) : LogicComponent(context)
{
	// Only the physics update event is needed: unsubscribe from the rest for optimization
	SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Character::RegisterObject(Context* context)
{
	context->RegisterFactory<Character>();
}

void Character::Start()
{
	// Component has been inserted into its scene node. Subscribe to events now
	SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Character, HandleNodeCollision));
	rigidbody_ = GetNode()->GetComponent<RigidBody>();
	//rigidbody_->SetFriction(1.0f);

	cameraNode_ = GetNode()->GetChild("cameraNode", true);
	gunNode_ = GetNode()->GetChild("gunNode", true);

}

void Character::Update(float timeStep) 
{

}

bool Character::Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
	hitDrawable = 0;

	Graphics* graphics = GetSubsystem<Graphics>();
	//Camera* camera = cameraNode_->GetComponent<Camera>();
	//Ray cameraRay = camera->GetScreenRay((float)graphics->GetWidth() * 0.5f, (float) graphics->GetHeight() * 0.5f);
	//Ray cameraRay = camera->GetScreenRay((float) 0.5f, (float) 0.5f);
	Ray gunRay = Ray(gunNode_->GetWorldPosition(), gunNode_->GetWorldDirection());



	// Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
	PODVector<RayQueryResult> results;
	//RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);
	RayOctreeQuery query(results, gunRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY, -1);
	

	Node* node = GetNode(); // playerNode
	Scene* scene = node->GetScene(); // root scene
	Octree* octree = scene->GetComponent<Octree>();
	octree->RaycastSingle(query);

	if (results.Size())
	{
		RayQueryResult& result = results[0];
		hitPos = result.position_;
		hitDrawable = result.drawable_;
		return true;
	}

	return false;
}

void Character::FixedUpdate(float timeStep)
{
	/// \todo Could cache the components for faster access instead of finding them each frame
	RigidBody* body = GetComponent<RigidBody>();

	const float MOVE_SPEED = 800.0f;

	Input* input = GetSubsystem<Input>();

	Quaternion worldRotation = cameraNode_->GetWorldRotation();
	worldRotation.z_ = 0.0f;

	Vector3 oldVel = rigidbody_->GetLinearVelocity();
	
	if (input->GetKeyDown('W'))
		//cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::FORWARD * MOVE_SPEED * timeStep);
	if (input->GetKeyDown('S'))
		//cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::BACK * (MOVE_SPEED / 2.0f) * timeStep);

	if (input->GetKeyDown('A'))
		//cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::LEFT * (MOVE_SPEED / 2.0f) * timeStep);

	if (input->GetKeyDown('D'))
		//cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
		rigidbody_->SetLinearVelocity(worldRotation * Vector3::RIGHT * MOVE_SPEED * timeStep);

	static bool isAlredyJumping = false;
	if (input->GetKeyDown(KEY_SPACE)) 
	{
		if (isAlredyJumping == false) 
		{
			rigidbody_->SetLinearVelocity(worldRotation * Vector3::UP * MOVE_SPEED  * timeStep);
			isAlredyJumping = true;
		}
	}
	else 
	{
		isAlredyJumping = false;

	}

	static bool isAlradyFired = false;

	if (input->GetMouseButtonDown(MOUSEB_LEFT)) 
	{
		if (!isAlradyFired) 
		{
			
			isAlradyFired = true;
		}	
	} 
	else 
	{
		isAlradyFired = false;
	}

}

void Character::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
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
