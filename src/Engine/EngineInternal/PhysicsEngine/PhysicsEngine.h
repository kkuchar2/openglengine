#pragma once

#include <memory>
#include <iostream>

#include <bullet3/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <bullet3/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <Engine/EngineInternal/Scene/Transform.h>

#include "btBulletDynamicsCommon.h"

class PhysicsEngine {

    private:
        /// Collision configuration contains default setup for memory, collision setup
        btDefaultCollisionConfiguration * collisionConfiguration = nullptr;

        /// Default collision dispatcher
        btCollisionDispatcher * dispatcher = nullptr;

        /// General purpose broadphase. Another possible: btAxis3Sweep.
        btBroadphaseInterface * overlappingPairCache = nullptr;

        /// The default constraint solver.
        /// For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        btSequentialImpulseConstraintSolver * solver = nullptr;

        /// Physics world
        btDiscreteDynamicsWorld * dynamicsWorld = nullptr;

        /// Collision shapes tracking
        /// Collision shapes should be reused among rigidbodies whenever possible
        btAlignedObjectArray<btCollisionShape*> collisionShapes;

        void init();

        void cleanup();

    public:
        PhysicsEngine();
        ~PhysicsEngine();

        void step(float timeStep);

        int addCollisionBox(const float & mass, const glm::vec3 & position, const glm::vec3 & size);
        int addCollisionSphere(const float & mass, const glm::vec3 & position, const glm::vec3 & size);
        std::shared_ptr<Transform> getTransform(const int & idx);
        void runTestSimulation(const int & iterations);
        void test();
};