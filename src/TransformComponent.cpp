#include "../include/TransformComponent.hpp"

TransformComponent::TransformComponent() : Component(GetComponentTypeID<TransformComponent>())
{
    std::cout << "Transform Component Constructed" << std::endl;
};

void TransformComponent::Translate(float dX, float dY) noexcept
{
    this->xPos += dX;
    this->yPos += dY;
};

void TransformComponent::Update(){};
void TransformComponent::Init(){};
void TransformComponent::Render(){};

TransformComponent::~TransformComponent(){};
