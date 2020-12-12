#pragma once

#include <station.h>
#include <pipe.h>
#include <set>


class web { //граф
private:
    std::map<std::pair<size_t,size_t>, int> adj_web;
    //std::map<size_t,size_t> key_map_id; //massid, idRC
    std::set<size_t> key_map_id;
    std::map<size_t,bool> used_pipes;

    std::map<size_t,size_t> sort_ts,colours, visited;

    bool dfs(size_t v,size_t ts);
    void cyclic (int v);
public:
    std::map<size_t,ITC::pipe>    pipes;
    std::map<size_t,ITC::station> stations;
    void edit();

    bool detach(size_t r, size_t c);
    void tie_in(size_t r, size_t c, int id);

    void delete_pipe(int r);
    void delete_pipe();
    void delete_st();

    bool rebuild();
    void print();
    bool topological_sort();

    bool fout(std::string);
    bool fin(std::string);

    web();
};

