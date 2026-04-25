#pragma once

#include <cstdint>

#include "obj2d.h"
#include "sequence.h"
#include "memorymgr.h"
#include "panacea_alloc.h"

namespace dk
{
    class Sprite
    {
    public:
        static void(*setNum)(char* Sprite, int num);
        static void(*setPos)(char* Sprite, int x, int y);
        static void(*update)(char* Sprite);
        static void(*initSqd)(char* Sprite, char* sqd, char* image, int num);

        static void _Sprite(char* self);

        static void draw(char* Sprite);
        static void initWork(char* Sprite);
        static void create(char* Sprite, int priority, char* seqd, char* image, int num, int group, int offset16x9);

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
                auto _createFunction = (uint64_t)create;

                auto _drawOriginal = SignatureScan<char*>("\x40\x53\x48\x83\xEC\x30\x8B\x41\x10\x48\x8B\xD9\xC1\xE8\x0B\xA8\x01", "xxxxxxxxxxxxxxxxx");
                auto _createOriginal = SignatureScan<char*>("\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x41\x56\x48\x83\xEC\x20\x4D\x8B\xF0\x49\x8B\xE9", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

                memset(_drawOriginal, 0x90, 0x1FD);
                memset(_createOriginal, 0x90, 0x106);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_drawFunction, 0x08);
                memcpy(_drawOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_createFunction, 0x08);
                memcpy(_createOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}