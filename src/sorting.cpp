#include"header/SortingApp.h"

void swap(Column& a, Column& b)
{
    int tmp = a.number;
    a.number = b.number;
    b.number = tmp;
}

size_t Window::MinValueIndx(Column* array, size_t size)
{
    if(numbers.empty() || !size)
        return -1;
    
    size_t min = 0;

    for(int i = 1; i < size; i++)
    {
        array[i].state = (int)COLUMN_COLORS::SEARCHING;
        Draw();

        if(array[min].number > array[i].number)
        {
            min = i;
        }
        
        array[i].state = (int)COLUMN_COLORS::IDLE;
        Draw();
    }

    return min;
}

void Window::SelectionSort()
{
    stopwatch.start();

    for(int i = 0; i < numbers.size() - 1; i++)
    {
        if(controls.terminate)
        {
            controls.sorted = true;
            return;
        }

        numbers[i].state = (int)COLUMN_COLORS::SELECTED;
        Draw();

        size_t index_of_min_val = MinValueIndx(&numbers[i], numbers.size() - i) + i;
        numbers[index_of_min_val].state = (int)COLUMN_COLORS::SELECTED;

        Draw();

        swap(numbers[i],
             numbers[index_of_min_val]);
        Draw();

        numbers[i].state = (int)COLUMN_COLORS::IDLE;
        numbers[index_of_min_val].state = (int)COLUMN_COLORS::IDLE;
        Draw();
    }

    controls.sorted = true;
    stopwatch.stop();
}

void Window::BubbleSort()
{
    stopwatch.start();

    for (int i = 0; i < numbers.size() - 1; i++)
    {
        for (int j = 0; j < numbers.size() - i - 1; j++)
        {
            if(controls.terminate)
            {
                controls.sorted = true;
                return;
            }

            numbers[j].state = (int)COLUMN_COLORS::SELECTED;
            
            if(numbers[j].number > numbers[j + 1].number)
            {
                numbers[j + 1].state = (int)COLUMN_COLORS::SELECTED;
                swap(numbers[j], numbers[j + 1]);
                Draw();
            }

            numbers[j + 1].state = (int)COLUMN_COLORS::IDLE;
            numbers[j].state = (int)COLUMN_COLORS::IDLE;
        }
    }

    controls.sorted = true;
    stopwatch.stop();
}