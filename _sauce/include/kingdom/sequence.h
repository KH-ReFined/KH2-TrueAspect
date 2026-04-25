#pragma once

#include "memorymgr.h"

namespace YI
{
	class SEQUENCE
	{
	public:
		static void(*_SEQUENCE)(char* SEQUENCE);
		static void(*Dispose)(char* SEQUENCE);
		static void(*Control)(char* SEQUENCE);
		static void(*Draw)(char* SEQUENCE);
		static void(*SetNumber)(char* SEQUENCE, int no);
		static void(*SetNumberForce)(char* SEQUENCE, int no);
		static void(*Init)(char* SEQUENCE, char* seqd, char* image);
		static int(*GetParamCr)(char* SEQUENCE);
		static int(*GetParamEx)(char* SEQUENCE);
		static int(*GetParamSize)(char* SEQUENCE);
		static int(*GetParamX)(char* SEQUENCE);
		static int(*GetParamY)(char* SEQUENCE);
		static int(*GetActiveX)(char* SEQUENCE);
		static int(*GetActiveY)(char* SEQUENCE);
		static void(*SetScaleX)(char* SEQUENCE, float scaleX);
		static uint32_t(*GetActiveRGBA)(char* SEQUENCE);
		static void(*SetColorRate)(char* SEQUENCE, float r, float g, float b, float a);
	};
}