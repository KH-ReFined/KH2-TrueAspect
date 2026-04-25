#pragma once

#include <map>
#include <string>
#include <cstdint>

#include "memorymgr.h"

using namespace std;

namespace YS
{
    class PANACEA_ALLOC
    {
        public:
        static map<string, char*> MEMORY_BLOCK;

        static char* (*alloc)(char* instance, size_t size);
        static void (*free)(char* instance, char* address);

        static char* _allocInstance;
        static char* _functionSpace;

        static char* Get(string Key);
        static void Free(string Key);
        static void Allocate(string  Key, size_t Size);
    };
}