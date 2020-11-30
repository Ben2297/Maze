#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <climits>

struct Position
{
    int x{0};
    int y{0};

    bool operator == (const Position& other)
    {
        return x == other.x && y == other.y;
    }
};

struct Node
{
    int x, y, dist;
    std::string route;
};

std::vector<std::vector<char>> maze;
std::vector<std::vector<bool>> visited;

int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };
char directions[] = {'N', 'W', 'E', 'S'};

bool isValid(int x, int y)
{
    return (x >= 0) && (x < maze.size()) && (y >= 0) && (y < maze[0].size())
           && !visited[x][y] && maze[x][y] != 'x';
}

void findPath (Position start, Position end)
{
    std::vector<char> prevDirections;
    std::queue<Node> q;
    int minDist = INT_MAX;

    visited[start.x][start.y] = true;
    q.push({start.x, start.y, 0, ""});

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int i = node.x, j = node.y, dist = node.dist;

        if (i == end.x && j == end.y)
        {
            minDist = dist;
            std::cout << node.route << std::endl;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            if (isValid(i + row[k], j + col[k]))
            {
                visited[i + row[k]][j + col[k]] = true;
                prevDirections.push_back(directions[k]);
                q.push({ i + row[k], j + col[k], dist + 1, (node.route + directions[k])});
            }
        }
    }

    if (minDist != INT_MAX)
        std::cout << "The shortest path from source to destination "
                "has length " << minDist;
    else
        std::cout << "Destination can't be reached from given source";
}

int main()
{
    std::fstream mazeFile;
    Position start, end;

    mazeFile.open("quickest_route_3.txt", std::ios::in); // Opens the maze file
    char ch;
    std::vector<char> temp;
    std::vector<bool> tempVisited;
    while (mazeFile >> std::noskipws >> ch)
    {
        if (ch == '\n')
        {
            maze.push_back(temp);
            temp.clear();
            visited.push_back(tempVisited);
            tempVisited.clear();
        }
        else
        {
            temp.push_back(ch);
            tempVisited.push_back(false);
        }
    }
    maze.push_back(temp);
    visited.push_back(tempVisited);
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

    findPath(start, end);

    return 0;
}

