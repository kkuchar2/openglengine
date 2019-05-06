#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
    init();
}

void PhysicsEngine::init() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10.0f, 0));
    addCollisionBox(0.0f, glm::vec3(0.0f, -50.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
}

void PhysicsEngine::test() {
    /// The ground is a cube of side 100 at position y = -56.
    /// The sphere will hit it at y = -6, with center at -5

    addCollisionBox(0.0f, glm::vec3(0.0f, -56.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f));
    addCollisionSphere(1.0f, glm::vec3(0.0f), glm::vec3(1.0f));

    runTestSimulation(2500);
}


int PhysicsEngine::addCollisionBox(const float & mass, const glm::vec3 & position,  const glm::vec3 & size) {

    btCollisionShape * groundShape = new btBoxShape(
            btVector3(btScalar(size.x / 2.0f), btScalar(size.y / 2.0f), btScalar(size.z / 2.0f)));

    collisionShapes.push_back(groundShape);

    /// Set transform
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(position.x, position.y, position.z));

    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);

    if (isDynamic) {
        groundShape->calculateLocalInertia(mass, localInertia);
    }

    /// Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    auto * myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    auto * body = new btRigidBody(rbInfo);
    body->setRestitution(0.8);


    /// Add the body to the dynamics world
    dynamicsWorld->addRigidBody(body);

    return dynamicsWorld->getNumCollisionObjects();
}


int PhysicsEngine::addCollisionSphere(const float & mass, const glm::vec3 & position, const glm::vec3 & size) {
    btCollisionShape * colShape = new btSphereShape(btScalar(size.x));
    collisionShapes.push_back(colShape);

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(position.x, position.y, position.z));

    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);

    if (isDynamic) {
        colShape->calculateLocalInertia(mass, localInertia);
    }

    /// Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    auto * myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    auto * body = new btRigidBody(rbInfo);

    dynamicsWorld->addRigidBody(body);

    return dynamicsWorld->getNumCollisionObjects();
}

void PhysicsEngine::step(float timeStep) {
    dynamicsWorld->stepSimulation(timeStep, 10, 1.f / 60.f);
}

void PhysicsEngine::runTestSimulation(const int & iterations) {

    for (int i = 0; i < iterations; i++) {
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        //print positions of all objects
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
            btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody * body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState()) {
                body->getMotionState()->getWorldTransform(trans);
            }
            else {
                trans = obj->getWorldTransform();
            }
            printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()),
                   float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
        }
    }
}


void PhysicsEngine::cleanup() {

    /// Remove the rigidbodies from the dynamics world and delete them
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {

        btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody * body = btRigidBody::upcast(obj);

        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }

        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    /// Delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++) {
        btCollisionShape * shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    /// Delete dynamics world
    delete dynamicsWorld;

    /// Delete solver
    delete solver;

    /// Delete broadphase
    delete overlappingPairCache;

    /// Delete dispatcher
    delete dispatcher;

    /// Delete collision configuration
    delete collisionConfiguration;

    /// Clear collision shapes array
    collisionShapes.clear();
}

PhysicsEngine::~PhysicsEngine() {
    cleanup();
}

std::shared_ptr<Transform> PhysicsEngine::getTransform(const int & idx) {
    btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[idx];
    btRigidBody * body = btRigidBody::upcast(obj);
    btTransform trans;
    if (body && body->getMotionState()) {
        body->getMotionState()->getWorldTransform(trans);
    }
    else {
        trans = obj->getWorldTransform();
    }

    std::shared_ptr<Transform> transform = std::make_shared<Transform>();

    btVector3 origin = trans.getOrigin();
    btQuaternion rotation = trans.getRotation();

    transform->position = glm::vec3(origin.getX(), origin.getY(), origin.getZ());

    return transform;
}





