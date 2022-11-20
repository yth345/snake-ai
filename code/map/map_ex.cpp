#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>
#include <fstream>
#include <queue>
using namespace std;

void loadmaps(vector<vector<int>> map[101]){
//    vector<vector<int>> map[101]; //maps
    fstream file;
    char buffer[150];
    string fname;
    for(int i=1;i<101;i++){
        if(i<10)
            fname = "00"+to_string(i);
        else if(i<100)
            fname = "0"+to_string(i);
        else
            fname = to_string(i);
        file.open("/maps/map_"+fname,ios::in);
        if(!file){
            cout<<"no file"<<endl;
        }
        else{
            do{
                vector<int> tempv;
                file.getline(buffer,sizeof(buffer));
                const char* d = " ";
                char *row;
                row = strtok(buffer,d);
                while(row){
                    string s = row;
                    int temp = stoi(s);
                    tempv.push_back(temp);
                    row=strtok(NULL,d);
                }
                map[i].push_back(tempv);
            }while(!file.eof());
        }
        file.close();
    }
}

// (all map, next map, snake position)
vector<vector<int>> generate_map(vector<vector<int>> map[101],int mapindex,queue<tuple<int, int>> snack){
    tuple<int,int> position;
    int row,col;
    int flag3=0;
    int flag5=0;
    int flag7=0;
    int flagall=0;

    // find snack position on map
    for(int m=0;m<50;m++){
        for(int n=0;n<50;n++){
            if(map[mapindex][m][n]==1){
                row=m;
                col=n;
                position=make_tuple(m,n);
            }
        }
    }

    // check if snack is on the snake
    int flag=0;
    queue<tuple<int, int>> tempsnack=snack;
    while(!tempsnack.empty() && flag==0){
        if(tempsnack.front()==position){
            flag=1;
        }
        tempsnack.pop();
    }
    if(flag==0)
        return map[mapindex];
    else{
        // 3*3 find new snack position
        for(int i=row-1;i<row+2;i++){
            if(i>0&&i<49&&flag3==0){
                for(int j=col-1;j<col+2;j++){
                    if(j>0&&j<49&&flag3==0){
                        tempsnack=snack;
                        flag=0;
                        position=make_tuple(i,j);
                        // compare every position and the position of snake, found
                        while(!tempsnack.empty() && flag==0){
                            if(tempsnack.front()==position){
                                flag=1;
                            }
                            tempsnack.pop();
                        }
                        if(flag==0){
                            flag3=1; // find a position to put snack in 3*3
                            row=i; // index of new snack position
                            col=j;
                            break;
                        }
                    }
                    if(flag3==1)
                        break;
                }
            }
            if(flag3==1){
                break;
            }
        }
        if(flag3==1){  // 3*3 found
            vector<vector<int>> newmap;
            for(int i=0;i<50;i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else{
                        if(i==row&&j==col){
                            tempv.push_back(1);
                        }
                        else if(j==0||j==49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if(flag3==0&&flag5==0){  // 5*5 find new snack position
            for(int i=row-2;i<row+3;i++) {
                if (i > 0 && i < 49 && flag5==0) {
                    for (int j = col - 2; j < col + 3; j++) {
                        if (j > 0 && j < 49 && flag5 == 0) {
                            tempsnack = snack;
                            flag = 0;
                            position = make_tuple(i, j);
                            // compare every position and the position of snake, found
                            while (!tempsnack.empty() && flag == 0) {
                                if (tempsnack.front() == position) {
                                    flag = 1;
                                }
                                tempsnack.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;  // find a position to put snack in 5*5
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if(flag5==1)
                            break;
                    }
                }
                if (flag5 == 1) {
                    break;
                }
            }
        }
        if(flag5==1){  // 5*5 found
            vector<vector<int>> newmap;
            for(int i=0;i<50;i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else{
                        if(i==row&&j==col){
                            tempv.push_back(1);
                        }
                        else if(j==0||j==49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if(flag3==0&&flag5==0&&flagall==0){
            for(int i=0;i<50;i++) {
                if (i > 0 && i < 49 && flagall==0) {
                    for (int j = 0; j < 50; j++) {
                        if (j > 0 && j < 49 && flagall == 0) {
                            tempsnack = snack;
                            flag = 0;
                            position = make_tuple(i, j);
                            // compare every position and the position of snake, found
                            while (!tempsnack.empty() && flag == 0) {
                                if (tempsnack.front() == position) {
                                    flag = 1;
                                }
                                tempsnack.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;  // find a position to put snack in 5*5
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if(flagall==1)
                            break;
                    }
                }
                if (flagall == 1) {
                    break;
                }
            }
        }
        if(flagall==1){
            vector<vector<int>> newmap;
            for(int i=0;i<50;i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else{
                        if(i==row&&j==col){
                            tempv.push_back(1);
                        }
                        else if(j==0||j==49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
    }

}
int main() {
    queue<tuple<int,int>> snack;
    tuple<int,int> temp=make_tuple(5,3);
    snack.push(temp);
    temp=make_tuple(5,4);
    snack.push(temp);
    temp=make_tuple(5,5);
    snack.push(temp);
    temp=make_tuple(4,5);
    snack.push(temp);
    temp=make_tuple(4,2);
    snack.push(temp);
    temp=make_tuple(4,3);
    snack.push(temp);
    temp=make_tuple(4,4);
    snack.push(temp);
    temp=make_tuple(5,2);
    snack.push(temp);
    temp=make_tuple(6,2);
    snack.push(temp);
    temp=make_tuple(6,3);
    snack.push(temp);
    temp=make_tuple(6,4);
    snack.push(temp);

    vector<vector<int>> map[101];  // 1~100 save 100 maps
    loadmaps(map);  // read map data from files

    vector<vector<int>> nextmap=generate_map(map,1,snack);
    // check map
    for(int i=0; i<50; i++){
        for(int j=0;j<50;j++){
            cout<<map[1][i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
