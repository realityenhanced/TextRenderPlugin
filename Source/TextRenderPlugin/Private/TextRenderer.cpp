// Copyright 2015 Nishant Naveen. All Rights Reserved.
#include "TextRenderPluginPrivatePCH.h"
#include "TextRenderer.h"

ATextRenderer::ATextRenderer(const FObjectInitializer& ObjectInitializer)
	: Super( ObjectInitializer )
{
	// Create the Body of the Actor and set it as the root component
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

}

// Called when the game starts or when spawned
void ATextRenderer::BeginPlay()
{
	Super::BeginPlay();

	// Setup the RenderTarget on which the text will be drawn.
	RenderTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(GetWorld(), UCanvasRenderTarget2D::StaticClass(), RenderTargetWidth, RenderTargetHeight);
	if (RenderTarget != nullptr)
	{
		RenderTarget->UpdateResource();
		RenderTarget->OnCanvasRenderTargetUpdate.AddDynamic(this, &ATextRenderer::OnReceiveUpdate);
	}

	// Create a dynamic material instance and set up the texture it will use
	// TODO: Create a parameterized material that accepts a texture
	
	if (MaterialInstance != nullptr)
	{
		MaterialInstance->SetTextureParameterValue(FName("Texture"), RenderTarget);
	}

	// TODO: Remove me
	EnteredText = TEXT("HELLO WORLD");
}

// Called when the game ends or when actor is destroyed
void ATextRenderer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Delegate called when the render target needs to be updated
// Called each time a key press is detected to render the text
void ATextRenderer::OnReceiveUpdate(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (Canvas != nullptr && Font != nullptr)
	{
		FVector2D pos(0.0f, 0.0f);
		FCanvasTextItem textItem(pos, FText::FromString(EnteredText), Font, TextColor);
		textItem.EnableShadow(ShadowColor, ShadowOffset);
		textItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
		Canvas->DrawItem(textItem);
	}
}