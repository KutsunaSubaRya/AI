---
tags: AI
title: AI Assignment 3
---

# AI Assignment 3

* 學生: 蘇子權
* 學號: 40947023S
* 系級: 資工 113
* 由於程式中的 bug 修了十分的久(有寫在第六點)，因此遲交，還請見諒

## Directory Tree
```
// Assignment 2 directory tree

├── gameLib
│   ├── basic.cpp
│   ├── basic.h
│   ├── board.cpp
│   ├── board.h
│   ├── game.cpp
│   └── game.h
├── input.txt
├── main.cpp
├── makefile
└── testcase
    ├── input1.txt
    ├── input2.txt
    ├── input3.txt
    ├── input4.txt
    └── input5.txt
```


## 1
* 硬體規格
    * CPU：AMD Ryzen 5 5600X (12) @ 3.700GHz
    * 顯卡：NVIDIA GeForce RTX 3600
    * RAM：16G
    * OS: Arch Linux
    * 選用該硬體規格和此電腦，而非我的筆電主要原因是 GPU 加速運算。
    * 選用該作業系統原因是本身對於使用 Windows 較為熟悉。
    * 寫程式的環境是 Arch Linux
        * ![](https://hackmd.io/_uploads/ByZ-rgeH3.png)


* 連絡電話
    * 0976960352
## 2. 
* 如何執行程式
    * 本次作業是使用 C++ 撰寫，也有寫 makefile 方便助教批改，但如果沒辦法 make，folder 中我也有附上執行檔以便不時之需。
    * **縱橫殺棋對抗賽** 的主要程式是 `main.cpp` 。
        * 若要批改，如果是 **使用 `make`** 的情況...
            1. 進入作業的 folder 中。
            2. 將指定要測試的 testcase (`./testcase` folder 中 `input<1~5>.txt` 指定欲批改的一筆內容**全部複製並全部覆寫**到現在作業目錄下的 `input.txt`)。
            3. `make clean`
            4. `make`
            5. `./main`
        * 若要批改，如果是 **使用執行檔** 的情況... 
            1. 進入作業的 folder 中。
            2. 將指定要測試的 testcase (`./testcase` folder 中 `input<1~5>.txt` 指定欲批改的一筆內容**全部複製並全部覆寫**到現在作業目錄下的 `input.txt`)。
            3. `./main`
## 3
* 第一筆：使用作業範例一的測資，為 $3\times4$ 的棋盤。
* 第二筆：使用作業範例二的測資，為 $3\times4$ 的棋盤。
* 第三筆：隨機產生的測資，為 $6\times7$ 的棋盤。
* 第四筆：隨機產生的測資，為 $8\times7$ 的棋盤。
* 第五筆：隨機產生的測資，為 $8\times8$ 的棋盤。
## 4
* 什麼方法
    * 將遊戲的功能細分(如本題第二點的回答)
    * 將板面讀入後建立好兩位 player 的狀態並呼叫使用 alpha beta pruning 遞迴求解
    * 兩位 player 輪流執行當回合的動作
    * 加總兩位 player 的得分後並印出
* 什麼資料結構
    * 根據 gameLib 的 folder，我先將遊戲本題的 core 和 API 建立好
        * `board.h`、`board.cpp`
            * 定義 game board 上的每一格的狀態以及修改該值的 api
                * class name -> boardUnit
            * 將整個 game board 以 `std::vector<std::vector<boardUnit>>` 的形式儲存
                * class name -> gameBoardUnit
                * 可以方便往下 board unit init board 的值
                * 與 game class friend
        * `game.h`、`game.cpp` 
            * 將整個 game board 以 `std::vector<std::vector<boardUnit>>` 的形式儲存
            * 設計
                * constructor init game board
                * 得到 game board 的大小 api
                * board 是否清空的 api
                * 指定其中的 row 或 column 並將其清空
                * 得到其中的 row 或 column 的 1 (棋子) 的數量的 api
                * 下一回輪的操作的 api
                * 那到 board 長、寬的 api
                * getter, setter

        * `basic.h`、`basic.cpp`
            * 主要是將測資 `.txt` file 轉成 string 再將1、0 parse 出來用 `vector<int>` 儲存。
            * 可以更新兩個 player 的 score 的 api
    * `main.cpp`
        * 讀好資料、construct and init game board 後 call AlphaBetaPruing function。
        * evaluate function 的主要思想 (每個節點上的值) 是 `player1_score - player2_score`
        * 演算法流程中詳細的 annotation 在 codebase 中。
* 什麼技術
    * alpha beta pruning 的演算法增進原先 min max 的不必要的 branch(也就是可以透或 alpha 和 beta 知道另一條 branch 的查詢是多餘的)

|編號|測資|執行結果|
|:-|:-|:-|
|testcase*-1|![](https://hackmd.io/_uploads/BJ9e1Wgrn.png)|![](https://hackmd.io/_uploads/rkG5kWxS2.png)|
|testcase*-2|![](https://hackmd.io/_uploads/SktGkbeHh.png)|![](https://hackmd.io/_uploads/HyRT1WlBh.png)|
|testcase*-3|![](https://hackmd.io/_uploads/S1C7JZgHh.png)|![](https://hackmd.io/_uploads/ryyQlbgrh.png)|
|testcase*-4|![](https://hackmd.io/_uploads/SJxHJWgSn.png)|![](https://hackmd.io/_uploads/H1nEe-lH2.png)|
|testcase*-5|![](https://hackmd.io/_uploads/HyGIyWxr3.png)|![](https://hackmd.io/_uploads/B18vg-gS2.png)|
## 5
* 參考資料
    * https://zh.wikipedia.org/zh-tw/Alpha-beta%E5%89%AA%E6%9E%9D
    * https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/
    * https://zhuanlan.zhihu.com/p/65108398
    * https://fu-sheng-wang.blogspot.com/2017/02/ai-16-alpha-beta-pruning.html
    * https://www.youtube.com/watch?v=hM2EAvMkhtk&ab_channel=MITOpenCourseWare
## 6
* 整體實作下來遇到的狀況基本上是一開始在建構資料結構和如何有層次性的拉好程式的架構
* 中途在設定 evaluate functon (也就是 node value 到底要怎麼決定) 想了兩天之久，在嘗試很多方法後才有了結論
* 程式完成後在砸下大筆的測資後遇到 ... 
    * **stack-overflow** 的問題，最後使用 Asan (Address Sanitizer) 加上 track program logic 花了半天找到問題如下
        * 原先是邊運行 alpha beta pruing 邊 new node，最後忘了 delete node
    * 微小的誤差
        * 是 alpha 和 beta 的值給予錯誤 
        * 是 setPlayerScore 的地方設定錯 player score
    * 以上基本上都算是實作 code 的問題
## 7
* 我在砸下 $n, m \gt 6$ 的測資時會跑非常的久(就是 5~10 分鐘都跑不出來)
    * 我嘗試在網路上尋求優化 alpha beta pruning 是否還有加速的手段，然而找到以下的這部 MIT OpenCourse 的影片的 [39:18](https://youtu.be/hM2EAvMkhtk?t=2358) 中有提到 reorder 的想法，因此我在實做 alpha beta pruning 時有先存每一行和列的總和和位置，並且將其以降序的方式 sort，如此一來在搜尋的過程中可以較容易使 prune 的情形頻繁發生，因此而造成加速的效果。
    * 我使用了這個手法優化並發現 8*8 的版面只需約 1 秒(如第五筆測資只使用了 1.39 秒)。
    * 上述有提到的影片是這部：[MIT OpenCourseWare - Mega-R3. Games, Minimax, Alpha-Beta](https://www.youtube.com/watch?v=hM2EAvMkhtk&ab_channel=MITOpenCourseWare)



