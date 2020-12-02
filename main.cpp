#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <climits>

// Struct to hold 2D coordinates
struct Position
{
    int x{0};
    int y{0};

    bool operator == (const Position& other)
    {
        return x == other.x && y == other.y;
    }
};

// Struct to hold node information
struct Node
{
    int x, y, dist;
    std::string route;
};

std::vector<std::vector<char>> maze; // 2D vector for holding the maze layout
std::vector<std::vector<bool>> visited; // 2D vector for holding information about where in the maze has been visited

int row[] = { -1, 0, 0, 1 }; // Holds X coordinates for directions
int col[] = { 0, -1, 1, 0 }; // Holds Y coordinates for directions
char directions[] = {'N', 'W', 'E', 'S'}; // Holds directional char values

// Determines if a move is valid
bool isValid(int x, int y)
{
    return (x >= 0) && (x < maze.size()) && (y >= 0) && (y < maze[0].size())
           && !visited[x][y] && maze[x][y] != 'x';
}

// Function for solving the maze
void findPath (Position start, Position end)
{
    std::queue<Node> nodeQueue; // Holds nodes that need to be explored
    int minDist = INT_MAX; // Sets the minimum path distance to the maximum value

    visited[start.x][start.y] = true; // Sets the start node as visited
    nodeQueue.push({start.x, start.y, 0, ""}); // Pushes the start node to the queue

    // Loops until every node has been explored or shortest path is found
    while (!nodeQueue.empty())
    {
        Node node = nodeQueue.front(); // Sets the current node to the one at the front of the queue
        nodeQueue.pop(); // Remove that node from the queue

        int i = node.x, j = node.y, dist = node.dist; // Breaks up the node information

        // If the node is the end position
        if (i == end.x && j == end.y)
        {
            minDist = dist; // Sets the minimum path distance
            std::cout << "Best route:" << std::endl;
            std::cout << node.route << std::endl; // Outputs the route directions
            std::cout << "Press any key to exit" << std::endl;
            break; // Ends the loop
        }

        // Checks all four directions from the current node
        for (int k = 0; k < 4; k++)
        {
            // If the direction leads to a valid move
            if (isValid(i + row[k], j + col[k]))
            {
                visited[i + row[k]][j + col[k]] = true; // Sets the node as visited
                nodeQueue.push({i + row[k], j + col[k], dist + 1, (node.route + directions[k])}); // Pushes the node to the queue with the best route to the node
            }
        }
    }

    // If no path was found
    if (minDist == INT_MAX)
    {
        std::cout << "The destination cannot be reached" << std::endl;
    }
}

int main()
{
    std::fstream mazeFile; // File stream for reading the maze file
    Position start, end; // Holds the start and end positions
    std::string input; // String for holding the file name
    bool startFound; // Start point found boolean
    bool endFound; // End point found boolean
    bool validMaze = false; // Valid maze boolean

    // Loops until a maze with a valid start and end point is inputted
    while (!validMaze)
    {
        // Loops until a valid file name is entered
        while (!mazeFile.is_open())
        {
            std::cout << "Please enter the maze file name:" << std::endl;
            std::getline (std::cin, input); // Retrieves the user input

            mazeFile.open(input, std::ios::in); // Opens the maze file

            // If the file name is invalid
            if (!mazeFile.is_open())
            {
                std::cout << "Invalid file name, please try again" << std::endl;
            }
        }

        char ch; // Holds the next character in the file
        std::vector<char> temp; // Holds the current row in the file
        std::vector<bool> tempVisited; // Used to set each row of the 2D visited vector

        // Reads the maze file character by character
        while (mazeFile >> std::noskipws >> ch)
        {
            // If a new line is reached
            if (ch == '\n')
            {
                maze.push_back(temp); // Pushes the row to the 2D maze vector
                temp.clear(); // Clears the temporary row vector
                visited.push_back(tempVisited); // Pushes the row to the 2D visited vector
                tempVisited.clear(); // Clears the temporary visited row vector
            }
            else
            {
                temp.push_back(ch); // Pushes the character to the maze row
                tempVisited.push_back(false); // Pushes a value of false to the visited row
            }
        }
        maze.push_back(temp); // Pushes the final row to the 2D maze vector
        visited.push_back(tempVisited); // Pushes the final row to the 2D visited vector
        mazeFile.close(); // Closes the maze file

        startFound = false;
        endFound = false;

        // Loops through the maze to find the start and end points
        for (int i = 0; i < maze.size(); i++)
        {
            for (int j = 0; j < maze[i].size(); j++)
            {
                if (maze[i][j] == 'A')
                {
                    start.x = i;
                    start.y = j;
                    startFound = true;
                }
                else if (maze[i][j] == 'B')
                {
                    end.x = i;
                    end.y = j;
                    endFound = true;
                }
            }
        }

        if (startFound && endFound)
        {
            validMaze = true;
        }
        else
        {
            if (!startFound)
            {
                std::cout << "No valid start point" << std::endl;
            }

            if (!endFound)
            {
                std::cout << "No valid end point" << std::endl;
            }
        }
    }

    findPath(start, end); // Calls the maze solving function

    std::string s;
    std::getline(std::cin, s);

    return 0;
}

