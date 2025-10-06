# Coffee Toolbar

**Version: 1.0**

`Coffee Toolbar`는 언리얼 엔진 에디터의 개발 편의성을 향상시키기 위해 제작된 유틸리티 툴바 플러그인입니다. 자주 사용하는 기능들을 원클릭으로 실행하여 반복적인 작업을 줄이고 개발 속도를 높이는 것을 목표로 합니다.

## 주요 기능 (Features)

*   **커스텀 콘솔 명령어 실행**: 설정 파일에 미리 정의된 다수의 콘솔 명령어들을 버튼 하나로 실행할 수 있습니다.
*   **레벨 관련 기능**: 현재 레벨의 모든 액터를 빌드하거나, 라이팅을 빌드하는 등 레벨 관리에 유용한 기능들을 제공합니다.
*   **고해상도 스크린샷**: 지정된 배율(예: 2x, 4x)로 고해상도 스크린샷을 간편하게 촬영하고 저장 폴더를 바로 열 수 있습니다.
*   **설정 기반 확장성**: `.ini` 파일을 통해 툴바에 표시될 기능과 순서를 사용자가 직접 커스터마이징할 수 있습니다.

## 설치 방법 (Installation)

### 1. 프로젝트에 설치

1.  프로젝트 폴더 내에 `Plugins` 폴더가 없다면 생성합니다.
2.  `CoffeeToolbar` 폴더를 `Plugins` 폴더 안으로 복사합니다.
3.  프로젝트를 재시작한 후, `Edit > Plugins` 메뉴에서 `CoffeeToolbar`를 찾아 활성화합니다.

**경로 예시**: `[YourProjectDirectory]/Plugins/CoffeeToolbar`

### 2. 엔진에 설치

1.  언리얼 엔진 설치 경로의 `Engine/Plugins` 폴더로 이동합니다.
2.  `CoffeeToolbar` 폴더를 `Engine/Plugins` 폴더 안으로 복사합니다.
3.  엔진을 재시작한 후, `Edit > Plugins` 메뉴에서 `CoffeeToolbar`를 찾아 활성화합니다.

**경로 예시**: `C:/Program Files/Epic Games/UE_5.X/Engine/Plugins/CoffeeToolbar`

## 사용법 (How to Use)

1.  플러그인이 활성화되면 에디터 상단 메인 툴바에 새로운 **커피 아이콘**이 나타납니다.
2.  툴바 아이콘을 클릭하면 등록된 기능 버튼들이 드롭다운 메뉴 형식으로 표시됩니다.
3.  원하는 기능의 버튼을 클릭하여 즉시 실행합니다.

## 설정 (Configuration)

`Project Settings > Plugins > Coffee Toolbar` 메뉴를 통해 플러그인의 동작을 상세하게 설정할 수 있습니다.

*   **콘솔 명령어 등록**: 툴바를 통해 실행할 커스텀 콘솔 명령어 목록을 추가하거나 수정할 수 있습니다.
*   **스크린샷 배율 설정**: 고해상도 스크린샷 촬영 시 사용될 배율을 지정합니다.
*   **툴바 기능 활성화/비활성화**: 툴바에 표시할 개별 기능들을 선택적으로 켜고 끌 수 있습니다.

설정된 내용은 프로젝트의 `Config/DefaultEditorPerProjectUserSettings.ini` 파일에 저장됩니다.

## 라이선스 (License)

본 플러그인은 MIT 라이선스 하에 배포됩니다. 자세한 내용은 `LICENSE` 파일을 참고하십시오.

## 제작자 (Author)

-   dopple