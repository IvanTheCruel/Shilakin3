#include <web.h>
//shared_ptr
//две трубы на одном месте
//diam 1m 1.4m
using namespace std;

web::web(){}

void web::edit(){
    size_t idr,idc;
    print();
    while(ITC::check_ans("\nwant to connect(disconnect) stations?")){
        idr = ITC::check_input_st_int("row");
        idc = ITC::check_input_st_int("column");
        if (key_map_id.find(idr) != key_map_id.end() && key_map_id.find(idc) != key_map_id.end()) {
            if (idr != idc) {
                size_t id = ITC::check_input_st_int("id of pipe to connect with(-1 to disconnect)");
                if (id == -1) detach(idr, idc);
                else tie_in(idr,idc,id);
            } else cout<<"WARNING: station already connected to itself\n\n";
        } else cout<<"not found\n\n";
        print();
    }
    return;
}

bool web::detach(size_t r, size_t c){
    int temp_id = adj_web[make_pair(r,c)];
    if (temp_id != -1) {
        used_pipes[temp_id] = false;
        adj_web[make_pair(r,c)] = -1;
        adj_true[make_pair(r,c)] = false;
        return true;
    } else cout << "cannot detach anything\n";
    return false;
}

void web::tie_in(size_t idr, size_t idc, int id){
    if (used_pipes.find(id) != used_pipes.end()){
        if(adj_true[make_pair(idr,idc)]==false){
            adj_web[make_pair(idr,idc)] = id;
            adj_true[make_pair(idr,idc)]=true;
            used_pipes[id] = true;
        } else cout<<"WARNING: already connected\n\n";
    } else cout<<"WARNING: pipe not found\n\n";
}

bool web::rebuild(const std::map<size_t, ITC::station> &stations, const std::map<size_t, ITC::pipe> &pipes){
    adj_web.clear();
    for (auto i: stations){
        key_map_id.insert({i.first,i.first});
        for (auto j: stations){
            adj_web.emplace(make_pair(i.first,j.first),-1);
            adj_true.emplace(make_pair(i.first,j.first),false);
        }
    }
    for (auto i: pipes) {
        used_pipes.insert(make_pair(i.first, false));
    }

    return !stations.empty();
}

void web::print(){
    cout << "\t";
    for (auto i: key_map_id) {
        cout << " " << i.second << " \t";
    }
    for (auto r: key_map_id){
        cout << "\n\n" << r.second << "\t";
        for (auto c: key_map_id){
            int temp = adj_web[make_pair(r.second,c.second)];
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

bool web::topological_sort(){
    sort_ts.clear(); colours.clear(); visited.clear();
    vector<size_t> temp_key_map;
    for (auto c: key_map_id){
        int temp=0;
        colours.emplace(c.second,1);
        visited.emplace(c.second,0);
        for (auto r: key_map_id){
            //Проверить столбец вершины(как в неё можно попасть)
            temp += (adj_web[make_pair(r.second,c.second)]==-1? 0:1);
        }
        if (temp == 0) temp_key_map.push_back(c.second); //запомнить вершины корни
    }
    if(temp_key_map.size()!=0){
        for (auto v: temp_key_map) {
            dfs(v,key_map_id.size()+1);
        }
        cout << "\n";
        for (auto c: sort_ts)
            cout << "id" << c.first << "_" << c.second << "\n";
        return true;
    } else
        cout<< "cycle\n";
    return false;
}

bool web::dfs(size_t v, size_t ts){
    ts--;
    colours[v] = 2; //мы тут были
    visited[v]++;
    int temp;
    for (auto c: key_map_id) { //куда можем попасть смотрим
        temp = adj_web[make_pair(v,c.second)];
        if (temp != -1){ //ребро должно существовать чтобы попасть
            if (colours[c.second]!=3 && visited[c.second]!=2){ //цвет вершины не конец
                                                               //и не цикл
                if (colours[c.second] == 1) {                  //если еще не были
                    if (dfs(c.second, ts)) return true;           //идем туда
                }
                else { if (colours[c.second] == 2) return true; } //если были забили
            }
        }
        if (colours[v] == 3) return false; //конечная
        if (visited[v] == 2) return false; //были два раза
    }
    colours[v] = 3; //конечная
    sort_ts.emplace(v,ts);
    return false;
}



void web::delete_st(size_t id){
    for (auto i: key_map_id) {
        detach(i.second,id);
        detach(id, i.second);
        adj_web.erase(make_pair(i.second,id));
        adj_web.erase(make_pair(id,i.second));
        adj_true.erase(make_pair(i.second,id));
        adj_true.erase(make_pair(id,i.second));
    }
    key_map_id.erase(id);
}

