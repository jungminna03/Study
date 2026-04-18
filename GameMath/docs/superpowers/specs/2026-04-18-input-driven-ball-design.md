# 입력으로 움직이는 공 — Design

**Date:** 2026-04-18
**Topic:** Input-driven ball on a centered grid

## Goal

화살표 키로 부드럽게 움직이는 공을 화면에 표시한다. 좌표 원점 `(0, 0)`을 화면 중앙으로 두고, Y축은 수학 관례(위쪽이 +Y)로 잡아 이후 게임 수학 학습(벡터·변환 등)의 기반 좌표계로 사용한다.

## Coordinate System

두 좌표계를 명확히 분리한다.

- **논리 좌표 (logical):** 화면 중앙이 `(0, 0)`. X는 오른쪽이 +, Y는 **위쪽이 +**. 게임 로직과 위치 상태는 모두 이 좌표로 다룬다.
- **씬 좌표 (scene, Siv3D 픽셀):** 좌상단이 `(0, 0)`, Y는 아래쪽이 +. Siv3D API로 그릴 때만 사용한다.
- **변환:** `scene = { center.x + logical.x, center.y - logical.y }` (`center = Scene::Center()`). 이 변환은 단일 헬퍼(예: `toScene(Vec2)`)에 두고, 모든 그리기는 그 헬퍼를 통한다. 양방향이 필요해지면 그때 `toLogical`을 추가한다.

거리·반지름·속도는 픽셀 단위 그대로 사용한다 (논리 1 = 픽셀 1, Y 방향만 부호 반대).

## State

- `Vec2 playerPos{ 0, 0 }` — 논리 좌표. 시작값이 곧 화면 중앙.
- `constexpr double playerRadius = 15.0` — 픽셀.
- `constexpr double moveSpeed = 200.0` — 픽셀/초.

## Per-frame Behavior

**update()**

```
dx = KeyRight.pressed() - KeyLeft.pressed()   // -1, 0, +1
dy = KeyUp.pressed()    - KeyDown.pressed()   // -1, 0, +1 (위가 +)
playerPos.x += dx * moveSpeed * Scene::DeltaTime()
playerPos.y += dy * moveSpeed * Scene::DeltaTime()
```

**draw()**

1. `RenderGrid()` (기존 그대로 — 빨강/초록 축은 이미 화면 중앙을 지나가므로 새 좌표계와 일치)
2. `Circle{ toScene(playerPos), playerRadius }.draw(Palette::White)`

경계 검사 없음. 공이 그리드 밖으로 나가도 그대로 둔다.

## Cleanup of Existing Code

`GameMath/Main.cpp`에 남아 있는 미완성/깨진 부분 정리:

- `Circle playerPos;` → `Vec2 playerPos{ 0, 0 };`
- `const int moveSpeed = 100.f;` → `constexpr double moveSpeed = 200.0;` (`int`인데 `100.f`로 초기화하던 것 + 단위·타입 정합)
- `Line { playerPos.center * 500f, }` (구문 오류, 미완성) → 삭제하고 위의 `Circle::draw` 한 줄로 대체.
- `update()`의 `KeyUp - KeyDown` 부호 — Y-up 논리 좌표계라 **현재 코드 그대로 유지**(위 키 = +Y). 그리기 시점의 `toScene`에서 부호가 뒤집힌다.

## Out of Scope

- 그리드 단위(units) 기반 좌표 전환 — 픽셀 유지.
- 가속도/관성, 충돌, 경계 클램프/랩어라운드, WASD/마우스 입력.
- 멀티 파일 분리 — 단일 `Main.cpp` 유지.
- `toLogical` 역변환 (필요해지는 시점에 추가).
