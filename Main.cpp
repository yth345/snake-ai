/*
This file is written and released by the TA for the students to check the snake program and count the points gained.
It is a demo and reads only map 1-100
Students will be writing in Snake.cpp and Snake.h
*/


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstring>

#include "Snake.h"

using namespace std;

void loadmaps(vector<vector<int>> map[101]) {
	// vector<vector<int>> map[101]; //maps
	fstream file;
	char buffer[150];
	string fname;
	for (int i = 1; i < 101; i++) {
		if (i < 10)
			fname = "00" + to_string(i);
		else if (i < 100)
			fname = "0" + to_string(i);
		else
			fname = to_string(i);
		file.open("D:\\STUFF\\C\\Data_Structure\\final_project\\map\\maps\\map_" + fname, ios::in);
		if (!file) {
			cout << "no file" << endl;
		}
		else {
			do {
				vector<int> tempv;
				file.getline(buffer, sizeof(buffer));
				const char* d = " "; // segmentation basis
				char *row; // save the result of every segmentation
				row = strtok(buffer, d);
				while (row) {
					string s = row;
					int temp = stoi(s);
					tempv.push_back(temp);
					row = strtok(NULL, d);
				}
				map[i].push_back(tempv);
			} while (!file.eof());
		}
		file.close();
	}
}

// (every map, next map, position of the snake)
vector<vector<int>> generate_map(vector<vector<int>> map[101], int mapindex, queue<tuple<int, int>> snack) {
	tuple<int, int> position;
	int row, col;
	int flag3 = 0;
	int flag5 = 0;
	int flag7 = 0;
	int flagall = 0;

	// find the snacks on the map
	for (int m = 0; m < 50; m++) {
		for (int n = 0; n < 50; n++) {
			if (map[mapindex][m][n] == 1) {
				row = m;
				col = n;
				position = make_tuple(m, n);
			}
		}
	}

	// check if the snack is on the snake's body
	int flag = 0;
	queue<tuple<int, int>> tempsnack = snack;
	while (!tempsnack.empty() && flag == 0) {
		if (tempsnack.front() == position) {
			flag = 1;
		}
		tempsnack.pop();
	}
	if (flag == 0)
		return map[mapindex];
	else {
		//  3*3 find new snack
		for (int i = row - 1; i < row + 2; i++) {
			if (i > 0 && i < 49 && flag3 == 0) {
				for (int j = col - 1; j < col + 2; j++) {
					if (j > 0 && j < 49 && flag3 == 0) {
						tempsnack = snack;
						flag = 0;
						position = make_tuple(i, j);
						// compare every spot with the snake's body, found
						while (!tempsnack.empty() && flag == 0) {
							if (tempsnack.front() == position) {
								flag = 1;
							}
							tempsnack.pop();
						}
						if (flag == 0) {
							flag3 = 1; // find a new spot to put snack in 3*3
							row = i; // new spot index
							col = j;
							break;
						}
					}
					if (flag3 == 1)
						break;
				}
			}
			if (flag3 == 1) {
				break;
			}
		}
		if (flag3 == 1) {  // 3*3 found
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
		else if (flag3 == 0 && flag5 == 0) { // 5*5 find snack
			for (int i = row - 2; i < row + 3; i++) {
				if (i > 0 && i < 49 && flag5 == 0) {
					for (int j = col - 2; j < col + 3; j++) {
						if (j > 0 && j < 49 && flag5 == 0) {
							tempsnack = snack;
							flag = 0;
							position = make_tuple(i, j);
							// compare every spot with the snake's body, found
							while (!tempsnack.empty() && flag == 0) {
								if (tempsnack.front() == position) {
									flag = 1;
								}
								tempsnack.pop();
							}
							if (flag == 0) {
								flag5 = 1; // find a new spot to put snack in 5*5
								row = i;
								col = j;
								break;
							}
						}
						if (flag5 == 1)
							break;
					}
				}
				if (flag5 == 1) {
					break;
				}
			}
		}
		if (flag5 == 1) {  // 5*5 found
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
		else if (flag3 == 0 && flag5 == 0 && flagall == 0) {
			for (int i = 0; i < 50; i++) {
				if (i > 0 && i < 49 && flagall == 0) {
					for (int j = 0; j < 50; j++) {
						if (j > 0 && j < 49 && flagall == 0) {
							tempsnack = snack;
							flag = 0;
							position = make_tuple(i, j);
							// compare every spot with the snake's body, found
							while (!tempsnack.empty() && flag == 0) {
								if (tempsnack.front() == position) {
									flag = 1;
								}
								tempsnack.pop();
							}
							if (flag == 0) {
								flag5 = 1; // find a new spot to put snack in 5*5
								row = i;
								col = j;
								break;
							}
						}
						if (flagall == 1)
							break;
					}
				}
				if (flagall == 1) {
					break;
				}
			}
		}
		if (flagall == 1) {
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
	}
	return map[mapindex];
}

queue<tuple<int, int>> get_start_position() {
	queue<tuple<int, int>> re;

	tuple<int, int> pos1(1, 1);
	tuple<int, int> pos2(1, 2);
	tuple<int, int> pos3(1, 3);
	tuple<int, int> pos4(1, 4);
	tuple<int, int> pos5(1, 5);

	re.push(pos1);
	re.push(pos2);
	re.push(pos3);
	re.push(pos4);
	re.push(pos5);

	return re;
}

vector<vector<int>> get_map() {
	vector<vector<int>> re;

	return re;
}
//
//vector<vector<int>> generate_map(vector<vector<int>> map[], int mapindex, queue<tuple<int, int>> snack) {
//	return map[mapindex];
//}

int main(int argc, char *argv[]) {
	queue<tuple<int, int>> ori_pos;
	queue<tuple<int, int>> new_pos = get_start_position();

	Snake snake(new_pos);

	/*///
#pragma region TmpMap
	vector<vector<int>> v1 = {
		{-1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1,  0,  0,  0,  0,  1,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1}
	};

	vector<vector<int>> v2 = {
		{-1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1,  0,  0,  0,  0,  0,  0,  2, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1}
	};

	vector<vector<int>> v3 = {
		{-1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  1,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1}
	};

#pragma endregion
	vector<vector<int>> whole_map[3] = { v1, v2, v3 };
	///*/

	vector<vector<int>> whole_map[101]; // 1~100 stores 100 maps
	loadmaps(whole_map); // read the maps

	int cur_map_index = 1;
	vector<vector<int>> map = generate_map(whole_map, cur_map_index, new_pos);

	int step_limit = 10000;
	int point = 0;
	cout << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << point << "\n";

	for (int i = 0; i < step_limit; i++) {
		ori_pos = new_pos;
		new_pos = snake.nextPosition(map);

		int new_head_x = get<0>(new_pos.back());
		int new_head_y = get<1>(new_pos.back());
		cout << i << ": " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << map[new_head_x][new_head_y] << "$" << point << "\n";

		// Walk one step
		int one_step_limit = 1;
		one_step_limit -= abs(get<0>(ori_pos.back()) - new_head_x);
		one_step_limit -= abs(get<1>(ori_pos.back()) - new_head_y);
		if (one_step_limit != 0) {
			cout << argv[1] << " A: Invalid step... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
			break;
		}

		// Hit wall
		if (map[new_head_x][new_head_y] == -1) {
			cout << argv[1] << " B: GAME OVER! Hit wall... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
			break;
		}

		// Hit self
		queue<tuple<int, int>> tmp_queue = new_pos;
		bool ifGameOver = false;
		for (int i = 0; i < new_pos.size() - 1; i++) {
			if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y) {
				cout << argv[1] << " C: GAME OVER! Hit yourself... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
				ifGameOver = true;
				break;
			}
			tmp_queue.pop();
		}
		if(ifGameOver)
			break;
		// Check teleport
		// TBD...

		// Count point and check eat longer
		if (map[new_head_x][new_head_y] > 0) {
			if (new_pos.size() != ori_pos.size() + 1) {
				cout << argv[1] << " D: Invalid eat length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
				break;
			}

			point += map[new_head_x][new_head_y];
			map = generate_map(whole_map, ++cur_map_index, new_pos);
		}
		else {
			if (new_pos.size() != ori_pos.size()) {
				cout << argv[1]<< " E: Invalid length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
				break;
			}
		}
		if(cur_map_index > 100) {
			break;
		}
	}
	cout << argv[1] << " | Final: " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "$" << point << "\n";

	system("pause");
	return 0;
}
