// Copyright 2015 Nishant Naveen. All Rights Reserved.
#pragma once
#include "TextRenderer.generated.h"

/**
 * Renders text based on keypresses
 */
UCLASS()
class ATextRenderer : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	/**
	* Static Mesh component that the text rendering block will be a child of.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Properties")
	class UStaticMeshComponent* Body;

	/**
	* The Font to be used for rendering text. Make sure it on type = Offline.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	class UFont* Font;

	/**
	* The width of the rendertarget on which the text will be drawn
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	float RenderTargetWidth;

	/**
	* The height of the rendertarget on which the text will be drawn
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	float RenderTargetHeight;

	/**
	* The color of the text
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	FLinearColor TextColor;

	/**
	* The background color
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	FLinearColor BackgroundColor;

	/**
	* The color of the shadow on the text
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	FLinearColor ShadowColor;

	/**
	* The offset of the shadow on the text
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Properties")
	FVector2D ShadowOffset;
public:
	// Delegate to handle text updates
	UFUNCTION()
	void OnReceiveUpdate(class UCanvas* Canvas, int32 Width, int32 Height);

	// Called on each key press from the KeyboardInputProcessor
	void UpdateText(const FKeyEvent& KeyEvent);

private: // Member variables
	class UCanvasRenderTarget2D* RenderTarget;
	class UMaterialInterface* TextMaterial;
	class UMaterialInstanceDynamic* TextMaterialInstance;
	FString EnteredText;
	TSharedPtr<IInputProcessor> KeyboardInputProcessor;

private: // Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or when actor is destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};


