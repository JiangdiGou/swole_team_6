//#include "collision_narrow.h"
#include "Body.h"
#include "Resolution.h"

// Physics system
class PhysicsManager : public ISystem
{
public:
	PhysicsManager();
	~PhysicsManager();

	std::vector<RigidBody *>bodies; // Holds the bodies
	std::vector<Manifold> contacts; // Holds the contacts
	std::vector<Primitive *>colliders; // Holds the colliders

	// Overloaded methods
    bool Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void IntegrateForces(RigidBody *body, float dt);
	void IntegrateVelocity(RigidBody *body, float dt);
	void Step(float dt);
	void ColliderCheck();
	void RigidBodyCheck();

	//I changed this from a Vector2D so I could load it from Setting
	float *GRAVITY;
};

extern PhysicsManager *physics;