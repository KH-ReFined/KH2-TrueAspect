#pragma once

#include "memorymgr.h"

using namespace std;

namespace YS
{
	class MESSAGE
	{
		public:
		static char* (*GetData)(int id);
		static size_t(*GetSize)(const char* message);
		static char* (*Sprintf)(char* buff, const char* string, ...);
	};
}
