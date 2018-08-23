#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;
class Team{
private:
    string name;
    string country;
    int capacity;
    int strength;
    
public:
    Team(string name,string country,int capacity,int strength){
        this->name = name;
        this->country = country;
        this->capacity = capacity;
        this->strength = strength;
        cout << "Team with name "<< name << " just got created"<<endl;
    }
    ~Team(){
        cout << "Team with name "<< this->name << " just got deleted"<<endl;
    }
    string get_name(){
        return this->name;
    }
    string get_country(){
        return this->country;
    }
    int get_capacity(){
        return this->capacity;
    }
    int get_strength(){
        return this->strength;
    }
    
};

class Pairs{
private:
    int check;
    Team *team1;
    Team *team2;
    
public:
    Pairs(Team *team1,Team *team2){
        this->check = 0;
        this->team1 = team1;
        this->team2 = team2;
    }
    
    Team* get_team1(){
        return this->team1;
    }
    Team* get_team2(){
        return this->team2;
    }
    int get_check(){
        return this->check;
    }
    void set_check(int check){
        this->check = check;
    }
    
};
typedef struct Table{
    Pairs* pair;
    Table* next;
}Table;
const int N = 6;

Table* table[N];
Table* tempT;
void push(int i,Pairs* temp){
    if(table[i]==NULL){
        table[i] = new Table;
        table[i]->pair = temp;
        table[i]->next = NULL;
        
    }
    else{
        tempT = table[i];
        while(tempT->next!=NULL){
            tempT = tempT->next;
        }
        tempT->next = new Table;
        tempT->next->pair = temp;
        tempT->next->next = NULL;
    }
    
}

int main(){

    
    int i,j;
    vector<Team*> team;
    //vector<Pairs*> pairs;
    
    string name,country;
    Team *tTeam;
    int capacity, strength;
    ifstream omades ("teams.txt");
    if(!omades){
        cout << "Something went wrong with the file"<<endl;
    }
    for(i=0;i<N;i++){
        omades >> name >> country >> capacity >> strength;
        tTeam = new Team(name,country,capacity,strength);
        team.push_back(tTeam);
    }
    for(i=0;i<N-1;i++){
        table[i] = NULL;
        //hash[i]->next = NULL;
        //hash[i]->pair = NULL;
        
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(i!=j){
                Pairs* temp = new Pairs(team[i],team[j]);
                push(i,temp);
            }
        }
    }

    int e=0;
    Team *pros[N];
    j=0;
    int array[N]={0};
    int tarray[N]={0};
    int met=0;
    int counter=0;
    int agonistikh=0;
    while(agonistikh< 2*(N-1)){
        cout <<agonistikh+1 <<"h agonistikh "<<endl;
        e=agonistikh;
        if(agonistikh>N-1){
            e=agonistikh - N-1;
        }
        
        
        while(counter==0){
            if(array[e]==2){
                for(int f=e;f<N;f++){
                    if(array[f]<2){
                        e=f;
                        break;
                    }
                }
            }
            //e = agonistikh;
            tempT = table[e];
            while(tempT!=NULL){
                if(tempT->pair->get_check()==0){
                    //agonas ton pairs
                    //temp1 = 50 + rand() % (1+team[j]->get_strength()/2);
                    //temp2 = 50 + rand() % (1+team[i]->get_strength()/2);
                    srand(time(NULL));
                    int score1 = 50 + rand() % (1+tempT->pair->get_team1()->get_strength()/2);
                    srand(time(NULL));
                    int score2 = 50 + rand() % (1+tempT->pair->get_team2()->get_strength()/2);
                    cout << tempT->pair->get_team1()->get_name() << " - " << tempT->pair->get_team2()->get_name() <<"  " <<score1<<"-"<<score2<<endl;
                    //kai vazw ta pairs sto pros..
                    // kai vazw check =1
                    tempT->pair->set_check(1);
                    pros[j] = tempT->pair->get_team1();
                    ++j;
                    pros[j] = tempT->pair->get_team2();
                    counter = counter + 1;
                    tarray[e] = 1;
                    break;
                }
                tempT=tempT->next;
            }
            if(counter==0){
                if(e==N-1){ // N
                    e=0;
                }else{
                e=e+1;
                }
            }
        }
        while(counter!=0 && counter<N/2){
            i=0;
           
            while(i<N){ // N
                if(array[i]==2){
                    for(int f=i;f<N;f++){
                        if(array[f]<2){
                            i=f;
                            break;
                        }
                    }
                }
                    tempT = table[i];
                    while(tempT!=NULL){
                        if(tempT->pair->get_check()==0){
                            string onoma1,onoma2;
                            onoma1 = tempT->pair->get_team1()->get_name();
                            onoma2 = tempT->pair->get_team2()->get_name();
                            for(int h=0;h<=j;h++){
                                if(onoma1.compare(pros[h]->get_name())==0){
                                    met=1;
                                    break;
                                }
                            }
                            for(int h=0;h<=j;h++){
                                if(onoma2.compare(pros[h]->get_name())==0){
                                    met=1;
                                    break;
                                }
                            }
                            if(met==0){
                                //agonas ton pairs
                                srand(time(NULL));
                                int score1 = 50 + rand() % (1+tempT->pair->get_team1()->get_strength()/2);
                                srand(time(NULL));
                                int score2 = 50 + rand() % (1+tempT->pair->get_team2()->get_strength()/2);
                                cout << tempT->pair->get_team1()->get_name() << " - " << tempT->pair->get_team2()->get_name() <<"  " <<score1<<"-"<<score2<<endl;
                                ++j;
                                pros[j]=tempT->pair->get_team1();
                                ++j;
                                pros[j]=tempT->pair->get_team2();
                                tempT->pair->set_check(1);
                                counter = counter+1;
                                tarray[i]=1;
                            }
                            met=0;
                        }
                        
                        tempT=tempT->next;
                    }
                    if(counter<N/2 && i==N-1){
                        i=0;
                    }else{
                        i=i+1;
                    }
                }
            }
        for(int l=0;l<N;l++){
            if(tarray[l]==0){
                array[l]=0;
            }else{
                array[l]=array[l]+tarray[l];
            }
        }
        for(int l=0;l<N;l++){
            tarray[l]=0;
        }
            agonistikh=agonistikh+1; counter=0; j = 0;
            for(int y=0;y<N;y++){
                pros[y]=NULL;
            }
        }
        
        
    
}
    
    

