#include"header/SortingApp.h"
#include<stdint.h>
#include<ctime>

// int number_of_allocs = 0;

// void* operator new(size_t size)
// {
//     number_of_allocs++;
//     return malloc(size);
// }

Column::Column(int num)
{
    this->number = num;
    this->state = (int)COLUMN_COLORS::IDLE;
}

Controls::Controls() : sort_type(0), target_fps(500), terminate(false), sorted(false) {}

Window::Window() : sort {
        std::bind(&Window::BubbleSort, this),
        std::bind(&Window::SelectionSort, this)
    }
{
    srand(time(NULL));
    numbers.reserve(constants::MAX_COLUMNS);
    InitWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, "Sorting");
    SetTargetFPS(controls.target_fps);
    rlImGuiSetup(true);

    GenerateArray();
}

void Window::GenerateArray()
{
    if(numbers.size())
        numbers.clear();

    for(int i = 0; i < constants::COLUMNS; i++)
        numbers.emplace_back(1 + rand() % constants::COLUMNS);
}

Window::~Window()
{
    rlImGuiShutdown();
    CloseWindow();
}

void Window::DrawInformationGUI()
{
    { /*Information about array window*/
        ImGui::Begin("Array:");
        
        for(int i = 0; i < numbers.size(); i++)
        {
            ImGui::Text("%d", numbers[i].number);
            if((i+1)%10)
                ImGui::SameLine();
        }

        ImGui::Text("Capacity: %Lu\nSize: %Lu",
                    numbers.capacity(), numbers.size());

        ImGui::End();
    }

    { /*Technical information GUI window*/
        ImGui::Begin("Technical information");

        ImGui::Text("%s algorithm illustration", constants::ALGORITHM_NAME[controls.sort_type]);
        ImGui::Text("FPS (target: %d): %d", controls.target_fps, GetFPS());
        ImGui::Text("Window size: %d x %d", constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT);
        ImGui::Text("Number of columns: %d", constants::COLUMNS);
        ImGui::Text("Execution time: %.3lf s", stopwatch.showInRealTime());

        ImGui::End();
    }
}

void Window::DrawControlGUI()
{
    { /*Control GUI window*/
        ImGui::Begin("Controls");

        { /*Child: Separated buttons control*/
            ImGui::BeginChild("ContrlButtns", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 100), ImGuiChildFlags_None);

            if(ImGui::Button("Pause sorting", ImVec2(126, 0)))
            {
                stopwatch.pause();
                controls.terminate = true;
            }
            
            if(ImGui::Button("Continue sorting", ImVec2(126, 0)) && controls.terminate)
            {
                stopwatch.resume();
                controls.terminate = false;
                controls.sorted = false;
            }

            if(ImGui::Button("Restart sorting", ImVec2(126, 0)))
            {
                GenerateArray();
                stopwatch.reset();
                controls.sorted = false;
                controls.terminate = false;
            }

            ImGui::EndChild();
        }
        
        ImGui::SameLine();

        { /*Child: Sorting type table selection*/
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("SortSel", ImVec2(0, 150), ImGuiChildFlags_Borders);

            if (ImGui::BeginTable("SortSel_split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
            {
                ImGui::TableSetupColumn("Sort Type");
                ImGui::TableHeadersRow();

                for (int i = 0; i < constants::AN_SIZE; i++)
                {
                    ImGui::TableNextColumn();
                    if(ImGui::Button(constants::ALGORITHM_NAME[i], ImVec2(-FLT_MIN, 0.0f)) && controls.terminate)
                    {
                        controls.sort_type = i;
                    }
                }
                ImGui::EndTable();
            }
            ImGui::EndChild();
            ImGui::PopStyleVar();
        }

        ImGui::Text("Set target FPS (execution speed)");
        if(ImGui::SliderInt("##", &controls.target_fps, constants::MIN_TARGET_FPS, constants::MAX_TARGET_FPS))
            SetTargetFPS(controls.target_fps);

        ImGui::End();
    }
}

void Window::DrawGraph()
{
    for(int i = 0; i < numbers.size(); i++)
    {
        DrawRectangle(
            i*(constants::WINDOW_WIDTH / numbers.size()), 
            constants::WINDOW_HEIGHT - (constants::COLUMN_SIZE * numbers[i].number),
            constants::COLUMN_SIZE,
            constants::COLUMN_SIZE * numbers[i].number,
            controls.sorted? GREEN : constants::FORMAT_COLORS[numbers[i].state]
        );
    }
}

void Window::Draw()
{
    BeginDrawing();
    ClearBackground({0, 0, 0, 255});
    rlImGuiBegin();
    DrawInformationGUI();
    DrawControlGUI();
    
    DrawGraph();

    rlImGuiEnd();
    EndDrawing();
}

void Window::Run()
{
    while(!WindowShouldClose())
    {
        if(!controls.sorted)
        {
            sort[controls.sort_type]();
        }
        else
            Draw();
    }
}