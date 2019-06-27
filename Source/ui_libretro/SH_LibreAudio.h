#pragma once

#include "tools/PsfPlayer/Source/SoundHandler.h"

class CSH_LibreAudio : public CSoundHandler
{
public:
	CSH_LibreAudio() = default;

	static CSoundHandler* HandlerFactory();

	void Reset() override;
	void Write(int16*, unsigned int, unsigned int) override;
	bool HasFreeBuffers() override;
	void RecycleBuffers() override;
};
