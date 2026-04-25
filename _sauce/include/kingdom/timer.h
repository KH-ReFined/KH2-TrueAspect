#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "obj2d.h"
#include "sound.h"
#include "sprite.h"
#include "sequence.h"
#include "memorymgr.h"
#include "info_base.h"

namespace dk
{
    class  TIMER
    {
        public:
        static bool(*isDown)();
        static uint32_t(*getTime)();

        static void update(char* timer);

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
                auto _updateOriginal = SignatureScan<char*>("\x40\x55\x53\x56\x57\x41\x56\x48\x8B\xEC\x48\x83\xEC\x60\x48\x8B\xD9\xE8", "xxxxxxxxxxxxxxxxxx");

                memset(_updateOriginal, 0x90, 0x44B);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_updateFunction, 0x08);
                memcpy(_updateOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}