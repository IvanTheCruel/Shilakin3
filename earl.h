#pragma once

#include <station.h>
#include <pipe.h>



class earl { //граф
private:
    std::map<std::pair<size_t,size_t>, int> adj_earl;
    std::map<size_t,size_t> key_map; //massid, idRC
    std::map<size_t,bool> used_pipes;

    size_t ts;
    std::map<size_t,size_t> sort_ts,colours, visited;

    bool dfss(size_t v);
    void cyclic (int v);
public:
    bool set();
    bool detach(size_t r, size_t c);
    bool rebuild(const std::map<size_t, ITC::station>&, const std::map<size_t, ITC::pipe>&);
    void print();
    bool topological_sort();
    earl();
};


