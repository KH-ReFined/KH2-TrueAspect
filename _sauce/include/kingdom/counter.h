#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>

#include "obj2d.h"
#include "sprite.h"
#include "sequence.h"
#include "info_base.h"
#include "memorymgr.h"
#include "cache_buff.h"

namespace dk
{
    class COUNTER
    {
        public:
        static void(*forceLeave)(char* counter);
        static void update(char* counter);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _updateFunction = (uint64_t)update;
                auto _updateOriginal = SignatureScan<char*>("\x48\x89\x5C\x24\x18\x48\x89\x74\x24\x20\x55\x57\x41\x56\x48\x8B\xEC\x48\x83\xEC\x50\x48\x8B\x05", "xxxxxxxxxxxxxxxxxxxxxxxx");

                memset(_updateOriginal, 0x90, 0x38E);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_updateFunction, 0x08);
                memcpy(_updateOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}