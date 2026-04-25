#pragma once

#include "memorymgr.h"

namespace YS
{
    class MESSAGEDRAW
    {
        public:
        static void(*_MESSAGEDRAW)(char* MessageDraw, int type, char* message, int size, int align);
        static void(*set_line_space)(char* MessageDraw, int space);
        static void(*draw)(char* MessageDraw, int x, int y, uint32_t color);
    };
}