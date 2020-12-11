#pragma once

#include <station.h>
#include <pipe.h>



class web { //граф
private:
    std::map<std::pair<size_t,size_t>, int> adj_web;
    std::map<std::pair<size_t,size_t>, bool> adj_true;
    std::map<size_t,size_t> key_map_id; //massid, idRC
    std::map<size_t,bool> used_pipes;


    std::map<size_t,size_t> sort_ts,colours, visited;

    bool dfs(size_t v,size_t ts);
    void cyclic (int v);
public:
    void edit();

    bool detach(size_t r, size_t c);
    void tie_in(size_t r, size_t c, int id);

    void delete_pipe(int r);
    void delete_st(size_t id);

    bool rebuild(const std::map<size_t, ITC::station>&, const std::map<size_t, ITC::pipe>&);
    void print();
    bool topological_sort();

    web();
};


