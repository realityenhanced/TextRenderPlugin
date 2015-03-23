// Copyright 2015 Nishant Naveen. All Rights Reserved.
#include "TextRenderPluginPrivatePCH.h"
#include "TextRenderer.h"

class FTextRenderPlugin : public ITextRenderPlugin
{
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FTextRenderPlugin, TextRenderPlugin )

void FTextRenderPlugin::StartupModule()
{	
}

void FTextRenderPlugin::ShutdownModule()
{
}



