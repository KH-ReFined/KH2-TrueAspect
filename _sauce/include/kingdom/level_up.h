#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "sprite.h"
#include "message.h"
#include "sequence.h"
#include "messagedraw.h"
#include "spritemessage.h"
#include "panacea_alloc.h"

namespace dk
{
    class LEVEL_UP
    {
    public:
        static void draw(char* levelUp);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _fetchVtable = ResolveRelativeAddress<char*>("\x40\x53\x57\x48\x83\xEC\x28\x48\x8B\x05", "xxxxxxxxxx", 0x56);

                auto _drawFunction = (uint64_t)draw;

                auto _drawOriginalDEF = *reinterpret_cast<char**>(_fetchVtable + 0x10);
                auto _drawOriginalFRM = *reinterpret_cast<char**>(_fetchVtable + 0x40);
                auto _drawOriginalSMN = *reinterpret_cast<char**>(_fetchVtable + 0x70);

                memset(_drawOriginalDEF, 0x90, 0xBA);
                memset(_drawOriginalFRM, 0x90, 0xBA);
                memset(_drawOriginalSMN, 0x90, 0xBA);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginalDEF, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginalFRM, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginalSMN, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}
