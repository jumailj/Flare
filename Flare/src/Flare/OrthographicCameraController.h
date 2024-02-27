#pragma once

#include <Flare/Core/Timestep.h>
#include <Flare/Renderer/OrthographicCamera.h>

#include <Flare/Events/ApplicationEvent.h>
#include <Flare/Events/MouseEvent.h>


namespace Flare{

    class OrthographicCameraController
    {
    public:

            OrthographicCameraController(float aspectRation, bool rotaiton = false);

            void OnUpdate(Timestep ts);
            void OnEvent(Event&e);

            void OnResize(float width, float height);

            OrthographicCamera& GetCamera() {return m_Camera;}
            const OrthographicCamera& GetCamera() const {return m_Camera;}

            float GetZoomLevel() const {return m_ZoomLevel;}
            void SetZoomLevel(float level) { m_ZoomLevel = level;}

    private:
            bool OnMouseScrolled(MouseScrolledEvent& e);
            bool OnWindowResize(WindowResizeEvent& e);


    private:

        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

    };

}