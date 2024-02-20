#include <iostream>
#include <vector>

enum note
{
    DO = 1,
    RE = 2,
    MI = 4,
    FA = 8,
    SOL = 16,
    LA = 32,
    SI = 64
};

void print_note(int noteFlag)
{
    if (noteFlag & DO)
    {
        std::cout << "DO ";
    }
    else if (noteFlag & RE)
    {
        std::cout << "RE ";
    }
    else if (noteFlag & MI)
    {
        std::cout << "MI ";
    }
    else if (noteFlag & FA)
    {
        std::cout << "FA ";
    }
    else if (noteFlag & SOL)
    {
        std::cout << "SOL ";
    }
    else if (noteFlag & LA)
    {
        std::cout << "LA ";
    }
    else if (noteFlag & SI)
    {
        std::cout << "SI ";
    }
}

void print_chord(std::string input_chord)
{
    unsigned int chord = 0;
    for (auto note : input_chord)
    {
        auto noteFlag = 1 << (note - '1');
        if ((chord & noteFlag) == 0)
        {
            print_note(noteFlag);
            chord |= noteFlag;
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> melody(0);
    std::string chord;

    for (int i = 0; i < 12; i++)
    {
        std::cout << "Enter the " << i + 1 << " chord (note 1-7): ";
        std::cin >> chord;
        for (int j = 0; j < chord.length(); j++)
        {
            while (chord[j] - '0' < 1 || chord[j] - '0' > 7)
            {
                std::cout << "Incorrect combination, try again: ";
                std::cin >> chord;
            }
        }
        melody.push_back(chord);
    }

    for (auto i : melody)
    {
        print_chord(i);
    }
}
