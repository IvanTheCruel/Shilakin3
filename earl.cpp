#include <earl.h>

using namespace std;

earl::earl(){}



bool earl::set(){
    size_t idr,idc;
    bool changed = false;
    print();
    while(ITC::check_ans("\nwant to (dis)connect stations?")){
        idr = ITC::check_input_st_int("row");
        idc = ITC::check_input_st_int("column");
        if (key_map.find(idr) != key_map.end() && key_map.find(idc) != key_map.end()) {
            if (idr != idc) {
                size_t id = ITC::check_input_st_int("id of pipe to connect with(-1 to disconnect)");
                if (id == -1) detach(idr, idc);
                else if (used_pipes.find(id) != used_pipes.end()){
                    adj_earl[make_pair(idr,idc)] = id;
                    used_pipes[id] = true;
                    changed = true;
                } else cout<<"pipe not found\n";
            }
            else cout<<"WARNING: station already connected to itself\n";
        } else cout<<"not found\n";
        print();
    }
    return changed;
}

bool earl::detach(size_t r, size_t c){
    int temp_id = adj_earl[make_pair(r,c)];
    if (temp_id != -1) {
        used_pipes[temp_id] = false;
        adj_earl[make_pair(r,c)] = -1;
        return true;
    } else cout << "cannot detach anything\n";
    return false;
}

bool earl::rebuild(const std::map<size_t, ITC::station> &stations, const std::map<size_t, ITC::pipe> &pipes){
    adj_earl.clear();
    int k = 0;
    for (auto i: stations){
        key_map.insert({k++,i.first});
        for (auto j: stations){
//            if(i.first!=j.first)
            adj_earl.emplace(make_pair(i.first,j.first),-1);
//            else
//                adj_earl.emplace(make_pair(i.first,j.first),-2);
        }
    }
    k = 0;
    for (auto i: pipes) {
        used_pipes.insert(make_pair(i.first, false));
    }

//    adj_earl[make_pair(0,1)]=1;
//    adj_earl[make_pair(0,3)]=1;
//    adj_earl[make_pair(1,3)]=1;
    return (stations.empty()? false:true);
}

void earl::print(){
    cout << "\t";
    for (auto i: key_map) {
        cout << " " << i.second << " \t";
    }
    for (auto r: key_map){
        cout << "\n\n" << r.second << "\t";
        for (auto c: key_map){
            int temp = adj_earl[make_pair(r.second,c.second)];
            if (temp != -1)
                cout << temp << "\t";
            else
                cout << " - " << "\t";
        }
    }
    cout << "\nunused pipe id is: ";
    for (auto i: used_pipes){
        if(!i.second) cout << i.first << " ";
    }
    cout << "\n";
}

bool earl::topological_sort(){
    sort_ts.clear(); colours.clear(); visited.clear();
    ts=0; vector<size_t> temp_key_map;
    for (auto c: key_map){
        int temp=0;
        colours.emplace(c.second,1);
        visited.emplace(c.second,0);
        for (auto r: key_map){
            //Проверить столбец вершины(как в неё можно попасть)
            temp += (adj_earl[make_pair(r.second,c.second)]==-1? 0:1);
        }
        if (temp == 0) temp_key_map.push_back(c.second); //запомнить вершины корни
    }
    if(temp_key_map.size()!=0){
        for (auto v: temp_key_map) {
            dfss(v);
        }
        cout << "\n";
        for (auto c: sort_ts)
            cout << "id" << c.first << "_" << c.second << "\n";
        return true;
    } else
        cout<< "цикл\n";
    return false;
}

bool earl::dfss(size_t v){
    colours[v] = 2; //мы тут были
    visited[v]++;
    int temp;
    for (auto c: key_map) { //куда можем попасть смотрим
        temp = adj_earl[make_pair(v,c.second)];
        if (temp != -1){ //ребро должно существовать чтобы попасть
            if (colours[c.second]!=3 && visited[c.second]!=2){ //цвет вершины не конец
                                                               //и не цикл
                if (colours[c.second] == 1) {                  //если еще не были
                    if (dfss(c.second)) return true;           //идем туда
                }
                else { if (colours[c.second] == 2) return true; } //если были забили
            }
        }
        if (colours[v] == 3) return false; //конечная
        if (visited[v] == 2) return false; //были два раза
    }
    colours[v] = 3; //конечная
    sort_ts.emplace(v,ts++);
    return false;
}

