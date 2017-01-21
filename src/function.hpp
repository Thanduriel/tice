#pragma once

#include <glm.hpp>
#include <math.h>


namespace Physics {
	class Wave
	{
	public:

		void setOrigin(glm::vec2 _vec) { m_origin = _vec; }
		void setShift(float _shift) { m_shift = _shift; }
	protected:
		glm::vec2 m_origin;
		float m_shift;
	};

	class SinusWave : public Wave
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			glm::vec2 dir = _vec - m_origin;
			return sin(m_shift + glm::length(dir)) * glm::normalize(dir);
		}
	};

	class SingleWave : public Wave
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			glm::vec2 dir = _vec - m_origin;
			float l = length(dir);
			float d = abs(m_shift - l);
			if (d < 2.f && d > 1.f) return 5.f/l * glm::normalize(dir);

			return glm::vec2(0.f, 0.f);
		}
	};

	class CrazyWave : public Wave
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			glm::vec2 dir = _vec - m_origin;
			float l = abs(m_shift - length(dir));
			if (l < 2.f) return 1 / l * glm::normalize(dir);

			return glm::vec2(0.f, 0.f);
		}
	};
}