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
    inputFile2.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/ex1_5_mutates.data",ifstream::in);

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
        i++;
    }

   
    //int max =-100;
    string max_s;
    int isＭutate;
    
    for(int j=0;j<=985;j++){
        isＭutate=1;
        
        string temp = line[0].substr(j,15);
        //cout << "temp is = "<<temp<<endl;

        for(int k=0;k<=985;k++){
            string compare_temp=line[1].substr(k,15);
            //cout << "temp = "<<temp<<" compare = "<<compare_temp<<endl;
            if(checkMutation(temp, compare_temp)){
                isＭutate=0;
                break;
            }
        }
        if(isＭutate==0){
            pattern[temp]=1;
        }
       
    }
    
    
    map<string, int>::iterator iter;
    cout <<"pattern size "<<pattern.size()<<endl;

    /*for(iter = pattern.begin(); iter != pattern.end(); iter++){
        cout << "pattern is = "<<iter->first <<endl;
        
    }*/
    int line_num=2;
    int end=0;
    
    while(line_num<20){
        cout <<"pattern size "<<pattern.size()<<"line num= "<<line_num<<endl;
        for(iter = pattern.begin();iter!=pattern.end();iter++){
            isＭutate=1;
            for(int k=0;k<=985;k++){
                string compare_temp=line[line_num].substr(k,15);
                cout <<"line is "<<line_num<<" k is = "<<k<<" pattern is = "<<iter->first<<endl;
                if(checkMutation(iter->first, compare_temp)){
                    isＭutate=0;
                    break;
                }
            }
            if(isＭutate==0){
                cout <<"in isMutate=0"<<endl;
                pattern[iter->first]=1;
            }else if(isＭutate==1){
                cout <<"in isMutate=1"<<endl;
                pattern.erase(iter->first);
            }

        }
        line_num++;
        
    }
    cout << "out while"<<endl;
    cout <<"pattern size "<<pattern.size()<<endl;

    for(iter = pattern.begin(); iter != pattern.end(); iter++){
        cout << "pattern is = "<<iter->first <<endl;
        
    }
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
