#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>

#include "memorymgr.h"
#include "panacea_alloc.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

vector<char> INSTRUCTION_LIMIT_ASPECT;

uint32_t POSITIVE_ASPECT_OFFSET = 0x55;
uint32_t NEGATIVE_ASPECT_OFFSET = 0xFFFFFFAB;

char** RADAR_STRUCT = ResolveRelativeAddress<char**>("\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x57\x41\x54\x48\x83", "xxxxxxxxxxxxxxxx", 0xD4);

char* VIEWPORT_LIMIT = SignatureScan<char*>("\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\xE8\x00\x00\x00\x00\xF3\x0F\x10\x15\x00\x00\x00\x00\x48\x8B\xC8\xF3\x0F\x10\x25\x00\x00\x00\x00\xF3\x0F\x5D\x50\x28", "xxxxxxxxxx????xxxx????xxxxxxx????xxxxx");
char* VIEWPORT3D_ADDR = ResolveRelativeAddress<char*>("\x48\x8B\xC4\x57\x41\x56\x41\x57\x48\x81\xEC\x50\x01\x00\x00\x48\xC7\x44\x24\x20\xFE\xFF\xFF\xFF\x48\x89\x58\x10\x48\x89\x68\x18\x48\x89\x70\x20\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\x40\x01\x00\x00\x48\x8B\xE9\x33\xD2\x41\xB8\x00\x01\x00\x00\x48\x8D\x4C\x24\x30\xE8\x00\x00\x00\x00\x45\x33\xFF", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx", 0x311);

extern "C"
{
    __declspec(dllexport) void OnInit(wchar_t* mod_path)
    {
        YS::PANACEA_ALLOC::Allocate("ASPECT_INFORMATION", 0x08);

        // Prevent the game from adjusting the aspect automatically.

        auto _fetchAdjustment = SignatureScan<char*>("\x48\x83\xEC\x28\x0F\x10\x41\x48\x4C\x8B\xC9\x4C\x8B\xD2\xF3\x0F\x10\x25\x00\x00\x00\x00\x0F\x57\xED\x0F\x11\x02\x41\x0F\x10\x00\x49\x8B\x41\x40", "xxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxx");

        memset(_fetchAdjustment + 0xF6, 0x90, 0x06);
        memset(_fetchAdjustment + 0x101, 0x90, 0x06);

        // Kill the enforcer in dk::MISSION_GAUGE::update so I don't want to kill myself.

        auto _fetchMissionUpdate = SignatureScan<char*>("\x48\x89\x5C\x24\x18\x57\x48\x83\xEC\x20\x48\x8B\xF9\xE8", "xxxxxxxxxxxxxx");
        memset(_fetchMissionUpdate + 0x119, 0xEB, 0x01);

        // Fetch all functions that handle fade-in and fade-outs in any way within the 2dFade rectangle.

        auto _fetchAllFade = MultiSignatureScan("\x41\xB8\xFF\xFF\xFF\xFF\x48\x8D\x0D\x00\x00\x00\x00\x0F\xB7\xD3\x66\xF7\xD2\xE8\x00\x00\x00\x00\xB8\x01\x01\x00\x00", "xxxxxxxxx????xxxxxxx????xxxxx");

        for (auto _function : _fetchAllFade)
        {
            uint32_t _fadeValue = 0x500;
            vector<uint8_t> _replaceFade{ 0xBA, 0x00, 0xFF, 0x00, 0x00 };

            memcpy(_function + 0x0D, "\x90\x90\x90\x90\x90\x90", 0x06);
            memcpy(_function + 0x0D, _replaceFade.data(), 0x05);

            memcpy(_function + 0x19, &_fadeValue, 0x04);
        }

        // Disables culling. Causes some side effects that I don't believe anyone will notice.

        auto _fetchCulling3D = SignatureScan<char*>("\x48\x8B\xC4\x48\x89\x58\x18\x48\x89\x70\x20\x55\x57\x41\x54\x41", "xxxxxxxxxxxxxxxx");

        memset(_fetchCulling3D + 0x11D, 0xEB, 0x01);
        memset(_fetchCulling3D + 0x12B, 0xEB, 0x01);
        memset(_fetchCulling3D + 0x133, 0xEB, 0x01);
        memset(_fetchCulling3D + 0x141, 0xEB, 0x01);
        memset(_fetchCulling3D + 0x149, 0xEB, 0x01);
        memset(_fetchCulling3D + 0x152, 0xEB, 0x01);

        auto _fetchCulling2D = SignatureScan<char*>("\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xFA\xE8", "xxxxxxxxxxxxxxxxxxx");

        memset(_fetchCulling2D + 0x06C, 0x00, 0x01);
    }

    __declspec(dllexport) void OnFrame()
    {
        float _resolutionHorizontal = *reinterpret_cast<float*>(VIEWPORT3D_ADDR + 0x10);
        float _resolutionVertical = *reinterpret_cast<float*>(VIEWPORT3D_ADDR + 0x14);

        float _commonDiv = 0x00F;

        if (_resolutionHorizontal != 0x00 && _resolutionVertical != 0x00)
        {
            POSITIVE_ASPECT_OFFSET = 0x55;
            NEGATIVE_ASPECT_OFFSET = 0xFFFFFFAB;

            uint16_t _offsetInformation = 0xFFFF;

            auto _tempWidth = _resolutionHorizontal;
            auto _tempHeight = _resolutionVertical;

            while (_tempWidth != 0 && _tempHeight != 0)
            {
                if (_tempWidth > _tempHeight)
                    _tempWidth = fmodf(_tempWidth, _tempHeight);

                else
                    _tempHeight = fmodf(_tempHeight, _tempWidth);
            }

            _commonDiv = _tempWidth == 0 ? _tempHeight : _tempWidth;

            auto _ratioNum = _resolutionHorizontal / _commonDiv;
            auto _checkRatio = _resolutionVertical / _commonDiv;

            if (_checkRatio != 9)
            {
                auto _commonMulp = 9 / _checkRatio;
                _ratioNum = _ratioNum * _commonMulp;
            }

            auto _ratioMultiplier = 0.0625F * _ratioNum;

            memcpy(VIEWPORT3D_ADDR + 0x20, &_ratioMultiplier, 0x04);

            auto _heightFactor = _resolutionVertical / 1080;
            auto _widthCalc = floorf(_resolutionHorizontal / _heightFactor);

            if (INSTRUCTION_LIMIT_ASPECT.size() == 0x00)
            {
                INSTRUCTION_LIMIT_ASPECT.resize(0x09);
                memcpy(INSTRUCTION_LIMIT_ASPECT.data(), VIEWPORT_LIMIT + 0x98, 0x09);
            }

            auto _zoomMultiplier = 16 / _ratioNum;

            if (_ratioMultiplier < 1)
            {
                memset(VIEWPORT_LIMIT + 0x98, 0x90, 0x09);
                memcpy(VIEWPORT3D_ADDR + 0x28, &_zoomMultiplier, 0x04);
            }

            else
            {
                memcpy(VIEWPORT_LIMIT + 0x98, INSTRUCTION_LIMIT_ASPECT.data(), 0x09);
                memcpy(VIEWPORT3D_ADDR + 0x28, "\x00\x00\x80\x3F", 0x04);
            }

            POSITIVE_ASPECT_OFFSET = ceilf(0.177F * (_widthCalc - 1440));
            NEGATIVE_ASPECT_OFFSET = POSITIVE_ASPECT_OFFSET * -1;

            auto _fetchMemory = YS::PANACEA_ALLOC::Get("ASPECT_INFORMATION");

            if (_fetchMemory)
            {
                memcpy(_fetchMemory, &POSITIVE_ASPECT_OFFSET, 0x04);
                memcpy(_fetchMemory + 0x04, &NEGATIVE_ASPECT_OFFSET, 0x04);
            }

            if (*RADAR_STRUCT)
            {
                *reinterpret_cast<int*>(*RADAR_STRUCT + 0xBBC) = POSITIVE_ASPECT_OFFSET;
                *reinterpret_cast<int*>(*RADAR_STRUCT + 0xBE0) = POSITIVE_ASPECT_OFFSET;
            }
        }
    }
}