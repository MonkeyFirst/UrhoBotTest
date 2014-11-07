#include "Common.h"

DEFINE_APPLICATION_MAIN(UrhoQuickStart)

UrhoQuickStart::UrhoQuickStart(Context* context) : Application(context)
{
	engineParameters_["WindowTitle"] = GetTypeName();
	engineParameters_["FullScreen"]  = false;
	engineParameters_["Headless"]    = false;
	engineParameters_["WindowWidth"] = 1280;
	engineParameters_["WindowHeight"] = 720; 
	engineParameters_["LogName"]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
	//engineParameters_["RenderPath"] = "Bin\CoreData\RenderPaths\Deferred.xml";
	//engineParameters_["FlushGPU"] = true;

}

void UrhoQuickStart::Start()
{
	Graphics* graphics = GetSubsystem<Graphics>();
	Renderer* renderer = GetSubsystem<Renderer>();
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	CreateConsole();
	SubscribeToEvents();
	LoadScene("MainScene.xml");
	CameraSetup("cameraNode");
	OtherSetup();

}

void UrhoQuickStart::LoadScene(Urho3D::String sceneFileName) 
{
	scene_ = new Scene(context_);
	File sceneFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/" + sceneFileName, FILE_READ);
	scene_->LoadXML(sceneFile);

}

void UrhoQuickStart::CameraSetup(Urho3D::String cameraNodeName)
{
	Renderer* renderer = GetSubsystem<Renderer>();

	cameraNode_ = scene_->GetChild(cameraNodeName, true);
	Camera* camera = cameraNode_->GetComponent<Camera>();
	camera->SetFarClip(1000.0f);
	camera->SetFov(75.0f);
	// Вид
	SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
	renderer->SetViewport(0, viewport);

	yaw_ = 0.0f;
	pitch_ = 0.0f;	
}


void UrhoQuickStart::OtherSetup()
{
	Graphics* graphics = GetSubsystem<Graphics>();
	Renderer* renderer = GetSubsystem<Renderer>();
	ResourceCache* cache = GetSubsystem<ResourceCache>();

}

void UrhoQuickStart::CreateConsole()
{
	// Get default style
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

	// Create console
	Console* console = engine_->CreateConsole();
	console->SetDefaultStyle(xmlFile);
	console->GetBackground()->SetOpacity(0.8f);
	
}


void UrhoQuickStart::SubscribeToEvents()
{
	SubscribeToEvent(E_UPDATE, HANDLER(UrhoQuickStart, HandleUpdate));
	SubscribeToEvent(E_KEYDOWN, HANDLER(UrhoQuickStart, HandleKeyDown));
	SubscribeToEvent(E_SCENEUPDATE, HANDLER(UrhoQuickStart, HandleSceneUpdate));
}

void UrhoQuickStart::CameraViewRotate(float timeStep) 
{
	Input* input = GetSubsystem<Input>();

	// Movement speed as world units per second
	const float MOVE_SPEED = 800.0f;
	// Mouse sensitivity as degrees per pixel
	const float MOUSE_SENSITIVITY = 0.1f;

	// Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
	IntVector2 mouseMove = input->GetMouseMove();

	yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
	pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
	pitch_ = Clamp(pitch_, -90.0f, 90.0f);
	//yaw_ = Clamp(yaw_, -720.0f, 720.0f);

	// Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
	cameraNode_->SetWorldRotation(Quaternion(pitch_, yaw_, 0.0f));

}


void UrhoQuickStart::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
	using namespace Update;

	// Take the frame time step, which is stored as a float
	float timeStep = eventData[P_TIMESTEP].GetFloat();

	CameraViewRotate(timeStep);
	//reflectionCameraNode_->SetWorldPosition(cameraNode_->GetWorldPosition());

}


void UrhoQuickStart::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	using namespace KeyDown;
	int key = eventData[P_KEY].GetInt();

	if (key == KEY_ESC)
	{
		Console* console = GetSubsystem<Console>();
		if (console->IsVisible())
			console->SetVisible(false);
		else

			engine_->Exit();
	}
	else if (key == KEY_F1) 
	{
		Console* console = GetSubsystem<Console>();
		console->Toggle();
	}
}

void UrhoQuickStart::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{


}
