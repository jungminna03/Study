# CLAUDE.md

이 저장소는 LeetCode 알고리즘 풀이(C++)와 GameMath(Siv3D) 학습 기록이다.
주 작업은 **알고리즘 문제 셋업 → 풀이 → README 반영 → push** 흐름이다.

---

## 문제 셋업 (문제 본문만 붙여넣으면 아래대로 실행)

사용자가 LeetCode 문제 본문을 붙여넣으면, "어떻게 하라"는 지시가 없어도 다음을 수행한다.

1. **난이도별 폴더에 `.cpp` 생성**
   - Easy → `Algorithm/Easy/`, Medium → `Algorithm/Medium/`
   - 파일명: 문제 제목을 그대로 쓰되 공백은 `_`, 특수문자 제거
     (예: `Binary Tree Level Order Traversal` → `Binary_Tree_Level_Order_Traversal.cpp`)
   - CMake는 `Easy/*.cpp`, `Medium/*.cpp`를 GLOB로 자동 인식하므로 별도 등록 불필요.

2. **파일 양식** — 기존 파일(예: `Algorithm/Easy/Maximum_Depth_of_Binary_Tree.cpp`) 스타일을 그대로 따른다.
   - 상단 `//` 주석 3줄 (`Created by jungk on 26. M. D..` 형식, 날짜는 오늘 날짜)
   - 필요한 `#include`, `using namespace std;`
   - 트리/리스트 문제면 LeetCode 원본 그대로의 `struct TreeNode` / `ListNode` 정의 포함
   - `class Solution { public: ... };` — **함수 본문은 비워두고** 시그니처와 반환용 변수 선언만 남긴다.
     함수 위에는 무엇을 하는 함수인지 **한국어 주석**으로 요약.
   - `int main()`:
     - 문제의 Example들을 입력 트리/배열로 구성
     - **`auto res = s.함수(...);` 형태로 호출** — 사용자가 `res` / `res2` / `res3` 라인에 중단점을 걸어 반환값을 확인한다. 각 줄 끝에 `// expected: ...` 주석.
     - `return 0;`

3. 셋업만 하고 **풀이는 사용자가 직접 작성**한다. (구현하지 말 것)

## 함수 네이밍 관례

사용자는 종종 첫 시도 풀이를 `함수명Prev`로 남기고, 개선한 최종 풀이를 원래 함수명으로 둔다.
이 패턴을 존중하고 `Prev` 함수를 임의로 지우지 않는다.

---

## 다 풀었으면 README 반영 + push

사용자가 "README에 추가하고 push해줘" 또는 유사 요청 시:

1. **`README.md`(일본어)와 `README.ko.md`(한국어) 둘 다** Algorithm 진척 표에 행 추가.
2. 표는 **Problem 이름 알파벳 순서**로 정렬되어 있다. 알맞은 위치에 삽입하고 **이후 `#` 번호를 전부 재정렬**한다.
3. 행 형식: `| N | Problem 제목 | [해법 요약](Algorithm/난이도/파일.cpp) |`
   - 해법 요약 예: `Two Pointers`, `DP`, `Tree Traversal (BFS)`, `Hash Table` 등 실제 풀이 접근법.
4. 표 위 문장의 문제 수 카운트 갱신: `(計 N問)`(일본어) / `(총 N문제)`(한국어).
5. 커밋 메시지: `[ADD] 파일명(확장자 제외)` — 기존 커밋 컨벤션(`[ADD] ...`)을 따른다.
6. `git add` → `commit` → `push`.

---

## 참고

- C++ 표준: C++20 (`Algorithm/CMakeLists.txt`).
- 커밋 컨벤션: `[ADD]`, `[FIX]` 등 대괄호 태그 접두.
