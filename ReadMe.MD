# Newton Game Dynamics 1.57 Wrapper

This is a Physics Wrapper which you can use for your project.

Add the GamePhysics folder to your GameFolder (aka where your source code is)

Using the wrapper is pretty straight forward you create a World Class setup your physics dimensions and other relevent settings.

I hope the following psuedo code gives you a starting point

----

// This callback transforms what you see on screen based on the abstract physics body attached to it
static void transformCallback(const NewtonBody* const body, const dFloat* const matrix)
{
	// Grab our user data
	MySceneNude* pNode = body->getUserData();
	// Make the incoming SceneNode's matrix match the matrix of its physics body
	p->setSceneNodeMatrix(matrix);
}

int main()
{
	// Create the physics world
	PhysicsWorld physicsWorld;
	
	// Initialise the Physics World
	physicsWorld.init(0, 0); // Function pointers here can be 0 and still work just fine. NOTE: Most of your callbacks should be in your Game:: singleton that way callbacks have access to everything in global scope

	// Make the PhysicsWorld
	MyPhysicsDebugger myPhysicsDebuuger;
	myPhysicsDebuuger.setNewtonWorld(physicsWorld.getNewtonWorld());
	
	// Make our CollisoinFramesFactory
	CollisoinFramesFactory myCollisionFramesFactory;
	
	// Make the Physics body
	MySceneSceneNode myNode;
	myNode.setNewtonWorld(physicsWorld.getNewtonWorld());
	myNode.setTransformCallback(transformCallback); // Every frame Newton will call this callback which will update the visual geometry to be in the same position/rotation and scale as the physics body
	
	bool isRunning = true;
	while(isRunning == true)
	{
		myGameEngineHandleEvents();
		
		if (myGameEngine.isFinished())
			isRunning = false;

		myGameEngineThink();
		
		myGameEngineUpdate();		
		physicsWorld.update(); // This should eventually find itsway into your myGameEngineUpdate method and be called 1.0f / 60.0f frames per second
		
		mySceneManager->drawEverything();
		myPhysicsDebugger.draw(); // NOTE: NewtonBodies are automatically added to the debugger, rays, joints, joints, collisionframes, vehicles need to be added each frame 
		
	}
	
	// Free the Physics World
	physicsWorld.free();
}

/* Our Custom Scene Node which implements both an Animated Mesh and a Physics body*/
class MySceneSceneNode : public AnimatedMesh, public PhysicsBody
{
	// Constructor
	MySceneSceneNode()
	{
		this->setUserData(this); // Connects this class to the physics body's getUserData method
	}
	
	...
	
};

----


