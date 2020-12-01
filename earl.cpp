#include <earl.h>

using namespace std;
using namespace ITC;


bool earl::set(){

}

bool earl::rebuild(const std::map<size_t, ITC::station> &stations){
    adj_earl.clear();
    for (auto i: stations){
        key_map.push_back(i.first);
        for (auto j: stations){
            adj_earl.insert({make_pair(i.first,j.first),-1});
        }
    }
    return (stations.empty()? false:true);
}

earl::earl(const std::map<size_t, ITC::station> &stations){
    for (auto i: stations)
        for (auto j: stations){
            adj_earl.insert({make_pair(i.first,j.first),-1});
    }
}
