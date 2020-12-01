#include <earl.h>

using namespace std;

earl::earl(){}

bool earl::set(){
    size_t idr,idc;
    bool changed = false;
    print();
    while(ITC::check_ans("want to connect stations?")){
        idr = ITC::check_input_st_int("row");
        idc = ITC::check_input_st_int("column");
        if (key_map.find(idr) != key_map.end() && key_map.find(idc) != key_map.end()) {
            if (idr != idc) {
                size_t id = ITC::check_input_st_int("id of pipe");
                if (used_pipes.find(id) != used_pipes.end()){
                    adj_earl[make_pair(idr,idc)] = id;
                    used_pipes[id] = true;
                    changed = true;
                } else cout<<"pipe not found\n";
            }
            else cout<<"station already connected to itself\n";
        } else cout<<"not found\n";
        print();
    }
    return changed;
}

bool earl::rebuild(const std::map<size_t, ITC::station> &stations, const std::map<size_t, ITC::pipe> &pipes){
    adj_earl.clear();
    int k = 0;
    for (auto i: stations){
        key_map.insert({k++,i.first});
        for (auto j: stations){
            adj_earl.emplace(make_pair(i.first,j.first),-1);
        }
    }
    k = 0;
    for (auto i: pipes) {
        used_pipes.insert(make_pair(i.first, false));
    }
    return (stations.empty()? false:true);
}

void earl::print(){
    cout << "\t";
    for (auto i: key_map) {
        cout << i.first << "\t";
    }
    for (auto i: key_map){
        cout << "\n" << i.first << "\t";
        for (auto j: key_map){
            cout << adj_earl[make_pair(i.first,j.first)] << "\t";
        }
    }
    cout << "\nunused pipe id is: ";
    for (auto i: used_pipes){
        if(!i.second) cout << i.first << " ";
    }
    cout << "\n";
}

void earl::topological_sort(){

}

