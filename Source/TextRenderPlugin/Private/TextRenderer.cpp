// Copyright 2015 Nishant Naveen. All Rights Reserved.
#include "TextRenderPluginPrivatePCH.h"
#include "TextRenderer.h"

ATextRenderer::ATextRenderer(const FObjectInitializer& ObjectInitializer)
	: Super( ObjectInitializer )
{
	// Create the Body of the Actor and set it as the root component
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	// Get the assets
	# define TR_ASSETS_FOLDER TEXT("/TextRenderPlugin") // used by engine plugin
	TextMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TR_ASSETS_FOLDER TEXT("/TR_TextMaterialInstance")).Object;

	// Default Params
	RenderTargetWidth = 512;
	RenderTargetHeight = 512;
}

// Called when the game starts or when spawned
void ATextRenderer::BeginPlay()
{
	Super::BeginPlay();

	// Setup the RenderTarget on which the text will be drawn.
	RenderTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(GetWorld(), UCanvasRenderTarget2D::StaticClass(), RenderTargetWidth, RenderTargetHeight);
	if (RenderTarget != nullptr)
	{
		RenderTarget->ClearColor = BackgroundColor;
		RenderTarget->UpdateResource();
		RenderTarget->OnCanvasRenderTargetUpdate.AddDynamic(this, &ATextRenderer::OnReceiveUpdate);
	}

	// Create a dynamic material instance and set up the texture it will use
	TextMaterialInstance = Body->CreateDynamicMaterialInstance(0, TextMaterial);
	if (TextMaterialInstance != nullptr)
	{
		TextMaterialInstance->SetTextureParameterValue(FName("Texture"), RenderTarget);
	}

	// Enable the Input Preprocessor
	KeyboardInputProcessor = TSharedPtr<IInputProcessor>(new FKeyboardInputProcessor());
	static_cast<FKeyboardInputProcessor*>(KeyboardInputProcessor.Get())->SetClient(this);
	FSlateApplication::Get().SetInputPreProcessor(true, KeyboardInputProcessor);
}

// Called when the game ends or when actor is destroyed
void ATextRenderer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Disable the Input Preprocessor
	static_cast<FKeyboardInputProcessor*>(KeyboardInputProcessor.Get())->SetClient(nullptr);
	FSlateApplication::Get().SetInputPreProcessor(false, nullptr);

	Super::EndPlay(EndPlayReason);
}

// Delegate called when the render target needs to be updated
// Called each time a key press is detected to render the text
void ATextRenderer::OnReceiveUpdate(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (Canvas != nullptr && Font != nullptr)
	{
		RenderTarget->ClearColor = BackgroundColor;

		FVector2D pos(0.0f, 0.0f);
		FCanvasTextItem textItem(pos, FText::FromString(EnteredText), Font, TextColor);
		textItem.EnableShadow(ShadowColor, ShadowOffset);
		textItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
		Canvas->DrawItem(textItem);
	}
}

// On Key Press
void ATextRenderer::UpdateText(const FKeyEvent& KeyEvent)
{
	// TODO: Add normal text editor functionality.
	// For now append the char that was entered.
	uint32 character = KeyEvent.GetCharacter();
	if (character != 0)
	{
		EnteredText = EnteredText.AppendChar(character);
		RenderTarget->UpdateResource();
	}
}