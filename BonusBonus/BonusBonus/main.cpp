#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
class Team{
private:
    string name;
    string country;
    int capacity;
    int strength;
    int thesi;
    
public:
    Team(string name,string country,int capacity,int strength,int thesi){
        this->name = name;
        this->country = country;
        this->capacity = capacity;
        this->strength = strength;
        this->thesi = thesi;
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
    int get_thesi(){
        return thesi;
    }
    
};
class Pairs{
private:
    Team *team1;
    Team *team2;
    
public:
    Pairs(Team *team1,Team *team2){
        this->team1 = team1;
        this->team2 = team2;
    }
    Team* get_team1(){
        return this->team1;
    }
    Team* get_team2(){
        return this->team2;
    }
    
};

const int N = 6;
const int B = N*(N-1)/2;
int main(){
    Team *team[N];
    
    Pairs *pairs[B];
    Team *tempTeam[N];
    int check[N]={0};
    string name;
    string country;
    int capacity;
    int strength;
    int k;
    
    int j=0;
    int i=0;
    ifstream openFile ("teams.txt");
    for(j=0 ;j<N/2;j++){
        openFile >> name >> country >> capacity >> strength;
        team[j] = new Team(name,country,capacity,strength,i);
        ++i;
    }
    for(j=N-1;j>=N/2;j--){
        openFile >> name >> country >> capacity >> strength;
        team[j] = new Team(name,country,capacity,strength,j);
        ++i;
    }
    //1st match
    // fill in the check array
    // put in the pair thats going to play the game..
    for(k=0;k<N/2;k++){
        pairs[k]=new Pairs(team[k],team[N/2+k]);
        check[team[k]->get_thesi()] = 1;
        check[team[N/2+k]->get_thesi()] = -1;
    }
    
    for(j=0;j<N-1;j++){
        // we copy the array
        for(i=0;i<N;i++){
            tempTeam[i]=team[i];
        }
        // we perform round robin to the array with 1st element being fixed..
        for(int i=1;i<N;i++){
            if(i==1){
                team[i]=tempTeam[N/2];
            }
            else if(i<N/2){
                team[i]=tempTeam[i-1];
            }
            else if(i<N-1){
                team[i]=tempTeam[i+1];
            }
            else{
                team[i]=tempTeam[N/2-1];
            }
        }
        //inspect the check Array then decide the matches..
        
            for(i=0;i<N/2;i++){
                int x = check[team[i]->get_thesi()];
                int y = check[team[N/2+i]->get_thesi()];
                if (x==-1 && y==1){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==1 && y==-1){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -1;
                    check[team[N/2+i]->get_thesi()] = 1;
                    ++k;
                }
                else if(x==2 && y==-2){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -1;
                    check[team[N/2+i]->get_thesi()] = 1;
                    ++k;
                }
                else if(x==-2 && y==2){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==1 && y==1){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 2;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==-1 && y==-1){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -2;
                    ++k;
                }
                else if(x==1 && y==2){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 2;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==-1 && y==2){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==-1 && y==-2){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -2;
                    check[team[N/2+i]->get_thesi()] = 1;
                    ++k;
                }
                else if(x==-1 && y==2){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if (x==2 && y==1){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -1;
                    check[team[N/2+i]->get_thesi()] = 2;
                    ++k;
                }
                else if (x==2 && y==-1){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -1;
                    check[team[N/2+i]->get_thesi()] = 1;
                    ++k;
                }
                else if (x==2 && y==2){
                    //in theory it will not go here but we put it just in case..
                    cout << "Dead end.." <<endl;
                }
                else if(x==1 && y==-2){
                    pairs[k] = new Pairs(team[N/2+i],team[i]);
                    check[team[i]->get_thesi()] = -1;
                    check[team[N/2+i]->get_thesi()] = 1;
                    ++k;
                }
                else if(x==-2 && y==1){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if (x==-2 && y==-1){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -2;
                    ++k;
                }
                else if(x==-2 && y==2){
                    pairs[k] = new Pairs(team[i],team[N/2+i]);
                    check[team[i]->get_thesi()] = 1;
                    check[team[N/2+i]->get_thesi()] = -1;
                    ++k;
                }
                else if(x==-2 && y==-2){
                    //in theory it will not go here but we put it just in case..
                    cout << "Dead end.." <<endl;
                }
            }
    }
    cout << endl;
    int ag=1;
    for(i=0;i<B;i++){
        //match
        if(i % (N/2) == 0){
        cout << "match "<<ag<<endl; ++ag;
        }
        cout << pairs[i]->get_team1()->get_name()<<" - "<<pairs[i]->get_team2()->get_name()<<endl;
        if(i % (N/2) == N/2-1){
            cout << endl;
        }
    }
    for(i=0;i<B;i++){
        //match
        if(i % (N/2) == 0){
            cout << "match "<<ag<<endl; ++ag;
        }
        cout << pairs[i]->get_team2()->get_name()<<" - "<<pairs[i]->get_team1()->get_name()<<endl;
        if(i % (N/2) == N/2-1){
            cout << endl;
        }
    }
}
