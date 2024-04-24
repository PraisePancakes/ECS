#pragma once
#include "../ECS.hpp"

class SpriteComponent : public Component
{
    // add texture member here, for example, if using SDL do,
    //  SDL_Texture* m_SpriteTexture = nullptr;
public:
    SpriteComponent() : Component(GetComponentTypeID<SpriteComponent>()) { std::cout << "Sprite Component Constructed " << GetComponentTypeID<SpriteComponent> << std::endl; };
    SpriteComponent *Clone() const override
    {
        return new SpriteComponent(*this);
    }

    // void SetTexture(const char* texture_path) {};
    void Update() override{};
    void Render() override{};
    void Init() override{};
   
    ~SpriteComponent() override{};
};