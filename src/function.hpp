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

	template<typename _T>
	class CircularWave : public Wave
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			glm::vec2 dir = _vec - m_origin;
			float l = glm::length(dir);
			dir /= l;
			return _T::process(dir, l, m_shift);
		}
	};

	template<typename _T1, typename _T2>
	class WavePack
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			return wave1(_vec) + wave2(_vec);
		}

		void setShift(float _shift)
		{
			wave1.setShift(_shift);
			wave2.setShift(_shift);
		}

		_T1 wave1;
		_T2 wave2;
	};

	// ********************************************** //
	class Sinus
	{
	public:
		static glm::vec2 process(glm::vec2 _dir, float _x, float _y)
		{
			return sin(_x + _y) * _dir;
		}
	};

	typedef CircularWave<Sinus> SinusWave;

	// ********************************************** //

	class Single
	{
	public:
		static glm::vec2 process(glm::vec2 _dir, float _x, float _y)
		{
			return std::min(2.f, 1.f/abs(0.01f+_x-_y)) * _dir;
		}
	};

	typedef CircularWave<Single> SingleWave;

	// ********************************************** //
/*	class SingleWave : public Wave
	{
	public:
		glm::vec2 operator()(glm::vec2 _vec)
		{
			glm::vec2 dir = _vec - m_origin;
			float l = length(dir);
			float d = abs(m_shift - l);
			return std::min(5.f/l, 10.f) std::min(2.f,1.f/d)  * glm::normalize(dir);

		//	return glm::vec2(0.f, 0.f);
		}
	};*/

	

	// ********************************************** //
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