#pragma once

#include <GL/GL.h>


namespace Graphic{

	enum class RenderModes {
		Simple,
		Textured,
		WireFrame
	};

	class DepthState
	{
	public:
		enum struct COMPARISON_FUNC {
			LESS = 0x0201,			///< Comparison function less '<'
			GREATER = 0x0204,		///< Comparison function greater '>'
			EQUAL = 0x0202,			///< Comparison function equal '=='
			NEVER = 0x0200,			///< Fail always
			ALWAYS = 0x0207			///< Disables z-Testing / stencil test
		};


		DepthState(COMPARISON_FUNC _func) : m_function(_func) {}

		void set() const;
	private:
		COMPARISON_FUNC m_function;
	};

	// ********************************************************* //

	class BlendMode
	{
	public:
		enum struct BLEND_OPERATION {
			ADD = 0x8006,
			SUBTRACT = 0x800A,
			REVERSE_SUBTRACT = 0x800B,
			MIN = 0x8007,
			MAX = 0x8008,
			DISABLE
		};

		enum struct BLEND {
			ZERO = 0,
			ONE = 1,
			SRC_ALPHA = 0x0302,
			INV_SRC_ALPHA = 0x0303,
		};

		BlendMode(BLEND_OPERATION _equation, BLEND _src, BLEND _dst) :
			m_equation(_equation), m_opSrc(_src), m_opDst(_src) {}

		void set() const;
	private:
		BLEND_OPERATION m_equation;
		BLEND m_opSrc;
		BLEND m_opDst;
	};

	// ********************************************************* //

	class Effect
	{
	public:
		//@param name without file ending of the shaders
		Effect(const char* _name, BlendMode _blendMode, DepthState _depthState);
		~Effect();

		void set() const;
		GLuint getProgId() const { return m_id; }
	private:
		GLuint m_id;

		BlendMode m_blendMode;
		DepthState m_depthState;
	};

}