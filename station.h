#pragma once

#include <check_input.h>

class ITC::station
{
private:
    static int sId;
    int id;

public:
    std::string name;
    int quantity;
    int quantity_in_work;
    int efficiency;

    int get_id() const;

    static int get_max_id();
    static void kill_sId();
    void change();


    station();
    station(bool);
    station(std::ifstream&, int);
    ~station();
};

std::ostream& operator<<(std::ostream&, const ITC::station&);
//аналогично pipe
std::ofstream& operator<<(std::ofstream&, const ITC::station&);
std::ifstream& operator>>(std::ifstream&, ITC::station&);

