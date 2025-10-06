/**
 * @file FScreenshotFeature.cpp
 * @brief Coffee Toolbar의 스크린샷 캡처 헬퍼 기능을 구현합니다.
 */
#include "Screenshot/FScreenshotFeature.h"
#include "Common/FCommon.h" // For GetActiveTargetWorld
#include "Framework/MultiBox/MultiBoxBuilder.h" // For FMenuBuilder
#include "LevelEditor.h" // For FLevelEditorModule
#include "IAssetViewport.h" // For IAssetViewport
#include "Engine/Engine.h" // For GEngine
#include "UnrealEdGlobals.h" // For GEditor
#include "Misc/Paths.h" // For FPaths
#include "HAL/FileManager.h" // For IFileManager
#include "HAL/IConsoleManager.h" // For IConsoleVariable
#include "HAL/PlatformProcess.h" // For FPlatformProcess
#include "Styling/AppStyle.h" // For FAppStyle
#include "Styling/SlateIcon.h" // For FSlateIcon

/** @brief 스크린샷 기능의 기본 생성자입니다. */
FScreenshotFeature::FScreenshotFeature()
{
}

/** @brief 스크린샷 옵션을 제공하는 메뉴 위젯을 구성합니다. */
TSharedRef<SWidget> FScreenshotFeature::GenerateScreenshotMenu()
{
    FMenuBuilder MenuBuilder(true, nullptr);

    MenuBuilder.AddMenuEntry(
        NSLOCTEXT("CoffeeToolbar", "Screenshot_QuickPreview", "개발 중 빠른 참고 (1x)"),
        NSLOCTEXT("CoffeeToolbar", "Screenshot_QuickPreview_Tooltip", "현재 활성 뷰포트를 1배 해상도로 빠르게 캡쳐합니다."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FScreenshotFeature::OnCaptureQuickPreview))
    );

    MenuBuilder.AddMenuEntry(
        NSLOCTEXT("CoffeeToolbar", "Screenshot_Standard", "보통 (2x)"),
        NSLOCTEXT("CoffeeToolbar", "Screenshot_Standard_Tooltip", "현재 활성 뷰포트를 2배 배율로 캡쳐합니다."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FScreenshotFeature::OnCaptureStandard))
    );

    MenuBuilder.AddMenuEntry(
        NSLOCTEXT("CoffeeToolbar", "Screenshot_High", "고해상도 (4x)"),
        NSLOCTEXT("CoffeeToolbar", "Screenshot_High_Tooltip", "현재 활성 뷰포트를 4배 배율로 캡쳐합니다."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FScreenshotFeature::OnCaptureHighResolution))
    );

    MenuBuilder.AddMenuEntry(
        NSLOCTEXT("CoffeeToolbar", "Screenshot_Ultra", "울트라 (8x)"),
        NSLOCTEXT("CoffeeToolbar", "Screenshot_Ultra_Tooltip", "현재 활성 뷰포트를 8배 배율로 캡쳐합니다."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FScreenshotFeature::OnCaptureUltra))
    );

    MenuBuilder.AddMenuSeparator();

    MenuBuilder.AddMenuEntry(
        NSLOCTEXT("CoffeeToolbar", "Screenshot_OpenFolder", "캡쳐 폴더 열기"),
        NSLOCTEXT("CoffeeToolbar", "Screenshot_OpenFolder_Tooltip", "스크린샷이 저장된 캡쳐 폴더를 엽니다."),
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.FolderOpen"),
        FUIAction(FExecuteAction::CreateRaw(this, &FScreenshotFeature::OnOpenScreenShotDir))
    );

    return MenuBuilder.MakeWidget();
}

/** @brief 빠른 참고용 스크린샷을 촬영합니다. */
void FScreenshotFeature::OnCaptureQuickPreview()
{
    CaptureActiveViewport(1);
}

/** @brief 표준 배율 스크린샷을 촬영합니다. */
void FScreenshotFeature::OnCaptureStandard()
{
    CaptureActiveViewport(2);
}

/** @brief 고해상도 스크린샷을 촬영합니다. */
void FScreenshotFeature::OnCaptureHighResolution()
{
    CaptureActiveViewport(4);
}

/** @brief 울트라 고해상도 스크린샷을 촬영합니다. */
void FScreenshotFeature::OnCaptureUltra()
{
    CaptureActiveViewport(8);
}

/** @brief 지정된 배율로 활성 뷰포트에 고해상도 캡처를 요청합니다. */
void FScreenshotFeature::CaptureActiveViewport(int32 ResolutionMultiplier)
{
    if (ResolutionMultiplier <= 0)
    {
        ResolutionMultiplier = 1;
    }

    if (IConsoleVariable* ResolutionCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.HighResScreenshot.ResolutionMultiplier")))
    {
        ResolutionCVar->Set(ResolutionMultiplier);
    }

    if (GEngine && GEditor &&
        GEditor->PlayWorld &&
        GEngine->GameViewport &&
        GEngine->GameViewport->Viewport)
    {
        FScreenshotRequest::RequestScreenshot(true);
        GEngine->GameViewport->Viewport->TakeHighResScreenShot();
        return;
    }

    if (FLevelEditorModule* LevelEditorModule = FModuleManager::GetModulePtr<FLevelEditorModule>("LevelEditor"))
    {
        if (TSharedPtr<IAssetViewport> AssetViewport = LevelEditorModule->GetFirstActiveViewport())
        {
            FEditorViewportClient& ViewportClient = AssetViewport->GetAssetViewportClient();
            ViewportClient.TakeHighResScreenShot();
            return;
        }
    }

    if (UWorld* World = FCommon::GetActiveTargetWorld())
    {
        const FString Command = FString::Printf(TEXT("HighResShot %d"), ResolutionMultiplier);
        GEditor->Exec(World, *Command);
    }
}

/** @brief 촬영된 스크린샷이 저장된 디렉터리를 엽니다. */
void FScreenshotFeature::OnOpenScreenShotDir()
{
    FString Dir = FPaths::ScreenShotDir();
    FString AbsoluteDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*Dir);
    IFileManager::Get().MakeDirectory(*AbsoluteDir, true);
    FPlatformProcess::ExploreFolder(*AbsoluteDir);
}