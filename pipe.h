#pragma once

#include <check_input.h>

class ITC::pipe
{
private:
    static int sId;
    int id;

public:
    std::string name;
    double length;
    int diameter;
    bool under_repair = false;

    int get_id() const;
    static int get_max_id();
    static void kill_sId();
    void change();

    pipe();
    pipe(bool);
    pipe(std::ifstream&, int);
    ~pipe();
};


std::ostream& operator<<(std::ostream&, const ITC::pipe&);
std::ofstream& operator<<(std::ofstream&, const ITC::pipe&);
