#include "iostream"
using namespace std;
#include "ctime"

string customed_time() {
    time_t current = time(NULL);

    tm *ct = localtime(&current);
    string crt = to_string(ct->tm_hour) + ":" + to_string(ct->tm_min) + " "
                + to_string(ct->tm_mday) + "/" + to_string(ct->tm_mon+1) + "/"
                + to_string(ct->tm_year+1900);
    return crt;
}