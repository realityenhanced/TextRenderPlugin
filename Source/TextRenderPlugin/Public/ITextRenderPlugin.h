// Copyright 2015 Nishant Naveen. All Rights Reserved.
#pragma once
#include "ModuleManager.h"

class ITextRenderPlugin : public IModuleInterface
{

public:
	static inline ITextRenderPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<ITextRenderPlugin>("TextRenderPlugin");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("TextRenderPlugin");
	}
};

