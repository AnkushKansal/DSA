#include <array>
#include <iostream>

void bubble_sort(auto &input)
{

    auto size = input.size();
    if (size < 2)
        return;

    for (size_t end = size; end > 1; --end)
    {
        bool swapped = false;

        for (size_t i = 0; i < end - 1; ++i)
        {
            if (input[i] > input[i + 1])
            {
                std::swap(input[i], input[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break; // one clean pass → fully sorted
    }
}

int main()
{

    std::array<int, 4> input{0, 1, 23, 3};
    bubble_sort(input);

    for (auto &ele : input)
    {
        std::cout << ele << ",";
    }
}