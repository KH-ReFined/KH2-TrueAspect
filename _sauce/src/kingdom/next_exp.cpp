#include "next_exp.h"

void dk::NEXT_EXP::draw(char* nextExp)
{
	auto _fetchMemory = YS::PANACEA_ALLOC::Get("ASPECT_INFORMATION");
	auto _offsetValue = 85;

	if (_fetchMemory)
		memcpy(&_offsetValue, _fetchMemory, 0x04);

	auto _applyAspect = (_offsetValue * -1) + 85;

	auto _activeX = YI::SEQUENCE::GetActiveX(nextExp + 0x0058) + *reinterpret_cast<int*>(nextExp + 0x0200);
	auto _activeY = YI::SEQUENCE::GetActiveY(nextExp + 0x0058) + *reinterpret_cast<int*>(nextExp + 0x0204);

	auto _positionX = *reinterpret_cast<int*>(nextExp + 0x01F8) + _activeX;
	auto _positionY = *reinterpret_cast<int*>(nextExp + 0x01FC) + _activeY;

	auto _articleCount = *reinterpret_cast<int*>(nextExp + 0x0DB0);

	for (int i = 0; i < _articleCount; i++)
	{
		auto _fetchSqd = nextExp + 0x03C0 + 0x01A0 * i;
		auto _fetchOffsetX = nextExp + 0x0D90 + 0x0004 * i;

		*reinterpret_cast<int*>(_fetchSqd - 0x04) = *reinterpret_cast<int*>(_fetchOffsetX) + _positionX + _applyAspect;
		*reinterpret_cast<int*>(_fetchSqd) = _positionY;

		YI::SEQUENCE::Draw(_fetchSqd - 0x0190);
	}
}

dk::NEXT_EXP::staticInitializer initializer;