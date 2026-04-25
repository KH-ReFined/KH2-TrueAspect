#include "sound.h"

void (*SOUND::PlaySFX)(uint32_t) = SignatureScan<void(*)(uint32_t)>("\x48\x83\xEC\x00\x44\x8B\xC2\xC7\x44\x24\x20\x00\x00\x00\x00", "xxx?xxxxxxx????");