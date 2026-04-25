#pragma once

#include <cstdint>

#include "sprite.h"
#include "sequence.h"
#include "memorymgr.h"
#include "spritemessage.h"
#include "panacea_alloc.h"

namespace dk
{
    class COMMAND_ONE
    {
        public:
        static void draw(char* Command);

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
                auto _drawOriginal = SignatureScan<char*>("\x40\x57\x48\x83\xEC\x20\x33\xC0\x48\x8B\xF9\x89\x44\x24\x30\x89", "xxxxxxxxxxxxxxxx");

                memset(_drawOriginal, 0x90, 0xA5);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}
