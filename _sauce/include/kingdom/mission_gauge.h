#pragma once

#include "sequence.h"
#include "memorymgr.h"
#include "panacea_alloc.h"

namespace dk 
{
    class MISSION_GAUGE {
        public:
        static void updateGauge(char* missionGauge);

        struct staticInitializer
        {
            staticInitializer()
            {
                vector<uint8_t> _absoluteInstructionJMP =
                {
                    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };

                auto _updateFunction = (uint64_t)updateGauge;
                auto _updateOriginal = SignatureScan<char*>("\x40\x53\x48\x83\xEC\x30\x48\x8B\xD9\x0F\x29\x74\x24\x20\x48\x81\xC1\x08\x09\x00", "xxxxxxxxxxxxxxxxxxxx");

                memset(_updateOriginal, 0x90, 0x95);

                memcpy(_absoluteInstructionJMP.data() + 0x06, &_updateFunction, 0x08);
                memcpy(_updateOriginal, _absoluteInstructionJMP.data(), _absoluteInstructionJMP.size());
            }
        };

        static staticInitializer initialize;
    };
}