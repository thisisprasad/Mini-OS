#include<iostream>
#include<conio.h>
//  #include
using namespace std;

//  Defining structure for process
struct Process{
    int id;
    int ttl;
    int tll;
    int ttc;
    int llc;
    //  int pc; //  Not required.
};

init_process(struct Process &p, int pid, int ttl, int tll)
{
    cout<<"Initializing process"<<endl; getch();
    p.id = pid;
    p.ttl = ttl;
    p.tll = tll;
}

struct PCB{
//  Nothing here.
};
