#include <mymenu.h>
using namespace std;
using namespace ITC;

int main(){
    map<size_t,pipe>    mpipes;
    map<size_t,station> mstations;
    while(1){
        switch(menu()){
        case 0:
            return 0;
        case 1:
            mpipes.insert({pipe::get_max_id(),pipe()});
            break;
        case 2:
            mstations.insert({station::get_max_id(),station()});
            break;
        case 3: //see all
            for (auto v: mpipes)    cout << v.second;
            for (auto v: mstations) cout << v.second;
            break;
        case 4: //edit pipe
        {
            if(!edit(mpipes,check_input_int("ID"))) cout << "can't edit pipe\n";
            break;
        }
        case 5: //edit station
        {
            if(!edit(mstations,check_input_int("ID"))) cout << "can't edit station\n";
            break;
        }
        case 6: //select pipes
        {
            if(!selectPipes(mpipes)) cout<<"can't select any pipe\n";
            break;
        }
        case 7: //select stations
        {
            if(!selectStations(mstations)) cout<<"can't select any station\n";
            break;
        }
        case 8: //save
            fout(check_input_str("name of file")+".itc", mpipes, mstations);
            break;
        case 9: //load
            fin(check_input_str("name of file")+".itc", mpipes, mstations);
            break;
        case 10: //delete pipe
        {
            size_t id = check_input_int("ID");
            if (mpipes.find(id) != mpipes.end()) {
                mpipes.erase(id);
            } else {
                cout << "ID not found\n";
            }
            break;
        }
        case 11: //delete station
            size_t id = check_input_int("ID");
            if (mstations.find(id) != mstations.end()) {
                mstations.erase(id);
            } else {
                cout << "ID not found\n";
            }
            break;
        }
    }
}
