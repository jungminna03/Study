# Study

日本語: README.md | **한국어: [README.ko.md](README.ko.md)**

バンダイナムコのクライアントプログラマー合格を目指した学習記録。
Start: 2026-05-06

## Track

- **[Algorithm/](./Algorithm)** — LeetCode + AtCoder. C++ Only.
- **[GameMath/](./GameMath)** — Siv3D ベースのゲーム数学学習。

## 🎮 GameMath 進捗状況

Siv3D でゲーム数学の理論を実際に可視化・実装しながら学習。すべての実装は [`GameMath/Main.cpp`](GameMath/GameMath/Main.cpp) にあります。

| 理論 | 学習内容 | 実装 |
| :--- | :--- | :--- |
| 座標系変換 (Coordinate System) | 画面中心を原点とする論理座標系の構築、数学座標(Y↑)とスクリーン座標(Y↓)の軸反転変換 | `RenderGrid()` で原点中心の単位グリッド(赤=X軸、緑=Y軸)を描画、`toScene()` で論理→スクリーン座標へ変換 |
| ベクトル & フレーム非依存移動 (Vector / Delta Time) | 2Dベクトル(`Vec2`)で位置・速度を表現、`DeltaTime` を掛けてフレームレートに依存しない等速移動 | 方向キー入力で `playerPos` を `moveSpeed * DeltaTime` だけ移動 |
| 媒介変数曲線 (Parametric Equation) | 三角関数の媒介変数方程式で曲線を座標点の集合として生成 | ハート曲線 `x = 16sin³t`、`y = 13cos t − 5cos2t − 2cos3t − cos4t` を点としてサンプリングして描画 |

## 📊 Algorithm 進捗状況

LeetCode の C++ アルゴリズム問題を解きながら学習。すべての実装は `Algorithm` にあります。(計 37問)

| # | Problem | 解法 (Approach) |
| :---: | :--- | :--- |
| 1 | Backspace String Compare | [Two Pointers](Algorithm/Easy/Backspace_String_Compare.cpp) |
| 2 | Best Time to Buy and Sell Stock | [Greedy](Algorithm/Easy/Best_Time_to_Buy_and_Sell_Stock.cpp) |
| 3 | Binary Search | [Binary Search](Algorithm/Easy/Binary_Search.cpp) |
| 4 | Binary Tree Level Order Traversal | [Tree Traversal (BFS)](Algorithm/Medium/Binary_Tree_Level_Order_Traversal.cpp) |
| 5 | Climbing Stairs | [DP](Algorithm/Easy/Climbing_Stairs.cpp) |
| 6 | Contains Duplicate | [Hash Table](Algorithm/Easy/Contains_Duplicate.cpp) |
| 7 | Counting Bits | [DP + Bit Manipulation](Algorithm/Easy/Counting_Bits.cpp) |
| 8 | Fibonacci Number | [DP](Algorithm/Easy/Fibonacci_Number.cpp) |
| 9 | First Bad Version | [Binary Search](Algorithm/Easy/First_Bad_Version.cpp) |
| 10 | Group Anagrams | [Hash Table](Algorithm/Medium/Group_Anagrams.cpp) |
| 11 | House Robber | [DP](Algorithm/Medium/House_Robber.cpp) |
| 12 | Implement Queue using Stacks | [Stack](Algorithm/Easy/Implement_Queue_using_Stacks.cpp) |
| 13 | Intersection of Two Linked Lists | [Two Pointers](Algorithm/Easy/Intersection_of_Two_Linked_Lists.cpp) |
| 14 | Invert Binary Tree | [Tree Traversal (BFS)](Algorithm/Easy/Invert_Binary_Tree.cpp) |
| 15 | Kth Largest Element in a Stream | [Heap (Min-Heap)](Algorithm/Easy/Kth_Largest_Element_in_a_Stream.cpp) |
| 16 | Last Stone Weight | [Heap (Max-Heap)](Algorithm/Easy/Last_Stone_Weight.cpp) |
| 17 | Linked List Cycle | [Two Pointers (Floyd)](Algorithm/Easy/Linked_List_Cycle.cpp) |
| 18 | Longest Substring Without Repeating Characters | [Sliding Window](Algorithm/Medium/Longest_Substring_Without_Repeating_Characters.cpp) |
| 19 | Majority Element | [Boyer-Moore Voting](Algorithm/Easy/Majority_Element.cpp) |
| 20 | Maximum Depth of Binary Tree | [Tree Recursion (DFS)](Algorithm/Easy/Maximum_Depth_of_Binary_Tree.cpp) |
| 21 | Merge Two Sorted Lists | [Two Pointers (Linked List)](Algorithm/Easy/Merge_Two_Sorted_Lists.cpp) |
| 22 | Min Stack | [Stack](Algorithm/Medium/Min_Stack.cpp) |
| 23 | Missing Number | [Math (Gauss / XOR)](Algorithm/Easy/Missing_Number.cpp) |
| 24 | Move Zeroes | [Two Pointers](Algorithm/Easy/Move_Zeroes.cpp) |
| 25 | Number of Strings That Appear as Substrings in Word | [String Search](Algorithm/Easy/Number_of_Strings_That_Appear_as_Substrings_in_Word.cpp) |
| 26 | Remove All Adjacent Duplicates In String | [Stack](Algorithm/Easy/Remove_All_Adjacent_Duplicates_In_String.cpp) |
| 27 | Remove Duplicates from Sorted Array | [Two Pointers](Algorithm/Easy/Remove_Duplicates_from_Sorted_Array.cpp) |
| 28 | Remove Duplicates from Sorted List | [Linked List](Algorithm/Easy/Remove_Duplicates_from_Sorted_List.cpp) |
| 29 | Remove Element | [Two Pointers](Algorithm/Easy/Remove_Element.cpp) |
| 30 | Reverse Bits | [Bit Manipulation](Algorithm/Easy/Reverse_Bits.cpp) |
| 31 | Reverse Linked List | [Linked List](Algorithm/Easy/Reverse_Linked_List.cpp) |
| 32 | Search a 2D Matrix | [Binary Search](Algorithm/Medium/Search_a_2D_Matrix.cpp) |
| 33 | Search Insert Position | [Binary Search](Algorithm/Easy/Search_Insert_Position.cpp) |
| 34 | Two Sum | [Hash Table](Algorithm/Easy/Two_Sum.cpp) |
| 35 | Two Sum II Input Array Is Sorted | [Two Pointers](Algorithm/Medium/Two_Sum_II_Input_Array_Is_Sorted.cpp) |
| 36 | Valid Anagram | [Hash Table (Counting)](Algorithm/Easy/Valid_Anagram.cpp) |
| 37 | Valid Palindrome | [Two Pointers](Algorithm/Easy/Valid_Palindrome.cpp) |
