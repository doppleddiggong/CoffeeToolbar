// Copyright (c) 2025 Doppleddiggong. All rights reserved. Unauthorized copying, modification, or distribution of this file, via any medium is strictly prohibited. Proprietary and confidential.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UCoffeeToolbarSettings.generated.h"

USTRUCT(BlueprintType)
struct FCoffeeToolbarButtonInfo
{
	GENERATED_BODY()

	/** 각 버튼을 구별하는 고유한 이름입니다. */
	UPROPERTY(EditAnywhere, Category="Button Info")
	FName Id;

	/** 툴바에 표시될 버튼의 이름입니다. */
	UPROPERTY(EditAnywhere, Category="Button Info")
	FString Label;

	/** 버튼에 마우스를 올렸을 때 나타나는 설명입니다. */
	UPROPERTY(EditAnywhere, Category="Button Info")
	FString Tooltip;

	/** 버튼을 클릭했을 때 실행될 콘솔 명령어입니다. */	UPROPERTY(EditAnywhere, Category="Button Info")
	FString Command;

	/** 
	 * 버튼에 표시될 아이콘입니다. 
	 * - 에디터 내장 아이콘: `EditorStyle.GraphEditor.Play` 와 같이 `.` 이 포함된 이름을 사용합니다.
	 * - 사용자 정의 아이콘: `Plugins/CoffeeToolbar/Resources/` 폴더에 있는 이미지 파일의 이름(확장자 제외)을 사용합니다. (예: `MyIcon`)
	 */
	UPROPERTY(EditAnywhere, Category="Button Info")
	FName Icon;

	/** true로 설정하면 껐다 켰다 할 수 있는 토글 버튼이 됩니다. */
	UPROPERTY(EditAnywhere, Category="Button Info")
	bool bIsToggleButton = false;
};

UCLASS(Config=CoffeeToolbar, DefaultConfig, meta=(DisplayName="CoffeeToolbar"))
class COFFEETOOLBAR_API UCoffeeToolbarSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UCoffeeToolbarSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
	virtual FName GetSectionName()  const override { return TEXT("Level Selector"); }

	static TArray<FName> GetSearchRoots(const bool bFallbackToGame = true);

	
	UPROPERTY(EditAnywhere, Config, Category="Search")
	TArray<FDirectoryPath> ExtraSearchPaths;

	UPROPERTY(EditAnywhere, Config, Category="Toolbar")
	TArray<FCoffeeToolbarButtonInfo> ToolbarButtons;
};
