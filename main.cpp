#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Position
{
    int x{0};
    int y{0};

    bool operator == (const Position& other)
    {
        return x == other.x && y == other.y;
    }
};

struct Direction
{
    Position position;
    char dir;
};

Position start, end;
std::vector<Direction> bestPath;
std::vector<std::vector<char>> maze;
int noOfRows = 1;
int noOfColumns = 1;

void findPath (Position currentPos, std::vector<Direction> currentPath)
{
    std::vector<Direction> tempPath;

    if (currentPos == end)
    {
        if (bestPath.empty() || currentPath.size() < bestPath.size())
        {
            bestPath = currentPath;
        }
        return;
    }

    if (maze[currentPos.x][currentPos.y] == 'x')
    {
        return;
    }

    Position temp = currentPos;
    temp.y -= 1;
    if (temp.y >= 0)
    {
        bool duplicateFound = false;
        for (int i = 0; i < currentPath.size(); i++)
        {
            if (currentPath[i].position == currentPos)
            {
                duplicateFound = true;
            }
        }
        if (!duplicateFound)
        {
            tempPath = currentPath;
            tempPath.push_back(Direction{currentPos, 'W'});
            std::cout << 'W' << std::endl;
            findPath(temp, tempPath);
        }
    }

    temp = currentPos;
    temp.x += 1;
    if (temp.x < maze.size())
    {
        bool duplicateFound = false;
        for (int i = 0; i < currentPath.size(); i++)
        {
            if (currentPath[i].position == currentPos)
            {
                duplicateFound = true;
            }
        }
        if (!duplicateFound)
        {
            tempPath = currentPath;
            tempPath.push_back(Direction{currentPos, 'S'});
            std::cout << 'S' << std::endl;
            findPath(temp, tempPath);
        }
    }

    temp = currentPos;
    temp.y += 1;
    if (temp.y < maze[0].size())
    {
        bool duplicateFound = false;
        for (int i = 0; i < currentPath.size(); i++)
        {
            if (currentPath[i].position == currentPos)
            {
                duplicateFound = true;
            }
        }
        if (!duplicateFound)
        {
            tempPath = currentPath;
            tempPath.push_back(Direction{currentPos, 'E'});
            std::cout << 'E' << std::endl;
            findPath(temp, tempPath);
        }
    }

    temp = currentPos;
    temp.x -= 1;
    if (temp.x >= 0)
    {
        bool duplicateFound = false;
        for (int i = 0; i < currentPath.size(); i++)
        {
            if (currentPath[i].position == currentPos)
            {
                duplicateFound = true;
            }
        }
        if (!duplicateFound)
        {
            tempPath = currentPath;
            tempPath.push_back(Direction{currentPos, 'N'});
            std::cout << 'N' << std::endl;
            findPath(temp, tempPath);
        }
    }
}

int main()
{
    std::fstream mazeFile;

    mazeFile.open("quickest_route_3.txt", std::ios::in); // Opens the maze file
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

    std::vector<Direction> tempPath;
    findPath(start, tempPath);

    for (int i = 0; i < bestPath.size(); i++)
    {
        std::cout << bestPath[i].dir;
    }
    std::cout << std::endl;

    return 0;
}

