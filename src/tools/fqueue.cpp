#include "../db.h"
#include "../number.h"
#include "../path.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
    DB::connect();

    int tid = 0;
    if(argc == 2)
        tid = number(argv[1]);
    else
        cerr << "Usage: fqueue ID" << endl;
    if(!tid) return 1;

    DB::Result r = DB::query("SELECT 1 FROM featured_tracks WHERE track_id=$1", number(tid));
    if(!r.empty()){
        cerr << tid << ": already featured" << endl;
        return 1;
    }

    r = DB::query("SELECT title FROM tracks WHERE id=$1", number(tid));
    if(r.empty()){
        cerr << tid << ": track not found" << endl;
        return 1;
    }

    int n;
    string path = eqbeatsDir() + "/feature.queue";
    fstream queue(path.c_str(), ios::in | ios::out | ios::app);
    while(queue){
        queue >> n;
        queue.ignore(1024, '\n');
        if(n == tid){
            cerr << tid << ": already queued" << endl;
            queue.close();
            return 1;
        }
    }
    queue.clear();
    queue << tid << " " << r[0][0] << endl;
    queue.close();

    cout << "queued '" << r[0][0] << "'" << endl;

    DB::close();
    return 0;
}
