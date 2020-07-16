# snake-ai

## Overview
This is an end of term competition from course "Data Structures and Advanced Program Design" by NTU IM.  
The goal of the competition is to design an algorithm to control the snake in the game "Snake" and gain as many points as possible under limited steps. Map informations will be kept unknown by the TAs, therefore generating maps for testing is needed. Note that the maps will become more and more complex as you gain more points, e.g., the appearance of multiple foods, obstacles.

## Details
[Instructions](https://drive.google.com/file/d/16Chh00WymK9k5Ir9oLUZnB1sxjIpFqHT/view?usp=sharing) for the competition.

### Algorithm
In the beginning, looking for a shortest path to the food may be a good strategy, however, as the snake's body length grow longer, a shortest path would be likely to cause the snake to walk into a dead end. The reason behind this is that a shortest path often cuts off the spare space and results in a smaller room for the snake.

One way to solve the problem is to NOT walk the shortest path, in other words, walk longer paths. Nevertheless, finding a longest path is a NP-complete problem and finding an general longer but efficient path is no eaiser.

Therefore, I decided to work on another strategy--find tail. This strategy derived from the idea that a snake would never meet a dead end if it follows its tail.

## To-Do List
1. Visualize the outcome.
2. Provide codes to generate maps.
3. Optimize the algorithm, e.g., replace Breadth-First Search by A* Search to improve efficiency.
