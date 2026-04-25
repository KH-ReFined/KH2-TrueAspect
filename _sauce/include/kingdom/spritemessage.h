#pragma once

#include <cstdint>

#include "obj2d.h"
#include "sequence.h"
#include "memorymgr.h"
#include "messagedraw.h"
#include "panacea_alloc.h"

namespace dk
{
    class SpriteMessage
    {
        public:
        static uint32_t drawMessage(char* Sprite);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _drawFunction = (uint64_t)drawMessage;
                auto _drawOriginal = SignatureScan<char*>("\x40\x56\x48\x81\xEC\xF0\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\xD0\x00\x00\x00\x48\x8B\xF1\x48\x8B\x89", "xxxxxxxxxxxx????xxxxxxxxxxxxxxxxx");

                memset(_drawOriginal, 0x90, 0x265);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}