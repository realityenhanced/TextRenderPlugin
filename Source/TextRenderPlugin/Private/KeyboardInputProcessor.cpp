#include "TextRenderPluginPrivatePCH.h"

void FKeyboardInputProcessor::SetClient(ATextRenderer* pClient)
{
	TextRenderer = pClient;
}

// IInputProcessor Interface 
void FKeyboardInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{

}

bool FKeyboardInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	TextRenderer->UpdateText(InKeyEvent);
	return false; // Allow the event to bubble up
}

bool FKeyboardInputProcessor::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	return false; // Allow the event to bubble up
}

bool FKeyboardInputProcessor::HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent)
{
	return false; // Allow the event to bubble up
}