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

void Character::CreateBullet() 
{
	Vector3 origin = gunNode_->GetWorldPosition();
	Vector3 dir = gunNode_->GetWorldDirection();
	ResourceCache* cache = GetSubsystem<ResourceCache>();

	XMLFile* cubePrebabFile = cache->GetResource<XMLFile>("Objects/bullet.xml");
	Node* bullet = GetNode()->GetScene()->InstantiateXML(cubePrebabFile->GetRoot(), origin, Quaternion(0.0f,0.0f,0.0f), LOCAL);
	//StaticModel* boxStaticModel = bullet->CreateComponent<StaticModel>();
	//boxStaticModel->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	//boxStaticModel->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));

	//RigidBody* r = bullet->CreateComponent<RigidBody>();
	//r->SetMass(0.1f);
	//r->SetLinearVelocity(dir * 100.0f);
	//
	//CollisionShape* c = bullet->CreateComponent<CollisionShape>();
	//c->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	bullet->SetScale(Vector3(0.1f, 0.1f, 0.1f));
	RigidBody* r = bullet->GetComponent<RigidBody>();
	r->SetLinearVelocity(dir * 30.0f);

}

void Character::PaintDecal()
{
	Vector3 hitPos;
	Drawable* hitDrawable;

	if (Raycast(250.0f, hitPos, hitDrawable))
	{
		// Check if target scene node already has a DecalSet component. If not, create now
		Node* targetNode = hitDrawable->GetNode();
		DecalSet* decal = targetNode->GetComponent<DecalSet>();
		if (!decal)
		{
			ResourceCache* cache = GetSubsystem<ResourceCache>();

			decal = targetNode->CreateComponent<DecalSet>();
			decal->SetMaterial(cache->GetResource<Material>("Materials/UrhoDecal.xml"));
		}
		// Add a square decal to the decal set using the geometry of the drawable that was hit, orient it to face the camera,
		// use full texture UV's (0,0) to (1,1). Note that if we create several decals to a large object (such as the ground
		// plane) over a large area using just one DecalSet component, the decals will all be culled as one unit. If that is
		// undesirable, it may be necessary to create more than one DecalSet based on the distance
		decal->AddDecal(hitDrawable, hitPos, cameraNode_->GetRotation(), 0.5f, 1.0f, 1.0f, Vector2::ZERO,
			Vector2::ONE);
	}
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

	const float MOVE_SPEED = 400.0f;

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
			PaintDecal();
			CreateBullet();
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
	if ( myAttr.GetString() == "grib") 
	{

	}

}
