# snake-ai

## Overview
This is an end of term competition from course "Data Structures and Advanced Program Design" by NTU IM.  
The goal of the competition is to design an algorithm to control the snake in the game "Snake" and gain as many points as possible under limited steps. Map informations will be kept unknown by the TAs, therefore generating maps for testing is needed. Note that the maps will become more and more complex as you gain more points, e.g., the appearance of multiple foods, obstacles.

## Details
[Instructions](https://drive.google.com/file/d/16Chh00WymK9k5Ir9oLUZnB1sxjIpFqHT/view?usp=sharing) for the competition.

### Snake
The position of the snake would be stored in `queue<tuple<int, int>>`. Of which, the last element in queue `queue.back()` represents the position of the head, and the first element in queue `queue.front()` represents the position of the tail.

After one unit of time, the snake would move one step in either direction (up, down, left, right), that is to say, `push` a `tuple` to the back of the queue and `pop` the first element.

<img src="https://github.com/yth345/-/blob/master/snake.jpg" width=500>

### Maps
Maps are two-dimensional vectors `vector<vector<int>>`. Maps may change sizes as you gain more points.  
Map informations:  
-1 : obstacles, if the snake's body appears on a obstacle, the game is over  
 0 : free space to move  
 1 : food, gets one point  
 2 : food, gets two points  

### Algorithm
In the beginning, looking for a shortest path to the food may be a good strategy, however, as the snake's body length grow longer, a shortest path would be likely to cause the snake to walk into a dead end.
initial status             | walk a shortest path      | walk a longer path
:-------------------------:|:-------------------------:|:-------------------------:
![](https://github.com/yth345/-/blob/master/path0.jpg) | ![](https://github.com/yth345/-/blob/master/path1.jpg) | ![](https://github.com/yth345/-/blob/master/path2.jpg)

One way to solve the problem is to NOT walk the shortest path, in other words, walk longer paths. Nevertheless, finding a longest path is a NP-complete problem and finding an general longer but efficient path is no eaiser.

Therefore, I decided to work on another strategy--find tail. This strategy derived from the idea that a snake would never meet a dead end if it follows its tail. If the snake can find its tail after eating the food, which means that eating the food won't make the snake stuck, then follow the path to the food directly. Otherwise, if the snake is unable to find its tail after eating the food or if it is unable to find a path to the food, then follow the path to its tail until the previous condition is fulfilled. If all of the above does not match the situation, meaning that the snake can neither find a path to the food nor its tail, walk in a ramdom valid direction.

To find out if the snake is able to find its tail after eating the food or not, once the snake finds a path to the food, it would send out a virtual snake to walk the current path and simulate the situation after eating the food.

The pseudocode would look like the following:

<img src="https://github.com/yth345/-/blob/master/pseudocode%20for%20snake.PNG" width=500>

In order to improve efficiency, I only search for paths when there are no current paths in record, so the exact code would be slightly different.

<img src="https://github.com/yth345/-/blob/master/pseudocode2.PNG" width=500>

## To-Do List
1. Visualize the outcome.
2. Provide codes to generate maps.
3. Optimize the algorithm, e.g., replace Breadth-First Search by A* Search to improve efficiency.
