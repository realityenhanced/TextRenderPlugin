// Copyright 2015 Nishant Naveen. All Rights Reserved.
#pragma once
#include "TextRenderer.h"
#include "Framework/Application/IInputProcessor.h"

/**
* Keyboard Input Preprocessor
*/
class FKeyboardInputProcessor : public IInputProcessor
{
private:
	ATextRenderer* TextRenderer;
public:
	// IInputProcessor Interface
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor);
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);
	virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);
	virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent);

	//
	void SetClient(ATextRenderer* pClient);
};


