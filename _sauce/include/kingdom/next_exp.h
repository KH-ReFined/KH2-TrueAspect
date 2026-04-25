#pragma once

#include "sequence.h"
#include "memorymgr.h"
#include "panacea_alloc.h"

namespace dk
{
    class NEXT_EXP
    {
        public:
        static void draw(char* nextExp);


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
                auto _drawOriginal = MultiSignatureScan("\x40\x53\x55\x57\x48\x83\xEC\x30\x48\x8B\xE9\xE8\x00\x00\x00\x00", "xxxxxxxxxxxx????");

                memset(_drawOriginal[0], 0x90, 0xBF);
                memset(_drawOriginal[1], 0x90, 0xBF);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginal[0], _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
                memcpy(_drawOriginal[1], _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}