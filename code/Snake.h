#include <queue>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

class Snake {
private:
	queue<tuple<int, int>> position;
	stack<tuple<int, int>> currPath;

	bool bfsFindPath;
    bool hasPath; // has path in record or not
    
	int pointCnt;
	int snakeLengthBound = 94; // set to some extent that the snake is long enough
	
public:
	// constructor
	Snake(queue<tuple<int, int>> startPosition);

	// Find the next step of the snake and move.
	// @post The snake will move one step, which means a new element (head of the snake) will be pushed to the back of the queue,
	//       and the front element (tail of the snake) will be popped.
	// @return The next position of the snake.
	queue<tuple<int, int>> nextPosition(vector<vector<int>> map);
	
	// Find the positions of the food on the map.
	// @pre There exist at least one piece of food on the map, food will be presented as a non-negative integer.
	// @return A vector that stores the positions of the food.
	vector<tuple<int, int>> findFood(vector<vector<int>> &map);

	// Find a path to target (food or tail) by Breadth First Search
	// @pre The positions of the starting point and destination must be inside the range of the map.
	// @return An empty stack if no path is found, or a stack that stores postitions of the path if a path is found.
	stack<tuple<int, int>> bfsNext(vector<vector<int>> &map, tuple<int, int> start, tuple<int, int> destination);

	// Mark the snake's body as -1 (obstacle) on the map.
	// @post The map will be updated with more obstacles.
	void markBodyPosition(vector<vector<int>> &map);

	// Send out a virtual snake to walk the path to the food, check if it is possible for the virtual snake to find its tail after eating the food.
	// @pre A copy of the current map and a path to the food.
	// @return A empty stack if it is not possible for the virtual snake to find its tail after eating the food,
	//         or a stack that stores the path to the tail after eating.
	stack<tuple<int, int>> bfsVirtualTail(vector<vector<int>> &copyMap, stack<tuple<int, int>> &path);

	// Check if the next step will arrive any food.
	// @para pos is the next position (step).
	// @return True if the next step is a food, false if not.
	bool arriveFood(tuple<int, int> &pos, vector<tuple<int, int>> &food);

	// Check if the head of the snake is crashing into any obstacle or itself.
	// @return True if collide will happen, false if not.
	bool collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map);
};
