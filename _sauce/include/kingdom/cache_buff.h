#pragma once

#include "memorymgr.h"

namespace YS
{
	class CACHE_BUFF
	{
		public:
		static char* (*SearchByName)(const char* fileName, int pri);
	};
}