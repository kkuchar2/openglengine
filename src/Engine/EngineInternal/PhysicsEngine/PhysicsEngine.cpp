#include <bullet3/examples/ThirdPartyLibs/BussIK/MathMisc.h>
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

    Transform t;
    t.position = glm::vec3(0.0f, -100.0f, 0.0f);
    t.rotation = glm::vec3(0.0f);
    t.scale = glm::vec3(200.0f, 200.0f, 200.0f);

    addCollisionBox(0., 0.9f, t);
}

void PhysicsEngine::test() {
    Transform t;
    t.position = glm::vec3(0.0f, 10.0f, 0.0f);
    t.rotation = glm::vec3(0.0f);
    t.scale = glm::vec3(1.0f);


    addCollisionBox(1.0f, 0.9f, t);
    runTestSimulation(1000);
}


int PhysicsEngine::addCollisionBox(const float & mass, const float & restitution, const Transform & transform) {

    btCollisionShape * shape = new btBoxShape(
            btVector3(
                    btScalar(transform.scale.x / 2.0f),
                    btScalar(transform.scale.y / 2.0f),
                    btScalar(transform.scale.z / 2.0f)
            ));

    collisionShapes.push_back(shape);

    /// Set transform
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(transform.position.x, transform.position.y, transform.position.z));
    btQuaternion quat;
    quat.setEuler(transform.rotation.y, transform.rotation.x, transform.rotation.z);
    t.setRotation(quat);


    bool isDynamic = (mass > 0.1f);

    btVector3 localInertia(0, 0, 0);

    if (isDynamic) {
        shape->calculateLocalInertia(mass, localInertia);
    }

    std::cout << "local inertia: " << localInertia.getX() << " " << localInertia.getY() << " " << localInertia.getZ()
              << std::endl;

    /// Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    auto * myMotionState = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    auto * body = new btRigidBody(rbInfo);
    body->setRestitution(restitution);

    /// Add the body to the dynamics world
    dynamicsWorld->addRigidBody(body);

    return dynamicsWorld->getNumCollisionObjects();
}


int PhysicsEngine::addCollisionSphere(const float & mass, const float & restitution, const Transform & transform) {
    btCollisionShape * colShape = new btSphereShape(btScalar(transform.scale.x));
    collisionShapes.push_back(colShape);

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(transform.position.x, transform.position.y, transform.position.z));

    btQuaternion quat;
    quat.setEuler(transform.rotation.y, transform.rotation.x, transform.rotation.z);
    startTransform.setRotation(quat);

    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);

    if (isDynamic) {
        colShape->calculateLocalInertia(mass, localInertia);
    }

    /// Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    auto * myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    auto * body = new btRigidBody(rbInfo);

    body->setRestitution(restitution);

    dynamicsWorld->addRigidBody(body);

    return dynamicsWorld->getNumCollisionObjects();
}

void PhysicsEngine::step(float timeStep) {
    dynamicsWorld->stepSimulation(timeStep, 100, 1.f / 60.f);
}

void PhysicsEngine::runTestSimulation(const int & iterations) {

    for (int i = 0; i < iterations; i++) {
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        //print positions of all objects
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 1; j--) {
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

btVector3 PhysicsEngine::quatToEuler(const btQuaternion & q1) {
    float heading, attitude, bank;

    double test = q1.getX() * q1.getY() + q1.getZ() * q1.getW();

    if (test > 0.499) { // singularity at north pole
        heading = 2 * atan2(q1.getX(), q1.getW());
        attitude = PI / 2;
        bank = 0;
        return btVector3(0, 0, 0);
    }
    if (test < -0.499) { // singularity at south pole
        heading = -2 * atan2(q1.getX(), q1.getW());
        attitude = -PI / 2;
        bank = 0;
        return btVector3(0, 0, 0);
    }

    double sqx = q1.getX() * q1.getX();
    double sqy = q1.getY() * q1.getY();
    double sqz = q1.getZ() * q1.getZ();
    heading = atan2(2 * q1.getY() * q1.getW() - 2 * q1.getX() * q1.getZ(), 1 - 2 * sqy - 2 * sqz);
    attitude = asin(2 * test);
    bank = atan2(2 * q1.getX() * q1.getW() - 2 * q1.getY() * q1.getZ(), 1 - 2 * sqx - 2 * sqz);
    btVector3 vec(bank, heading, attitude);
    return vec;
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

    btScalar yawZ;
    btScalar pitchY;
    btScalar rollX;

    trans.getRotation().getEulerZYX(yawZ, pitchY, rollX);

    transform->position = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
    transform->rotation = glm::vec3(rollX, pitchY, yawZ);

    return transform;
}





