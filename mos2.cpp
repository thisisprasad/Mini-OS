//  #include<bits/stdc++.h>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#define INT_FRAME '0'
#define DATA_FRAME '1'
#define WORD_FRAME '2'
#define pb push_back
#include"proces.h"
//  #include"procss.h"

using namespace std;

void display_memory();
void allocatePTR();
bool compare();
void mos();
void resetPI();
void terminateProcess();
void terminateProcess(int );
bool isSet(bool );
void printInstructionFrameLen();
void ttcIncrement();
void ttcIncrement(int);
bool operandError();
int allocateWord(char );
bool check(int );
int charToInt();
void printPCB(int err);
int getValue(int );
int getRegister();
void storeInMemory(int , int );   ///  Stores in memory location ir[2,3](virtual).
void writeInFile(string );


//  Process *p;
struct Process p;
int pid;
int ptr;    //  PT register.
int ptrcnt = 0; //  page table entry counter
int pi = 0, ti = 0, si = 0;
int instrlen;   //  instruction length.
int instrframeno;
int frameaddr;
vector<int> instrframelen;  //  Stores the instruction length of the  frames.
/// This is necessary in case of multiple instruction frames.

int llc = 0;    //  Line-Limit-Counter
int ttc = 0;    //  Total-Time-Counter

char ir[4]; //  Seperating its declaration
int error = -1;   //  Initial
bool atleast = false;

int jobcnt=0;
char reg[4];
char r[4];
//  char ic[2];
short ic=0;   //  2-byte instruction-counter;
bool c;
bool toggle;
bool comp;
bool carry = false;
char mem[300][4]={'\0'};
//  int si=0;
char buff[40]={" "};
//  ifstream fin;
string s=" ";

void printPCB(int err){
    ofstream ferr;
    ferr.open("output.txt", std::ios::app);

    ferr<<"r: "<<r<<" ";
    ferr<<"ir: "<<ir<<" ";
    ferr<<"ic: "<<ic<<" ";
    ferr<<"c: "<<c<<" ";
    ferr<<"ptr: "<<ptr<<" ";
    ferr<<"ttl: "<<p.ttl<<" ";
    ferr<<"ttc: "<<ttc<<" ";
    ferr<<"tll: "<<p.tll<<" ";
    ferr<<"llc: "<<llc<<" ";
    ferr<<"em: "<<err<<" ";
}
int allocateWord(char ch)
{
    int temp = 0; //    temp %= 300;
    int wrd = temp; //  temp /= 10;
    while(!check(temp)){
        temp = (rand()+7)%300;
        wrd = temp;
        temp /= 10; //  For checking the page table entry.
    }

    cout<<"ir[2,3]: "<<ir[2]<<" "<<ir[3]<<endl;
    int pte = charToInt();
    cout<<"pte: "<<pte<<", ptr: "<<ptr<<endl; getch();
    pte /= 10;
    mem[ptr+pte][0] = WORD_FRAME;
    mem[ptr+pte][1] = wrd/100 + '0';
    mem[ptr+pte][2] = wrd/10 + '0';
    mem[ptr+pte][3] = wrd%10 + '0' + 7;
    return wrd+7;
}

void storeInMemory(int res, int ra)
{
    mem[ra][0] = res/1000 + '0';
    mem[ra][1] = (res/100)%10 + '0';
    mem[ra][2] = (res/10)%10 + '0';
    mem[ra][3] = res%10 + '0';

    cout<<"mem[0,1,2,3]: "<<mem[ra][0]<<" "<<mem[ra][1]<<" "<<mem[ra][2]<<" "<<mem[ra][3]<<endl; getch();
}

int getRegister()
{
    int a = 0;
    a += (r[0]-'0')*1000 + (r[1]-'0')*100 + (r[2]-'0')*10 + (r[3]-'0');
    return a;
}

int getValue(int ra)
{
    int a = 0;
    a += (mem[ra][0]-'0')*1000 + (mem[ra][1]-'0')*100 + (mem[ra][2]-'0')*10 + (mem[ra][3]-'0');
    return a;
//    for(int i = 0; i < 4; i++){
//        a += (mem[ra][i]-'0')*
//    }
}

void writeInFile(string s)
{
    ofstream ferr;
    ferr.open("output.txt", std::ios::app);

    ferr<<"error: "<<s<<"\n";
    cout<<"s: "<<s<<endl; getch();
}

bool operandError()
{
    if(!(ir[2]>='0' && ir[2]<='9') || !(ir[3]>='0' && ir[3]<='9')){
        pi = 2;
        mos();
        return true;
    }
    return false;
}

void ttcIncrement()
{
    ttc++;
    if(ttc > p.ttl){
            ti = 2;
            mos();
//        terminateProcess(3);
    }
}
void ttcIncrement(int inc)
{
    ttc += 2;
    if(ttc > p.ttl){
            ti = 2;
            mos();
//        terminateProcess(3);
    }
}

void printInstructionFrameLen()
{
    cout<<instrframelen.size()<<endl;
    for(int i = 0; i < instrframelen.size(); i++){
        cout<<instrframelen[i]<<" ";
    }
    cout<<endl;
    getch();
}

void debug(string str, bool get=false)
{
    cout<<str;
    if(get) getch();
}

bool isSet(bool f)
{
    if(f) return true;
    return false;
}

void resetPI(){
    pi = 0;
}

void terminateProcess()
{
    cout<<"Inside terminate()"<<endl;
    cout<<"Terminated successfully"<<endl;
    ofstream ferr;
    ferr.open("output.txt", std::ios::app);
    ferr<<"terminated succ. \n\n\n";
    toggle = true;  //  set toggle. Due to error.
}

void terminateProcess(int err)
{
    error = err;
    atleast = true;
    cout<<"Inside overloaded terminateProcess(int )";
    toggle = true;  //  this is importatnt.
    ofstream ferr;
    ferr.open("output.txt", std::ios::app);
    switch(err){
    case 0:
        ferr<<"Terminated successfully\n";
        cout<<"terminated succ. \n\n\n";
        break;
    case 1:
        cout<<"Out of data error\n";
        ferr<<"Out of data error\n";
        break;

    case 2:
        cout<<"Line limit execeeded error\n";
        ferr<<"Line limit execeeded error\n";
        break;

    case 3:
        cout<<"Time limit execeeded\n";
        ferr<<"Time limit execeeded\n";
        break;

    case 4:
        cout<<"Opcode error\n";
        ferr<<"Opcode error\n";
        break;

    case 5:
        cout<<"Operand error\n";
        ferr<<"Operand error\n";
        break;

    case 6:
        cout<<"Invalid page fault\n";
        ferr<<"Invalid page fault\n";
        break;

    default:
        cout<<"Some error in error"<<endl; getch();
    }
//  Print the PCB
    printPCB(err);

    ferr<<"\n\n";
}

//void allocateFrame()
//{
//    int temp;
//    mem[ptr+ptrcnt][0]=id/10;
//    mem[ptr+ptrcnt][1]=id%10;
//
//    while(!check(temp))
//    {
//        temp=rand()%30;
//    }
//    mem[ptrcnt][2]=temp/10;
//    mem[ptrcnt][3]=temp%10;
//
//    frameBaseAddr=temp*10;
//}

void allocatePTR()
{
    //  ptr = rand(); cout<<"ptr(before mod): "<<ptr<<endl;
    ptr = rand()%30;
    ptr *= 10;
    cout<<"ptr : "<<ptr<<endl; getch();
    for(int i = 0; i <= 9; i++){
        mem[ptr+i][0] = '#';
        mem[ptr+i][1] = '#';
        mem[ptr+i][2] = '#';
        mem[ptr+i][3] = '#';
    }
}

int charToInt()
{
    int a = ir[2]-'0';
    int b = ir[3]-'0';
    return (int)(a*10+b);
}

int charToInt(char a, char b)
{
    int x = a-'0';
    int y = b-'0';
    return (x*100+y*10);
}


bool check(int temp)
{
    int i=0;
    int temp2=0;
    for(i=ptr;i<=ptr+9;i++)
    {
        temp2=charToInt(mem[i][2],mem[i][3]);
        temp2 /= 10;
        if(temp==temp2 or temp==ptr/10) return false;
    }
    return true;
}


int addressMap(int va)
{
    int pte = ptr + va/10;
    if(mem[pte][0]!=INT_FRAME && mem[pte][0]!=DATA_FRAME && mem[pte][0]!=WORD_FRAME){
        pi = 3; //  Valid page-faut which occurs in dataframe only.
    }
    int ra = charToInt(mem[pte][2], mem[pte][3]) + va%10;
    return ra;
}
int addressMap(int va, bool flag)
{
    if(flag == false){
        return addressMap(va);
    }

    int pte = ptr + va/10 + instrframeno;
        if(mem[pte][0]!=INT_FRAME && mem[pte][0]!=DATA_FRAME && mem[pte][0]!=WORD_FRAME){//    Most probably this will not be executed.
        pi = 3; //  Valid page-faut which occurs in dataframe only.
    }
    int ra = charToInt(mem[pte][2], mem[pte][3]) + va%10;
    return ra;
}

int allocateFrame(char frame)
{
    int temp;
    int pte = ptr + ptrcnt; ptrcnt = (ptrcnt+1)%10;   //  within0-9 only.
//  Determine the type of the frame.
    if(frame == INT_FRAME){ //  Instruction frame
        temp = temp%30;
        while(!check(temp)){
            temp = rand()%30;
            temp = rand()%30;
        }
        cout<<"Frame allocated(instruction) = "<<temp<<endl;
    }
    else{   //  data frame
        temp = temp%30;
        while(!check(temp)){
            temp = rand()%30;
        }
    }
    return temp;
//        mem[pte][0]=id/10;
//        mem[pte][1]=id%10;
//        mem[ptrcnt][2]=temp/10;
//        mem[ptrcnt][3]=temp%10;

    //  frameBaseAddr=temp*10;
}

void exec_usr_prog()
{
    cout<<"inside exec_usr_prog()"<<endl;
    //  debug("inside exec+usr_prog", true);
    int i,temp=0;
    //while(1)
    //  {
        int instraddr = addressMap(ic, true); //  got the base address of instruction frame.
        cout<<"instraddr: "<<instraddr<<endl;
        for(i = 0; i < 4; i++){
            ir[i] = mem[instraddr][i];
        }
        ic++;
    /// Check here only operandd error.
        if(ir[0]!='H' && operandError()){
            //  terminateProcess(5);
            return ;
        }

        cout<<"ic : "<<ic<<endl;
        cout<<"ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
        if(ir[0]=='G' && ir[1]=='D'){
            if(s[0]=='$' && s[1]=='E' && s[2]=='N' && s[3]=='D'){
            //  Out of Data error
                cout<<"Out-of-Data error"<<endl; getch();
                terminateProcess(1);
                return ;
            }

            si = 1;
            int va = charToInt();
            cout<<"va(mos): "<<va<<endl; getch();
            int ra = addressMap(va);    //  pi will be set or reset!!
            mos();// ttc++;
            ttcIncrement();
            if(isSet(toggle)) return ;
            if(pi == 3){
                resetPI();
                //  ic--;
                mos();
                ttcIncrement();
                //ttc++;
            }
        }
        else if(ir[0]=='P' && ir[1]=='D'){
            //cout<<"here...................\n";
            cout<<"PD here"<<endl; getch();
            si = 2;
            mos();
            ttcIncrement();

            //ttc++;
        }
        else if(ir[0]=='L' && ir[1]=='R')
        {
            cout<<"in LR\n";
            int va = charToInt();
            int ra = addressMap(va);
            int offset = va%10;
        //  invalid page-fault
            if(pi == 3){
                resetPI();
                terminateProcess(6);
                return ;
            }

        //  We are doing an assumption. So not using the below code.
//            int id;
//        //  Check whther it is a number.
//            for(id = 0; id < s.length(); id++){
//                if(!(s[id]>='0' && s[id]<='9')){
//                    break;
//                }
//            }
//            if(id == s.length()){
//            //  load in register.
//                r[0] = r[1] = r[2] = r[3] = '0';
//                if(s.length() == 1) r[3] = s[0];
//                else if(s.length() == 2){
//                    r[2] = s[0]; r[3] = s[1];
//                }
//                else if(s.length() == 3){
//                    r[1] = s[0]; r[2] = s[1]; r[3] = s[3];
//                }
//                else{
//                    for(int i = 0; i < 4; i++){
//                        r[i] = s[i];
//                    }
//                }
//                return ;
//            }

        //  Now we have memory location
            for(i=0;i<4;i++)
            {
                r[i]=mem[ra+offset][i];
                //mem[temp][i]=' ';
            }
            cout<<"r : "<<r<<endl; getch();
            ttcIncrement();
            //ttc++;
        }
        else if(ir[0]=='S' && ir[1]=='R')
        {
            cout<<"in SR\n";
            //  cout<<"Before charTooInt in SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
            int va = charToInt();
            //  cout<<"After cti SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
            cout<<"va(mos): "<<va<<endl; getch();
            //  cout<<"Before addrmap in SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
            int ra = addressMap(va);
            //  cout<<"aft addrmap in SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
            //  if(isSet(toggle)) return ;  //  This might not occur
            if(pi == 3){
                cout<<"Page fault for SR occured"<<endl; getch();
                resetPI();
                //  cout<<"before allocate in SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
                int wrd = allocateWord(WORD_FRAME);
                //  while(wrd <= 4) wrd = allocateWord(WORD_FRAME);
                //  if(wrd <= 4) wrd += 7;
                //  cout<<"aft alloc in SR ir[0,1, 2, 3]: "<<ir[0]<<" "<<ir[1]<<" "<<ir[2]<<" "<<ir[3]<<endl; getch();
                cout<<"wrd: "<<wrd<<endl; getch();
                for(int i = 0; i < 4; i++){
                    mem[wrd][i] = r[i];
                }
                ttcIncrement();
            }
            else{
                for(int i = 0; i < 4; i++){
                    mem[ra][i] = r[i];
                }
            }
//            for(i=0;i<4;i++)
//            {
//                mem[temp][i]=r[i];
//            }
            ttcIncrement();
            //ttc++;
            display_memory();
        }
        else if(ir[0]=='C' && ir[1]=='R')
        {
            if(compare()) comp = true;
            else comp = false;
            if(pi == 3){
                resetPI();
                terminateProcess(6);
                return ;
            }
            ttcIncrement();
            //ttc++;
        }
        else if(ir[0]=='B' && ir[1]=='T')
        {
            int va;
            if(comp){
                va = charToInt();
                int frameno = va/10;
                int offset = va%10;
                int ra = addressMap(va);
                ic = offset;
                instrframeno = frameno;
                frameaddr = ra/10;
            }
            ttcIncrement();
            //ttc++;
        }
        else if(ir[0]=='A' && ir[1]=='D'){  //  Addition instruction
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = a + b;
            if(res > 9999){
            //  Overflow has occured.
                carry = true;
                writeInFile("Addition overflow occurred");
                carry = false;
            }
        //  Store this result on memory ir[2,3]
            storeInMemory(res, ra);
        }
        else if(ir[0]=='S' && ir[1]=='B'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = b - a;
        //  Store this result on memory ir[2,3]
            storeInMemory(res, ra);
        }
        else if(ir[0]=='M' && ir[1]=='L'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = a*b;
            cout<<"In multiplication(res): "<<res<<endl; getch();
            if(res<=9999) storeInMemory(res, ra);
            else {
                int res1 = res/10000; storeInMemory(res1, ra);
                res1 = res%10000; storeInMemory(res1, ra+1);
            }
//            storeInMemory(res, ra);
//            storeInMemory(res/1000, ra+1);
        }
        else if(ir[0]=='D' && ir[1]=='V'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int quo = b/a;
            int rem = b%a;
            cout<<"In division(quo), rem: "<<quo<<" "<<rem<<endl; getch();
            storeInMemory(quo, ra);
            storeInMemory(rem, ra+1);
        }
        else if(ir[0]=='A' && ir[1]=='N'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = a & b;
            storeInMemory(res, ra);
        }
        else if(ir[0]=='O' && ir[1]=='R'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = (a|b);
            storeInMemory(res, ra);
        }
        else if(ir[0]=='X' && ir[1]=='R'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            int b = getRegister();
            int res = (a^b);
            storeInMemory(res, ra);
        }
        else if(ir[0]=='N' && ir[1]=='T'){
            int va = charToInt();
            int ra = addressMap(va);
        //  Handle invalid page-fault
            if(pi == 3){
                terminateProcess(6);
                return ;
            }

            int a = getValue(ra);
            //  int b = getRegister();
            int res = ~a;   //  2's complement
            storeInMemory(res, ra);
        }

        else if(ir[0]=='H'){
            //  std::ofstream outfile;
            ofstream outfile;

            outfile.open("output.txt", std::ios::app);
            outfile<<"\n\n\n";
            outfile.close();
            return;
        }
        else{
        //  Handle opcode or operand error.
//            if((ir[2]<='0' || ir[2]>='9') || (ir[3]<='0' || ir[3]>='9')){
//                pi = 2;
//                mos();
//                return ;
//            }
            pi = 1;
            mos();
        }
    //  }
}

void start_exec()
{
    //  ic[0]=0;ic[1]=0;
    //  ic = 0;
    cout<<"Inside start"<<endl; getch();
    exec_usr_prog();
    if(ic >= 10){
    /**
        End of the instruction frame. We must now take a new frame of instruction from page-table.
    */
        instrframeno++;
        ic = 0;
    }
}

//  ifstream fin;


void init_os()
{
    int i;
    cout<<"Initializing OS"<<endl; getch();
    instrlen = 0;
    for(i = 0; i < 4; i++){
        reg[i] = 0; ir[i] = 0;r[i]=0;
        //  if(i<2) ic[i] = 0;
    }
    ic = 0;
    toggle = false;
    comp = false;
    carry = false;
    c = false;
    //  mem[100][4] = {" "};
    for(int i = 0; i < 300; i++){
        for(int j = 0; j < 4; j++) mem[i][j] = 0;
    }

//    for(int i = 0; i < 40; i++){
//        buff[i] = 0;
//    }

    ti = 0; pi = 0;// si = 0;
    llc = 0; ttc = 0;
    toggle =  false; //  toggle flag set to false.
    comp = false;
    instrframeno = 0;
    instrframelen.clear();
    ptrcnt = 0;
}
void display_memory()
{
    int k=0,j=0;
        for(k = 0; k < 300; k++){
                cout<<"M["<<k<<"]"<<" : ";
                for(j = 0; j < 4; j++){
                    cout<<mem[k][j]<<" ";
                }
                cout<<endl;
            }
}

void read()
{
    cout<<"in read"<<endl<<"s = "<<s<<endl;
    int temp=0,i,j,k=0;
    //  ir[3]=0; temp = ir[2]-48;
    //  temp=charToInt();
    //  cout<<"ir[2,3]: "<<(int)ir[2]<<" " <<(int)ir[3]<<endl; getch();

    temp = temp*10;
    //  cout<<"temp : "<<temp<<endl;getch();
    //  getline(fin,buff);
    //  Don't access memory which is not allocated
    for(i = 0; i < 40 && i<s.length(); i++){
        buff[i] = s[i];
    }
    for(i = 0; i<40 && i < s.length(); i++){
        int row = (i)/4;
        int col = (i)%4;
        mem[frameaddr*10+row][col] = buff[i];

//        mem[temp+row][col] = buff[i];   //  No problem of accessing outOfBounds memory.
    }
    /*k=0;
    for(i=temp;i<=s.length()/4;i++)
    {
        for(j=0;j<4;j++)
        {
            mem[i][j]=buff[k];
            k++;
        }
    }*/

    display_memory();
//    for(i = 0, j = temp; i < s.length(), ; i+=4, j++){
//
//                mem[j][0] = s[i];
//                mem[j][1] = s[i+1];
//                mem[j][2] = s[i+2];
//                mem[j][3] = s[i+3];
//            }
//            temp+=10;
}

void write()
{
    int i, j;
    string str;
    cout<<"in write"<<endl;getch();
    //getch()
    //  ifstream fin;
    fstream fout;
    fout.open("prog2.txt", ios::in|ios::out);
    //  fin.open("prog.txt");
//    while(1){   //  This is causing problem.
//        getline(fout, str);
//        if(str[0]=='$' && str[1]=='E' && str[2]=='N' && str[3]=='D'){
//            break;
//        }
//    }

//  Actual logic begins from here!!!...
    int temp = charToInt();
    int dataframeaddr = addressMap(temp);   //  get the base address of the data-frame.
//  Check for invalid page-fault
    if(pi == 3){
        resetPI();
        terminateProcess(6);
        return ;
    }

    llc++;  //  increment LLC;
    if(llc > p.tll){
        terminateProcess(2);   //  Does not ensure that the process is terminated.
    //  Next instruction should not get executed. Return to the original loop.
        return ;
    }
    str = "";
    for(i = 0; i <= 9; i++){
        for(j = 0; j < 4; j++){
            str += mem[dataframeaddr+i][j];
        }
    }
    cout<<"dataframeaddr: "<<dataframeaddr<<endl;
    cout<<"str : "<<str<<endl; getch();
    std::ofstream outfile;

    cout<<"Writing in output file"<<endl; getch();
    outfile.open("output.txt", std::ios::app);
    //outfile<<"\n\n";
    outfile <<str;
    outfile<<"\n";
    //  outfile<<"\n";
    outfile.close();
    fout.close();
    //sfout<<"\n\n"<<str;
    //  fputs(str, fout);
}

void mos()
{
    bool pflag = false;
    if(ti == 0){
        if(pi == 3){    //  valid page-fault has occured.
            frameaddr = allocateFrame(DATA_FRAME);
            cout<<"Valid page fault has occured, frameaddr: "<<frameaddr<<endl; getch();
            cout<<"frameaddr: "<<frameaddr<<endl; getch();
            //  int pte = ptr+ptrcnt;
            int va = charToInt(); va /= 10;
            int pte = ptr + va;
            mem[pte][0] = DATA_FRAME;
            mem[pte][1] = frameaddr/100 + '0';
            mem[pte][2] = frameaddr/10 + '0';
            mem[pte][3] = frameaddr%10 + '0';
            //  ic--;   /   /This is causing the problem.
            cout<<"ti=0 and pi=3"<<endl; getch();
            pflag = true;
        }
        else if(pi == 1){
        //  Precede your instructions.
            terminateProcess(4);
            pflag = true;
        }
        else if(pi == 2){
        //  Precede your instruction.
            terminateProcess(5);
            pflag = true;
        }
        else{
            cout<<"No pi related error"<<endl; getch();
        }
        if(pflag) return ;  //  No need to execute si.

        if(si == 1){
            read();
            si = 0; //  reset si..
        }
        else if(si == 2){
            write();
            si = 0;
        }
        else if(si == 3){
            terminateProcess(0);
        }
   }
   else if(ti == 2){
       if(pi == 0){
            terminateProcess(3);
            return ;
       }

       if(pi == 1){
            terminateProcess(3);
            terminateProcess(4);
            pflag = true;
       }
       else if(pi == 2){
            terminateProcess(3);
            terminateProcess(5);
            pflag = true;
       }
       else if(pi == 3){
            terminateProcess(3);
            pflag = true;
       }
       if(pflag) return ;

        if(si == 1){
            terminateProcess(3);
        }
        else if(si == 2){
            write();
            terminateProcess(3);
        }
        else if(si == 3){
            terminateProcess(0);
        }
   }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    switch(si)
//    {
//        case 1 : //cout<<"========================================="<<endl;
//                 read();
//                 si=0;
//                 //exec_usr_prog();
//                 break;
//
//        case 2 : cout<<"========================================="<<endl;
//                 write();
//                 si=0;
//                 //exec_usr_prog();
//                 break;
//    }
}

/*
void mos(int ra)
{
    bool pflag = false;
   if(ti == 0){
        if(pi == 3){    //  valid page-fault has occured.
            int frameaddr = allocateFrame(DATA_FRAME);
            //  cout<<"Valid page fault has occured, frameaddr: "<<frameaddr<<endl; getch();
            int pte = ptr+ptrcnt;
            mem[pte][0] = DATA_FRAME;
            mem[pte][1] = frameaddr/100 + '0';
            mem[pte][2] = frameaddr/10 + '0';
            mem[pte][3] = frameaddr%10 + '0';
            ic--;
            cout<<"ti= and pi=3"<<endl; getch();
            pflag = true;
        }
        else if(pi == 1){
        //  Precede your instructions.
            pflag = true;
        }
        else if(pi == 2){
        //  Precede your instruction.
            pflag = true;
        }
        if(pflag) return ;  //  No need to execute si.

        if(si == 1){
            read();
            si = 0; //  reset si..
        }
        else if(si == 2){
            write();
            si = 0;
        }
        else if(si == 3){
            terminateProcess();
        }
   }
   else if(ti == 2){
       if(pi == 1){}
       else if(pi == 2){}
       else if(pi == 3){}

   }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    switch(si)
//    {
//        case 1 : //cout<<"========================================="<<endl;
//                 read();
//                 si=0;
//                 //exec_usr_prog();
//                 break;
//
//        case 2 : cout<<"========================================="<<endl;
//                 write();
//                 si=0;
//                 //exec_usr_prog();
//                 break;
//    }
}

*/
bool compare()
{
    int i=0,flag=0,temp=0;
    int va = charToInt();
    int ra = addressMap(va);
    if(pi == 3){
        //  resetPI();
        //  terminateProcess(6);
        return false;
    }

    int offset = va%10;
    for(i=0;i<4;i++)
    {
        if(r[i]!=mem[ra+offset][i]) flag=1;
    }
    if(flag==0) return true;
    else return false;
}



int getHeader(int a)
{
    int x, y, z, q;
    switch(a){
    case 0:
        x = (buff[4]-'0')*1000;
        y = (buff[5]-'0')*100;
        z = (buff[6]-'0')*10;
        q = (buff[7]-'0');

        return (x+y+z+q);
        break;

    case 1:
        x = (buff[8]-'0')*1000;
        y = (buff[9]-'0')*100;
        z = (buff[10]-'0')*10;
        q = (buff[11]-'0');

        return (x+y+z+q);
        break;

    case 2:
        x = (buff[12]-'0')*1000;
        y = (buff[13]-'0')*100;
        z = (buff[14]-'0')*10;
        q = (buff[15]-'0');

        return (x+y+z+q);
        break;
    }
}

void load()
{
    ifstream fin;
    //cout<<"inside load";
    int i=0,j=0,k=0;
    fin.open("prog.txt");
    string sdata;

    bool flag = false;  //  For checking the end of the card.
    bool flag2 = false;
    while(EOF){

        //  if(flag2)   //  The previous job is to be terminated.


        getline(fin, s);

        if(s == ""){
        //  Now we have to stop.
            break;  //  come out.
        }

        for(i = 0; i < s.length(); i++){
            if(!(s[i]>='0' && s[i]<='9')) break;
        }
        if(i == s.length()){
            while(s.length() != 4){
                s = "0" + s;
            }
            cout<<"s(numeral string): "<<s<<endl; getch();
        } //  Consists only of numbers


        for(i = 0; i < s.length(); i++){
            buff[i] = s[i];
        }

        if(buff[0]=='$'){
            if(buff[1]=='A' && buff[2]=='M' && buff[3]=='J')
            {
                if((error!=-1) && !atleast){
                    terminateProcess(0);
                }
                cout<<"\n\n";
                init_os(); flag = false; allocatePTR();
                int pid = getHeader(0);
                int ttl = getHeader(1);
                int tll = getHeader(2);
                int entry = ptr + ptrcnt;
                //  p = new Process(pid, ttl ,tll);
                init_process(p, pid, ttl, tll);

            //  This is new job. init();
            }
            else if(buff[1]=='D' && buff[2]=='T' && buff[3]=='A'){
            //  this is data. start execution. do notihing here
                while(1)
                {
                    getline(fin, s);
                ///////////////////////////////////////////////////////////Numeral adjustment
                    for(i = 0; i < s.length(); i++){
                        if(!(s[i]>='0' && s[i]<='9')) break;
                    }
                    if(i == s.length()){
                        while(s.length() != 4){
                            s = "0" + s;
                        }
                        cout<<"s(numeral string): "<<s<<endl; getch();
                    } //  Consists only of numbers
                ///////////////////////////////////////////////////////

                    cout<<"DTA s = "<<s<<endl; getch();
                    if(s[0]=='$' && s[1]=='E' && s[2]=='N' && s[3]=='D'){
                        //  debug("This is $END. Should exit now!!");
                        cout<<"This is $END"<<endl;
//                        char ch = mem[frameaddr+ic][0];
//                        if(ch == 'G'){
//                            flag2 = true;
//                            cout<<"GD with END"<<endl; getch();
//                            terminateProcess(1);
//                        }
                        flag = true;
                        break;
                    }
                    if(isSet(toggle)){
                        flag2 = true; break;
                    }
                    start_exec();
                }
                if(flag2) continue; //  toggle is set.
                printInstructionFrameLen();
                while((ic < instrframelen[instrframeno]) && (instrframeno < instrframelen.size())){
                    cout<<"While after $END"<<endl; getch();
                    if(isSet(toggle)){
                        flag = true; break;
                    }
                    start_exec();
                }
                if(flag2) continue; //  Reached end.

                if(!isSet(toggle)){
                    cout<<"Terminated successfully"<<endl; getch();
                    terminateProcess(0);
                }

            }
            else if(buff[1]=='E' && buff[2]=='N' && buff[3]=='D'){
            //  End of job.
                cout<<"The else if block."<<endl;
                //  break;
//                continue;
            }
        }
        else{
        //  This is an instruction set. Allocate a frame.
            instrlen = s.length()/4 + 1;    //  This is applicable only in case of single instruction frame.
                                            //  In other cases it won't work. Isn't used anymore.
            instrframelen.push_back(instrlen);
            int frameaddr = allocateFrame(INT_FRAME);
            cout<<endl;
            int pte = ptr + ptrcnt-1;
            mem[pte][0] = INT_FRAME;
            char ch = frameaddr/100 + '0'; mem[pte][1] = ch;
            ch = frameaddr/10 + '0'; mem[pte][2] = ch;
            ch = frameaddr%10 + '0'; mem[pte][3] = ch;
        //  Entry done in page table.
            frameaddr *= 10;
            for(i = 0; i < s.length(); i+=4){
                mem[frameaddr][0] = s[i];
                mem[frameaddr][1] = s[i+1];
                mem[frameaddr][2] = s[i+2];
                mem[frameaddr][3] = s[i+3];
                frameaddr++;
            }

//            for(i = 0, j = 0; i < s.length(); i+=4, j++){
//
//                mem[j][0] = s[i];
//                mem[j][1] = s[i+1];
//                mem[j][2] = s[i+2];
//                mem[j][3] = s[i+3];
//            }
        }

        //  cout<<"end of process"<<endl; getch();
//        ofstream ferr;
//        ferr.open("output.txt", std::ios::app);
//        ferr<<"Terminated successfully\n";
//        printPCB(0);
    }
    //  cout<<"End of the process: "<<p.id<<endl;
    cout<<"OS shutdown"<<endl;
}

int main()
{
    cout<<"Starting os";
    std::ofstream outfile;
    outfile.open("prog.txt", std::ios_base::app);
    outfile<<"\n\n\n";
    outfile.close();
    load();
    display_memory();
    cout<<"Done with load and disp_memory()"<<endl; getch();
return 0;
}
