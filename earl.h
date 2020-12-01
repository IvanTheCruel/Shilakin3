#pragma once

#include <station.h>
#include <pipe.h>

class ITC::earl { //граф
private:
    std::map<std::pair<size_t,size_t>, size_t> adj_earl; //don't touch me
    std::vector<size_t> key_map;
public:
    bool set();
    bool rebuild(const std::map<size_t, ITC::station>&);
    earl();
    earl(const std::map<size_t, ITC::station> &stations);
};
