#pragma once

#include "memorymgr.h"

namespace dk
{
	class INFO_BASE
	{
		public:
		static void(*create)(char* infoBase, int priority, int height, int draw_priority, int group, int align);
		static void(*update)(char* infoBase);

		static char* sm_height;
	};
}