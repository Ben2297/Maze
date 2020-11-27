#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Position
{
    int x{0};
    int y{0};
};

bool findPath (Position currentPos)
{

}

int main()
{
    std::vector<std::vector<char>> maze;
    std::fstream mazeFile;
    Position start, end;

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
    maze.push_back(temp);
    mazeFile.close();

    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j] == 'A')
            {
                start.x = i;
                start.y = j;
            }
            else if (maze[i][j] == 'B')
            {
                end.x = i;
                end.y = j;
            }
        }
    }



    return 0;
}
