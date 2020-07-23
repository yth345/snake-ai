#include "Snake.h"

Snake::Snake(queue<tuple<int, int>> start_position) : bfsFindPath(true), hasPath(false), pointCnt(0)
{
	position = start_position;
}


queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map)
{
    tuple<int, int> nextPos;
    vector<tuple<int, int>> food = findFood(map);
	bool foodOnBody = false;
	queue<tuple<int, int>> copyPosition = position;

	// If the food generates on the snake's body, add one body length immediately
	for (int i = 0; i < copyPosition.size(); i++){
		if (arriveFood(copyPosition.front(), food))
			foodOnBody = true;
		copyPosition.pop();
	}



	// if there is no path in record, find one
    if (!this->hasPath){

		vector<vector<int>> copyMap, copyMap2;
	    vector<int> row;
	    for (int i = 0; i < map.size(); i++){
	    	for (int j = 0; j < map[0].size(); j++){
	    		row.push_back(map[i][j]);
	    	}
	    	copyMap.push_back(row);
			copyMap2.push_back(row);
	    	row.clear();
	    }

        // do bfs
        this->currPath = bfsNext(copyMap, position.back(), food[food.size()-1]);

		// see if it is possible for the snake to find its tail after eating the current food, if not, follow tail
		// send out virtual snake only when the snake is long enough
		if (pointCnt > snakeLengthBound){

			if (!this->currPath.empty()){
				stack<tuple<int, int>> virtualTailPath = bfsVirtualTail(copyMap2, this->currPath);

				if (virtualTailPath.empty()){
					stack<tuple<int, int>> tailPath = bfsNext(copyMap, position.back(), position.front());

					if (!tailPath.empty()){
						nextPos = tailPath.top();
						if (arriveFood(nextPos, food) || foodOnBody){
							this->hasPath = false;
							pointCnt++;
						}else
							position.pop();
					
    					position.push(nextPos);
						return position;
					}

				}
			}
			
		}
		
    }



	// if the path in record is not yet empty, move one step on the current path
    if (!this->currPath.empty()){
        this->hasPath = true;
        nextPos = this->currPath.top();
        this->currPath.pop();
    }

	// otherwise, find a valid way to move
    else{
        this->hasPath = false;
        tuple<int, int> head = position.back();
        int headX = get<0>(head), headY = get<1>(head);
		
        // up
        if (map[headX][headY+1] != -1 && !collide(position,tuple<int, int>(headX,headY+1),map))
            nextPos = {headX, headY+1};
        // right
        else if (map[headX+1][headY] != -1 && !collide(position,tuple<int, int>(headX+1,headY),map))
            nextPos = {headX+1, headY};
        // down
        else if ((map[headX][headY-1] != -1) && !collide(position,tuple<int, int>(headX,headY-1),map))
            nextPos = {headX, headY-1};
        // left
        else if (map[headX-1][headY] != -1 && !collide(position,tuple<int, int>(headX-1,headY),map))
            nextPos = {headX-1, headY};
        // if the snake is stuck, stay at current position
        else
            nextPos = {headX, headY};
    }



	// update position
    if (arriveFood(nextPos, food) || foodOnBody){
		hasPath = false;
		pointCnt++;
	}else{
		position.pop();
	}
        
    position.push(nextPos);
	return position;  

}



vector<tuple<int, int>> Snake::findFood(vector<vector<int>> &map) 
{
	vector<tuple<int, int>> foodList;
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[0].size(); j++){
			if (map[i][j] > 0)
				foodList.push_back({i, j});
		}
	}
	return foodList;
}



stack<tuple<int, int>> Snake::bfsNext(vector<vector<int>> &map, tuple<int, int> start, tuple<int, int> destination) 
{
    int startX = get<0>(start), startY = get<1>(start);
	int dstX = get<0>(destination), dstY = get<1>(destination);
	queue<tuple<int, int>> que;
    stack<tuple<int, int>> path;

	vector<vector<bool>> visited;
	vector<bool> rowVisited;
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[0].size(); j++){
			rowVisited.push_back(false);
		}
		visited.push_back(rowVisited);
	}
	vector<vector<tuple<int, int>>> predecessor;
	vector<tuple<int, int>> row;
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[0].size(); j++){
			row.push_back({0, 0});
		}
		predecessor.push_back(row);
	}
	


	int x = 0, y = 0;
	markBodyPosition(map);

	que.push(start);
	while(!que.empty()){
		x = get<0>(que.front());
		y = get<1>(que.front());
		que.pop();
		visited[x][y] = true;

		// right
		if (!visited[x][y+1]){
			if (x == dstX && y+1 == dstY){
				predecessor[x][y+1] = {x, y};
				break;
			}else if (map[x][y+1] != -1){
				que.push({x, y+1});
				predecessor[x][y+1] = {x, y};
				visited[x][y+1] = true;
			}
		}

		// down
		if (!visited[x+1][y]){
			if (x+1 == dstX && y == dstY){
				predecessor[x + 1][y] = {x, y};
				break;
			}else if (map[x+1][y] != -1){
				que.push({x+1, y});
				predecessor[x+1][y] = {x, y};
				visited[x+1][y] = true;
			}
		}

		// left
		if (!visited[x][y-1]){
			if (x == dstX && y-1 == dstY){
				predecessor[x][y-1] = {x, y};
				break;
			}else if (map[x][y-1] != -1){
				que.push({x, y-1});
				predecessor[x][y-1] = {x, y};
				visited[x][y-1] = true;
			}
		}

		// up
		if (!visited[x-1][y]){
			if (x-1 == dstX && y == dstY){
				predecessor[x - 1][y] = {x, y};
				break;
			}else if (map[x-1][y] != -1){
				que.push({x-1, y});
				predecessor[x-1][y] = {x, y};
				visited[x-1][y] = true;
			}
		}

	}

    // find the path by the predecessors recorded
	tuple<int, int> prev = predecessor[dstX][dstY];
	int prevX = get<0>(prev), prevY = get<1>(prev);
	int curX = dstX, curY = dstY;
	this->bfsFindPath = !(get<0>(prev) == 0 && get<1>(prev) == 0);

	// if it is unable to find a path, stay at current position
	if (!this->bfsFindPath)
		return path;

    path.push({dstX, dstY});
	while (!(prevX == startX && prevY == startY)){
        path.push({prevX, prevY});
		prev = predecessor[prevX][prevY];
		prevX = get<0>(prev);
		prevY = get<1>(prev);
	}
	return path;

}



void Snake::markBodyPosition(vector<vector<int>> &map)
{
	queue<tuple<int, int>> temp;
	int x = 0, y = 0;
	while (!position.empty()){
		temp.push(position.front());
		x = get<0>(position.front());
		y = get<1>(position.front());
		map[x][y] = -1;
		position.pop();
	}
	while(!temp.empty()){
		position.push(temp.front());
		temp.pop();
	}
	
}



stack<tuple<int, int>> Snake::bfsVirtualTail(vector<vector<int>> &copyMap, stack<tuple<int, int>> &path) 
{
	stack<tuple<int, int>> copyPath = path;
	queue<tuple<int, int>> virtualSnake = position;
	int x, y, headx, heady;

	while (!copyPath.empty()){
		virtualSnake.pop();
		virtualSnake.push(copyPath.top());
		x = get<0>(virtualSnake.front());
		y = get<1>(virtualSnake.front());
		headx = get<0>(virtualSnake.back());
		heady = get<1>(virtualSnake.back());
		copyMap[headx][heady] = -1;
		copyMap[x][y] = 0;
		copyPath.pop();
	}

	stack<tuple<int, int>> pathToTail = bfsNext(copyMap, virtualSnake.back(), virtualSnake.front());
	return pathToTail;
}



bool Snake::arriveFood(tuple<int, int> &pos, vector<tuple<int, int>> &food)
{
	for (int i = 0; i < food.size(); i++){
		if (pos == food[i])
			return true;
	}
	return false;
}



bool Snake::collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map)
{
	//Check if the head is crashing into the obstacle
	if(map[std::get<0>(pos_head)][std::get<1>(pos_head)] == -1)
		return true;
	
	
	//Check if the head is crashing into itself, a.k.a. tails
	while(pos_body.size() != 0){
		if(std::get<0>(pos_body.front()) == std::get<0>(pos_head) and std::get<1>(pos_body.front()) == std::get<1>(pos_head))
			return true;
		pos_body.pop();
	}

	return false;
}