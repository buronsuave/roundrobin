#ifndef PROCESS_H
#define PROCESS_H

#include "FlyEye.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>   

class Process
{
    public:
    Process(int id, int priority, int n);

    int id;
    int priority;
    int progress;

    FlyEye* flyeye;
    std::vector<std::pair<double, double>> vertices_coords;
    sf::RenderWindow* window;
    
    void run();
    void compute_vertex_coords();
    bool isOver();
    void print();
};

#endif