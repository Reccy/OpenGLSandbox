#pragma once
#include "RML/RML.h"

namespace ROGLL
{
	class Camera
	{
	public:
		RML::Transform transform;
	public:
		/// <summary>
		/// Creates a Camera with orthographic projection
		/// </summary>
		Camera(float width, float height);

		void SetOrthographic(float width, float height);
		void SetPerspective(float width, float height, float fov);

		const RML::Matrix<double, 4, 4> GetViewProjectionMatrix() const;
	private:
		RML::Matrix<double, 4, 4> m_projectionMatrix;
		float m_aspectRatio;

		float m_zNear = 0.1f;
		float m_zFar = 1000.0f;
	};
}
