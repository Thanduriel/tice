#pragma once

#include "body.hpp"

namespace Game {
	
	class Character : public Physics::Body
	{
	public:
		Character();

		void process(float _deltaTime);

		void setTargetVelocity(glm::vec2 _targetVelocity) { m_targetVelocity = _targetVelocity; }
	private:
		glm::vec2 m_targetVelocity;
	};
}