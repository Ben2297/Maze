#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main()
{
    std::vector<std::vector<char>> maze;
    std::fstream mazeFile;

    mazeFile.open("quickest_route_1.txt", std::ios::in); // Opens the maze file
    char ch;
    std::vector<char> temp;
    while (mazeFile >> std::noskipws >> ch)
    {
        if (ch == '\n')
        {
            maze.push_back(temp);
            temp.clear();
        }
        else
        {
            temp.push_back(ch);
        }
    }
    mazeFile.close();

    return 0;
}
