
#include <Engine/EngineInternal/Components/Behaviour/BehaviourComponent.h>
#include "GameObjectBase.h"

std::shared_ptr<Component> GameObjectBase::addComponent(const std::shared_ptr<Component> & component) {

    if (Component::isTypeOf<BehaviourComponent>(component)) {
        Component::asType<BehaviourComponent>(component)->SetObject(this);
    }

    components.push_back(component);

    return components[components.size() - 1];
}