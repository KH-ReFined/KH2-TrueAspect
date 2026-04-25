#pragma once

#include <cstdint>

#include "obj2d.h"
#include "sequence.h"
#include "memorymgr.h"
#include "panacea_alloc.h"

namespace dk
{
    class CIRCLE_MASK
    {
        public:
        static void draw(char* Sprite);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _drawFunction = (uint64_t)draw;
                auto _drawOriginal = SignatureScan<char*>("\x40\x57\x48\x83\xEC\x50\x48\x8B\xF9\x48\x8B\x89\x40\x02", "xxxxxxxxxxxxxx");

                memset(_drawOriginal, 0x90, 0xF5);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}