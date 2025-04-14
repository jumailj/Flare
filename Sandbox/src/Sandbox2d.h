#pragma once

#include <Flare/Core/Flare.h>
#include "glm/glm.hpp"

class Sandbox2D : public Flare::Layer{

    //todo fix acpect ration when changing camera aspect ratio.
    public:
    Sandbox2D();
	virtual ~Sandbox2D() = default;


    virtual void OnAttach() override;
    virtual void OnDetach() override;

	// mainupdate loop;
	virtual void OnUpdate(Flare::Timestep ts) override;
	// graphics;
	virtual void OnImGuiRender() override;
    // events;
	virtual void OnEvent(Flare::Event& event) override;

public:

	Flare::Ref<Flare::Texture2D>m_CheckTexture;
	Flare::Ref<Flare::Texture2D> m_player;

	Flare::OrthographicCameraController m_CameraController;
	
	glm::vec3 playerPos = {0.0f, 0.0f, 0.0f};

};