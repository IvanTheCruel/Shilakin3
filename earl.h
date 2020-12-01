#pragma once

#include <station.h>
#include <pipe.h>



class earl { //граф
private:
    std::map<std::pair<size_t,size_t>, int> adj_earl; //don't touch me
    std::map<size_t,size_t> key_map;
    std::map<size_t,bool> used_pipes;
public:
    bool set();
    bool rebuild(const std::map<size_t, ITC::station>&, const std::map<size_t, ITC::pipe>&);
    void print();
    void topological_sort();
    earl();
};


