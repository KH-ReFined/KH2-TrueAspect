#pragma once

#include "memorymgr.h"
#include "info_base.h"

namespace dk
{
	class Obj2D
	{
		public:
		static bool(*isExist)(char* obj);
		static void(*commitSuicide)(char* obj, int unk1);
		static void(*create)(char* obj, int priority, int group);

		static char** sm_manager_ptr;
	};
}
