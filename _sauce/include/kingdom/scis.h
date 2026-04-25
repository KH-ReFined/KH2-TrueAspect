#pragma once

#include "memorymgr.h"
#include "panacea_alloc.h"

namespace dk 
{
    class Scis
    {
        public:
        static void setScis(char* scissor, short x, short y, short width, short height);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _setScisFunction = (uint64_t)setScis;
                auto _setScisOriginal = SignatureScan<char*>("\x66\x89\x54\x24\x08\x66\xFF\xCA\x66\x44\x89\x44\x24\x0C\x66\x41", "xxxxxxxxxxxxxxxx");

                memset(_setScisOriginal, 0x90, 0x21);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_setScisFunction, 0x08);
                memcpy(_setScisOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}