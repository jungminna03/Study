# Study

**日本語: [README.md](README.md)** | 한국어: README.ko.md

반다이남코 클라이언트 프로그래머 합격을 위한 학습 기록.
Start: 2026-05-06

## Track

- **[Algorithm/](./Algorithm)** — LeetCode + AtCoder. C++ Only.
- **[GameMath/](./GameMath)** — Siv3D Base GameMath Study.

## 🎮 GameMath 진행 현황

Siv3D로 게임 수학 이론을 직접 시각화·구현하며 학습. 모든 구현은 [`GameMath/Main.cpp`](GameMath/GameMath/Main.cpp)에 있음.

| 이론 | 학습 내용 | 구현 |
| :--- | :--- | :--- |
| 좌표계 변환 (Coordinate System) | 화면 중심을 원점으로 하는 논리 좌표계 구성, 수학 좌표(Y↑)와 스크린 좌표(Y↓)의 축 반전 변환 | `RenderGrid()`로 원점 중심 단위 그리드(빨강=X축, 초록=Y축) 렌더링, `toScene()`으로 논리→스크린 좌표 변환 |
| 벡터 & 프레임 독립 이동 (Vector / Delta Time) | 2D 벡터(`Vec2`)로 위치·속도 표현, `DeltaTime`을 곱해 프레임률과 무관한 등속 이동 | 방향키 입력으로 `playerPos`를 `moveSpeed * DeltaTime`만큼 이동 |
| 매개변수 곡선 (Parametric Equation) | 삼각함수 매개변수 방정식으로 곡선을 좌표점 집합으로 생성 | 하트 곡선 `x = 16sin³t`, `y = 13cos t − 5cos2t − 2cos3t − cos4t`를 점으로 샘플링해 렌더링 |

## 📊 Algorithm 진행 현황

LeetCode의 C++ 알고리즘 문제를 풀면서 학습. 모든 구현은 `Algorithm`에 있음. (총 35문제)

| # | Problem | 풀이 방법 |
| :---: | :--- | :--- |
| 1 | Backspace String Compare | [Two Pointers](Algorithm/Easy/Backspace_String_Compare.cpp) |
| 2 | Best Time to Buy and Sell Stock | [Greedy](Algorithm/Easy/Best_Time_to_Buy_and_Sell_Stock.cpp) |
| 3 | Binary Search | [Binary Search](Algorithm/Easy/Binary_Search.cpp) |
| 4 | Climbing Stairs | [DP](Algorithm/Easy/Climbing_Stairs.cpp) |
| 5 | Contains Duplicate | [Hash Table](Algorithm/Easy/Contains_Duplicate.cpp) |
| 6 | Counting Bits | [DP + Bit Manipulation](Algorithm/Easy/Counting_Bits.cpp) |
| 7 | Fibonacci Number | [DP](Algorithm/Easy/Fibonacci_Number.cpp) |
| 8 | First Bad Version | [Binary Search](Algorithm/Easy/First_Bad_Version.cpp) |
| 9 | Group Anagrams | [Hash Table](Algorithm/Medium/Group_Anagrams.cpp) |
| 10 | House Robber | [DP](Algorithm/Medium/House_Robber.cpp) |
| 11 | Implement Queue using Stacks | [Stack](Algorithm/Easy/Implement_Queue_using_Stacks.cpp) |
| 12 | Intersection of Two Linked Lists | [Two Pointers](Algorithm/Easy/Intersection_of_Two_Linked_Lists.cpp) |
| 13 | Invert Binary Tree | [Tree Traversal (BFS)](Algorithm/Easy/Invert_Binary_Tree.cpp) |
| 14 | Kth Largest Element in a Stream | [Heap (Min-Heap)](Algorithm/Easy/Kth_Largest_Element_in_a_Stream.cpp) |
| 15 | Last Stone Weight | [Heap (Max-Heap)](Algorithm/Easy/Last_Stone_Weight.cpp) |
| 16 | Linked List Cycle | [Two Pointers (Floyd)](Algorithm/Easy/Linked_List_Cycle.cpp) |
| 17 | Longest Substring Without Repeating Characters | [Sliding Window](Algorithm/Medium/Longest_Substring_Without_Repeating_Characters.cpp) |
| 18 | Majority Element | [Boyer-Moore Voting](Algorithm/Easy/Majority_Element.cpp) |
| 19 | Merge Two Sorted Lists | [Two Pointers (Linked List)](Algorithm/Easy/Merge_Two_Sorted_Lists.cpp) |
| 20 | Min Stack | [Stack](Algorithm/Medium/Min_Stack.cpp) |
| 21 | Missing Number | [Math (Gauss / XOR)](Algorithm/Easy/Missing_Number.cpp) |
| 22 | Move Zeroes | [Two Pointers](Algorithm/Easy/Move_Zeroes.cpp) |
| 23 | Number of Strings That Appear as Substrings in Word | [String Search](Algorithm/Easy/Number_of_Strings_That_Appear_as_Substrings_in_Word.cpp) |
| 24 | Remove All Adjacent Duplicates In String | [Stack](Algorithm/Easy/Remove_All_Adjacent_Duplicates_In_String.cpp) |
| 25 | Remove Duplicates from Sorted Array | [Two Pointers](Algorithm/Easy/Remove_Duplicates_from_Sorted_Array.cpp) |
| 26 | Remove Duplicates from Sorted List | [Linked List](Algorithm/Easy/Remove_Duplicates_from_Sorted_List.cpp) |
| 27 | Remove Element | [Two Pointers](Algorithm/Easy/Remove_Element.cpp) |
| 28 | Reverse Bits | [Bit Manipulation](Algorithm/Easy/Reverse_Bits.cpp) |
| 29 | Reverse Linked List | [Linked List](Algorithm/Easy/Reverse_Linked_List.cpp) |
| 30 | Search a 2D Matrix | [Binary Search](Algorithm/Medium/Search_a_2D_Matrix.cpp) |
| 31 | Search Insert Position | [Binary Search](Algorithm/Easy/Search_Insert_Position.cpp) |
| 32 | Two Sum | [Hash Table](Algorithm/Easy/Two_Sum.cpp) |
| 33 | Two Sum II Input Array Is Sorted | [Two Pointers](Algorithm/Medium/Two_Sum_II_Input_Array_Is_Sorted.cpp) |
| 34 | Valid Anagram | [Hash Table (Counting)](Algorithm/Easy/Valid_Anagram.cpp) |
| 35 | Valid Palindrome | [Two Pointers](Algorithm/Easy/Valid_Palindrome.cpp) |
