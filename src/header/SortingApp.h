#pragma once

#include<raylib.h>
#include<vector>
#include<array>
#include<functional>
#include"../../lib/rlImGui-main/rlImgui.h"
#include"../../lib/rlImGui-main/imgui.h"
#include"stopwatch.hpp"

namespace constants
{
    constexpr uint16_t WINDOW_HEIGHT  = 600;
    constexpr uint16_t WINDOW_WIDTH   = 1000;
    constexpr uint16_t MAX_COLUMNS    = WINDOW_WIDTH / 2;
    constexpr uint16_t COLUMNS        = 100;
    constexpr uint16_t MAX_TARGET_FPS = 10000;
    constexpr uint16_t MIN_TARGET_FPS = 1;

    constexpr uint16_t COLUMN_SIZE    = WINDOW_HEIGHT / COLUMNS;

    constexpr int      AN_SIZE        = 2;
    constexpr const char* ALGORITHM_NAME[] = {
                                "Bubble Sort",
                                "Selection Sort"
    };

    constexpr Color    FORMAT_COLORS[3] = {
                                WHITE,
                                RED,
                                BLUE
    };
}

enum class COLUMN_COLORS
{
    IDLE,
    SELECTED,
    SEARCHING
};

struct Column
{
    int number;
    int state;

    Column(int num);
};

struct Controls
{
    int sort_type;
    int target_fps;
    bool terminate;
    bool sorted;
    int columns;

    Controls();
};

class Window
{
    public:
        Window();
        ~Window();

        void Run();
    
    private:
        void GenerateArray();
        size_t MinValueIndx(Column* array, size_t size);

        /*Draw methods*/
        void Draw();
        void DrawGraph();
        void DrawInformationGUI();
        void DrawControlGUI();
        
        /*Sorting algorithms*/
        void BubbleSort();
        void SelectionSort();

        Time::Stopwatch stopwatch;
        Controls controls;
        std::vector<Column> numbers;
        std::array<std::function<void()>, 2> sort;
};