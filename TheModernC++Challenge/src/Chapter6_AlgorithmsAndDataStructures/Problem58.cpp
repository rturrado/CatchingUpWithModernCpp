#include <iostream>  // cout

// The shortest path between two nodes
//
// Write a program that, given a network of nodes and the distances between them,
// computes and displays the shortest distance from a specified node to all the others,
// as well as the path between the start and end node.
//
// As input, consider the following undirected graph:
//
//     [A, B] = 7, [A, C] = 9, [A, F] = 14
//     [B, C] = 10, [B, D] = 14
//     [C, D] = 11, [C, F] = 2
//     [D, E] = 6
//     [E, F] = 9
//
// The program output for this graph should be the following:
//
// A -> A : 0     A
// A -> B : 7     A -> B
// A -> C : 9     A -> C
// A -> D : 20    A -> C -> D
// A -> E : 20    A -> C -> F -> E
// A -> F : 11    A -> C -> F
void problem_58_main()
{
    std::cout << "\n";
}
