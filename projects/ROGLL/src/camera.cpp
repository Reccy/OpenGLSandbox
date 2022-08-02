#include "camera.h"

namespace ROGLL
{
	Camera::Camera(float width, float height, float fov)
		: m_transform(),
		m_aspectRatio(width/height),
		m_fov(fov)
	{
		float t = tan(fov / 2.0f);

		float a = 1.0f / (m_aspectRatio * t);
		float b = 1.0f / t;
		float c = -((m_zFar + m_zNear) / (m_zFar - m_zNear));
		float d = -((2.0f * m_zFar * m_zNear) / (m_zFar - m_zNear));
		float e = -1.0f;

		m_projectionMatrix = RML::Matrix<float, 4, 4>({
			a,0,0,0,
			0,b,0,0,
			0,0,c,d,
			0,0,e,0
		});
	}

	const RML::Matrix<double, 4, 4> Camera::matrix() const
	{
		return m_projectionMatrix * m_transform.matrix();
	}
}
