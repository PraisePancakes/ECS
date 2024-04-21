#pragma once
#include "../ECS.hpp"

class SpriteComponent : public Component
{

public:
    SpriteComponent() : Component(GetComponentTypeID<SpriteComponent>()) { std::cout << "Sprite Component Constructed " << GetComponentTypeID<SpriteComponent> << std::endl; };
    void Update() override{};
    void Render() override{};
    void Init() override{};
    ~SpriteComponent() override{};
};