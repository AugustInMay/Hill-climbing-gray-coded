#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <bitset>
#include <iomanip>
using namespace std;

void gray_code(bitset<5> inp, bitset<5> *out){
    *out=inp>>1^inp;
}

void gray_decode(bitset<5> inp, bitset<5> *out){
    *out=inp;
    for(int i=1; i<5; i++){
        *out^=inp>>i;
    }
}

void neighb_fill(bitset<5> inp, bitset<5> *out){
    for(int i=0; i<5; i++){
        bitset<5> fl=inp;
        out[i]=fl.flip(i);
    }
}

int max_around(bitset<5> inp, bitset<5> *out, int *Q){
    int ret=(int)(inp.to_ulong());
    for(int i=0; i<5; i++){
        if(Q[(int)(out[i].to_ulong())]>Q[ret]){
            ret=(int)(out[i].to_ulong());
        }
    }
    return ret;
}

int main() {
    srand(time(0));
    bitset<5> field_g[32], neighb[5], field[32];
    int Q[32], n, cur_p=rand()%32, step=1;
    bool by_neighb=false;
    cin>>n;
    cout<<"The field and landscape are:  "<<endl;
    for(int i=0; i<32; i++){
        field[i]=i;
        gray_code(i, &field_g[i]);
        Q[i]=rand()%101;
        cout<<fixed;
        cout<<setw(2)<<right<<i+1<<") "<<field[i]<<" - Q = "<<setw(10)<<left<<Q[i]<<setw(5)<<left<<" ";
        if((i+1)%5==0){
            cout<<"\n";
        }
    }
    cout<<"\n-----\nThe field and landscape gray-coded are: "<<endl;
    for(int i=0; i<32; i++){
        cout<<fixed;
        cout<<setw(2)<<right<<i+1<<") "<<field_g[i]<<" - Q = "<<setw(10)<<left<<Q[i]<<setw(5)<<left<<" ";
        if((i+1)%5==0){
            cout<<"\n";
        }
    }
    cout<<"\n-----\n";
    cout<<"\nRandom choice is "<<field[cur_p]<<" - Q = "<<Q[cur_p];
    while(step!=n+1){
        cout<<"\n-----\n\nSTEP "<<step<<" -----\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p];
        neighb_fill(field_g[cur_p], neighb);
        cout<<"\nHere are the neighbours: ";
        for(int i=0; i<5; i++){
            bitset<5> temp;
            gray_decode(neighb[i], &temp);
            cout<<temp<<" Q = "<<Q[(int)(temp.to_ulong())]<<" ; ";
        }
        cout<<"\n\n-----\nThe same gray-coded: \nCurrent max is "<<field_g[cur_p]<<" with max Q = "<<Q[cur_p];
        cout<<"\nHere are the neighbours: ";
        for(int i=0; i<5; i++){
            bitset<5> temp;
            gray_decode(neighb[i], &temp);
            cout<<neighb[i]<<" Q = "<<Q[(int)(temp.to_ulong())]<<" ; ";
        }
        cout<<"\n-----\n";
        if(cur_p==max_around(field_g[cur_p], neighb, Q)){
            cout<<"\nThere are no better neighbours left... Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step<<" STEPS\n\n-----\nThe same gray-coded: \nFinished with "<<field_g[cur_p]<<" Q = "<<Q[cur_p]<<"\n-----\n";
            by_neighb=true;
            break;
        }
        else{
            step++;
            cur_p=max_around(field_g[cur_p], neighb, Q);
            cout<<"\nThere is a better neighbour, and it is a NEW max!\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p]<<"\n\n-----\nThe same gray-coded: \nCurrent max is "<<field_g[cur_p]<<" with max Q = "<<Q[cur_p];
        }
    }
    if(step-1==n && !by_neighb){
        cout<<"\n-----\n\n!The limit of steps is reached!\n\n-----Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step-1<<" STEPS\n\n-----\nThe same gray-coded: \nFinished with "<<field_g[cur_p]<<" Q = "<<Q[cur_p]<<"\n-----\n";
    }
    return 0;
}