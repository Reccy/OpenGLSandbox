#pragma once
#include "RML/RML.h"

namespace ROGLL
{
	class Camera
	{
	public:
		Camera(float width, float height, float fov);

		const RML::Matrix<double, 4, 4> matrix() const;
	private:
		RML::Transform m_transform;
		RML::Matrix<double, 4, 4> m_projectionMatrix;
		float m_aspectRatio;
		float m_fov;

		float m_zNear = 0.1f;
		float m_zFar = 100.0f;
	};
}
