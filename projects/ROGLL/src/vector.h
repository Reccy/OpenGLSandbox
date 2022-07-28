#pragma once

namespace ROGLL
{
	template<typename T>
	struct Vector4 {
		T x, y, z, w;
	};

	template<typename T>
	struct Vector3 {
		T x, y, z;
	};

	template<typename T>
	struct Vector2 {
		T x, y;
	};

	template<typename T>
	struct Vector1 {
		T x;
	};
}
