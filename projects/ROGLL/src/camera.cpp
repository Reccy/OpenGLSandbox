#include "camera.h"

namespace ROGLL
{
	Camera::Camera(float width, float height)
		: transform(),
		m_aspectRatio(height/width)
	{
		SetOrthographic(width, height);
	}

	void Camera::SetOrthographic(float width, float height)
	{
		float w = 1.0f / width;
		float h = 1.0f / height;
		float x = -(2.0f / (m_zFar - m_zNear));
		float y = -((m_zFar + m_zNear) / (m_zFar - m_zNear));

		m_projectionMatrix = RML::Matrix<double, 4, 4>({
			w, 0, 0, 0,
			0, h, 0, 0,
			0, 0, x, y,
			0, 0, 0, 1
		});
	}

	const RML::Matrix<double, 4, 4> Camera::GetViewProjectionMatrix() const
	{
		return m_projectionMatrix * transform.matrix().invert();
	}
}
