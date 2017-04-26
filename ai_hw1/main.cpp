//
//  main.cpp
//  ai_hw1
//
//  Created by sam on 2017/4/16.
//  Copyright © 2017年 sam. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <map>
#include <vector>


using namespace std;
int last=-1;



struct sig_pattern
{
    string pattern;
    int pos;
    
    sig_pattern(string pattern, int pos)
    {
        this->pattern = pattern;
        this->pos = pos;
    }
};

bool checkMutation(string pattern, string temp){
    
    int error=0;
    
    for(int j=0;j<15;j++){
        if(pattern[j]!=temp[j]){
            error++;
        }
        if(error>5){
            return false;
        }
    }
    
    return true;
}
char mapChar(int value){
    
    if(value==0){
        return 'A';
    }else if(value==1){
        return 'T';
    }else if(value==2){
        return 'C';
    }else if(value==3){
        return 'G';
    }
    return ' ';
}
string mutation(string temp){
    cout <<"mutate origin string "<<temp<<endl;
    
    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
    int random_pos=rand()%16;
    int random_c=rand()%4;
    char value = mapChar(random_c);
    
    while(temp[random_pos]==value || last==random_pos){
        unsigned seed;
        seed = (unsigned)time(NULL);
        srand(seed);
        last=random_pos;
        random_pos=rand()%16;
        random_c=rand()%4;
        value = mapChar(random_c);
    }
    cout <<"mutate pos = "<<random_pos<<" , value = "<<value<<endl;

    temp[random_pos]=value;
    
    return temp;
    
}


string createRandomPattern(int a, int t ,int c ,int g){
    
    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
    string pattern2="";
    
    
    while(a!=0 || t!=0 || c!=0 || g!=0){
        int random = rand()%4;
        if(random==0 && a>0){
            pattern2=pattern2+"A";
            a--;
        }else if(random==1 && t>0){
            pattern2=pattern2+"T";
            t--;
        }else if(random==2 && c>0){
            pattern2=pattern2+"C";
            c--;
        }else if(random==3 && g>0){
            pattern2=pattern2+"G";
            g--;
        }
        
    }
    cout << "pattern2 in func is = "<<pattern2<<endl;

    return pattern2;
}

int main(int argc, const char * argv[]) {

    ifstream inputFile1,inputFile2,inputFile3;
    inputFile1.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q1.data",ifstream::in);
    inputFile2.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q2.data",ifstream::in);

    string temp_line;
    string line[50];
    int i=0;
    map<string, int> pattern;
    
    cout << "---q1----"<<endl;


    /*while(getline(inputFile1,temp_line))
    {
        //cout << temp_line<<endl;
        line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
   
    for(int j=0;j<=985;j++){
        
        string temp = line[0].substr(j,15);  //substr(starPos,length)
      
        
        if(pattern.find(temp)!=pattern.end()){  //find in map   //maybe be contain more than one in other control sequence
            pattern.erase(temp);
        }else{  //not in map
            int match_all=1;
            for(int k=1;k<50;k++){
                if(line[k].find(temp)==string::npos){
                    match_all=0;
                    //cout << "temp not in sequence "<<k<<endl;
                    break;
                }
            }
            if(match_all){
                pattern[temp]=1;
                //cout << "temp in all sequence "<<endl;
            }

            
        }
        
    }
    
    map<string, int>::iterator iter;
    
    cout <<"there are "<<pattern.size()<<" pattern"<<endl;

    for(iter = pattern.begin(); iter != pattern.end(); iter++){
        for(int i=0;i<50;i++){
            cout << "S"<<i+1<<" patern "<<iter->first<< " in pos "<<line[i].find(iter->first)<<endl;
        }
    }*/
    
    /*question2*/
    cout << "---q2----"<<endl;
    i=0;
    map<char,int>count;
    while(getline(inputFile2,temp_line))
    {
        line[i]=temp_line.substr(0,temp_line.length()-1);
        
        // count the number of each char
        for(int j=0;j<line[i].size();j++){
            //cout <<"line["<<i<<"]["<<j<<"] = "<<line[i][j]<<endl;
            if(count.find(line[i][j])!=count.end()){
                count[line[i][j]]++;
            }else{
                count[line[i][j]]=1;
            }
        }
        //cout <<"next line"<<endl;
        i++;
    }
    cout << "count a "<<count['A']<<endl;
    cout << "count t "<<count['T']<<endl;
    cout << "count c "<<count['C']<<endl;
    cout << "count g "<<count['G']<<endl;

    //int sum = count['A']+count['T']+count['C']+count['G'];
    int a = 15*count['A']/50000;
    int t = 15*count['T']/50000+1;
    int c = 15*count['C']/50000;
    int g = 15*count['G']/50000;

    cout << "a = "<<a<<" ,t = "<<t<<" ,c = "<<c<<" ,g = "<<g<<endl;
    int max =-100;
    string max_s;
    
    for(int j=0;j<=985;j++){
        //cout <<"j is "<<j<<endl;
        
        string temp = line[0].substr(j,15);  //substr(starPos,length)
        
        
        if(pattern.find(temp)!=pattern.end()){  //find in map   //maybe be contain more than one in other control sequence
            //do nothing
        }else{  //not in map

            for(int k=1;k<50;k++){
                if(line[k].find(temp)!=string::npos){
                    if(pattern.find(temp)==pattern.end()){
                        pattern[temp]=1;
                    }else{
                        pattern[temp]++;
                    }
                }else if(line[k].find(temp)==string::npos){
                    //do nothing
                }
            }
        }
        if(pattern[temp]>max){
            max=pattern[temp];
            max_s=temp;
        }
        
    }
    cout <<"string = "<<max_s<<" time = "<<max<<endl;
    
    string goal_pattern2=createRandomPattern(a,t,c,g);

    
    
    
    vector<sig_pattern> v_sig_pattern;
    int find=0;
    int find_pattern=0;
    int time=0;
    string temp_goal;
    int temp_count=0;
    int max_count=-100;
    
    while(find_pattern==0){
        time++;
        cout << "this is "<<time<<" time"<<endl;
        if(time!=1){
            max_s=mutation(max_s);
        }
        
        for(int j=0;j<50;j++){
            find=0;
            //cout << "line "<<j+1<<endl;
            if(line[j].find(max_s)!=string::npos){
                v_sig_pattern.push_back( sig_pattern( max_s, ( line[j].find(max_s) ) ));
            }else{
                for(int k=0;k<985;k++){
                    string temp = line[j].substr(k,15);  //substr(starPos,length)
                    if(checkMutation(max_s, temp)){  //mutation less than 5
                        v_sig_pattern.push_back( sig_pattern(temp,k));
                        find=1;
                        //temp_count++;
                        break;
                    }
                    
                }
                if(find==0){
                    v_sig_pattern.clear();   // not find significant patter in line
                    /*if(temp_count>max_count){
                        goal_pattern2=max_s;
                    }
                    temp_count=0;*/
                    break;
                }
            }
        }
        if(v_sig_pattern.size()==50){
            find_pattern=1;
        }
        

    }
    cout << "find goal pattern , and pattern is  "<<max_s<<endl;
    
    
    
    
    
    
    
    
    
    
    return 0;
}
