#include "Process.h"

Process::Process(int id, int priority, int n)
{
    this->id = id;
    this->priority = priority;
    this->progress = 0;
    std::pair<int, int> o(150, 150);
    this->flyeye = new FlyEye(100, n, 0, sf::Color::White, o);
    
    this->window = new sf::RenderWindow(sf::VideoMode(300, 300), "Process " + std::to_string(this->id) + " [" + std::to_string(this->flyeye->getV()) +"]");
    this->window->setPosition(sf::Vector2i((id*350)%(350*3), 350*int(id/3)));

    // Compute coords
    this->compute_vertex_coords();
}

void Process::compute_vertex_coords()
{
    // Retrieve values
    int v = this->flyeye->getV();
    std::vector<std::pair<int, int>> e = this->flyeye->getE();
    double r = flyeye->getR();
    double t = flyeye->getT();
    sf::Color c = flyeye->getC();
    std::pair<int, int> o = flyeye->getO();
    double t_in = 2*M_PI/v;
    for (int i = 0; i < v; ++i)
    {
        std::pair<double, double> vertex_coords(r*cos(i*t_in + t) + o.first, -r*sin(i*t_in + t) + o.second);
        this->vertices_coords.push_back(vertex_coords);
    }
}

bool Process::isOver()
{
    return this->progress >= this->flyeye->getE().size();
}

void Process::run()
{
    if (this->isOver()) return;
    sf::Vertex l[2];

    // Current edge
    std::pair<int, int> edge = this->flyeye->getE()[this->progress];
    l[0].position = sf::Vector2f(vertices_coords[edge.first].first, vertices_coords[edge.first].second);
    l[0].color = sf::Color::White;
    l[1].position = sf::Vector2f(vertices_coords[edge.second].first, vertices_coords[edge.second].second);
    l[1].color = sf::Color::White;
    this->window->draw(l, 2, sf::Lines);
    this->window->display();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    this->progress ++;
    if (this->isOver())
    {
        this->window->setTitle("COMPLETED [" + std::to_string(this->flyeye->getV()) + "]");
        this->window->display();
    }
}

void Process::print()
{
    std::cout   << "{Process | id:" << this->id 
                << ", priority:" << this->priority 
                << ", progress:" << this->progress 
                << ", total verices: " << this->flyeye->getV() 
                << ", total work: " << this->flyeye->getE().size()
                << "}\n";
}