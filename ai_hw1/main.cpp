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
//map<string, int> pattern;
string geno_line[1000];




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
    }
    //cout <<"error = "<<error<<endl;
    if(error==10){
        //cout << "checkmutation return true"<<endl;
        return true;
    }
    
    return false;
}
void createString(map<string,int> &pattern,string pattern1,string pattern2){
    //cout << "in createstring"<<endl;
    
    
    int error=0;
    string temp1=pattern1;
    string temp2=pattern2;
    for(int j=0;j<15;j++){   // pattern1 換成 pattern2  pattern1保留後面
        if(temp1[j]!=temp2[j]){
            error++;
            if(error<6){
                temp1[j]=temp2[j];
            }else{
                if(pattern.find(temp1)==pattern.end()){  // not find in pattern
                    //cout<<"in add to pattern"<<endl;
                    pattern[temp1]=1;
                }
                break;
            }
        }
    }
    error=0;
    temp1=pattern1;
    temp2=pattern2;
    for(int j=0;j<15;j++){   // pattern1 換成 pattern2  pattern2保留後面
        if(temp1[j]!=temp2[j]){
            error++;
            if(error<6){
                temp2[j]=temp1[j];
            }else{
                if(pattern.find(temp2)==pattern.end()){  // not find in pattern
                    //cout<<"in add to pattern"<<endl;
                    pattern[temp2]=1;
                }
                break;
            }
        }
    }
    
    
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
void findMin(map<string,int>&temp_pattern,string pattern,int pos){
    
    int min_score=10000;
    string min_pattern;
    
   
    cout <<"in finMin, pattern is = "<<pattern<<" pos is = "<<pos<<endl;
    for(int alpha=4;alpha>0;alpha--){
        int score_f=0;
        int score_b=0;
        int score=0;
        string temp=pattern;
        if(alpha==4){
            temp[pos]='A';
        }else if(alpha==3){
            temp[pos]='T';
        }else if(alpha==2){
            temp[pos]='C';
        }else if(alpha==1){
            temp[pos]='G';
        }
        for(int k=0;k<1000;k++){
            if(geno_line[k].find(temp.substr(0,15))!=string::npos){
                score_f=score_f+64;
            }
            if(geno_line[k].find(temp.substr(0,14))!=string::npos){
                score_f=score_f+32;
            }
            if(geno_line[k].find(temp.substr(0,13))!=string::npos){
                score_f=score_f+16;
            }
            if(geno_line[k].find(temp.substr(0,12))!=string::npos){
                score_f=score_f+8;
            }
            if(geno_line[k].find(temp.substr(0,11))!=string::npos){
                score_f=score_f+4;
            }
            if(geno_line[k].find(temp.substr(0,10))!=string::npos){
                score_f=score_f+2;
            }
            if(geno_line[k].find(temp.substr(0,9))!=string::npos){
                score_f=score_f+1;
            }
            if(geno_line[k].find(temp.substr(1,15))!=string::npos){
                score_b=score_b+64;
            }
            if(geno_line[k].find(temp.substr(2,15))!=string::npos){
                score_b=score_b+32;
            }
            if(geno_line[k].find(temp.substr(3,15))!=string::npos){
                score_b=score_b+16;
            }
            if(geno_line[k].find(temp.substr(4,15))!=string::npos){
                score_b=score_b+8;
            }
            if(geno_line[k].find(temp.substr(5,15))!=string::npos){
                score_b=score_b+4;
            }
            if(geno_line[k].find(temp.substr(6,15))!=string::npos){
                score_b=score_b+2;
            }
            if(geno_line[k].find(temp.substr(7,15))!=string::npos){
                score_b=score_b+1;
            }
        }
        score=score_f+score_b;

        cout <<"in finMin mutate pattern is = "<<temp<<" score is = "<<score<<endl;
        temp_pattern[temp]=score;

        if(score<min_score){
            min_score=score;
            min_pattern=temp;
        }

        
    }
    //cout << "min_string = "<<min_pattern<<endl;
    //return min_pattern;
    
}




int main(int argc, const char * argv[]) {

    ifstream inputFile1,inputFile2,inputFile3;
    inputFile1.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q1.data",ifstream::in);
    inputFile2.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/ex1_5_mutates.data",ifstream::in);
    inputFile3.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/genome.data",ifstream::in);


    string temp_line;
    string line[50];
    //string geno_line[1000];

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

    while(getline(inputFile2,temp_line))
    {
        line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
    
    i=0;
    
    while(getline(inputFile3,temp_line))
    {
        geno_line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
    string start;

    for(int j=0;j<985;j++){
        string temp=line[0].substr(j,15);
        if(temp[0]=='G'){
            start=temp;
            break;
        }
    }

   
    string max_s;
    
    for(int j=0;j<15;j++){
        cout <<"j is = "<<j<<endl;
        findMin(pattern,start, j);
    }
    
    cout <<"start is = "<<start<<endl;
    
    map<string, int>::iterator iter;
    cout <<"pattern size "<<pattern.size()<<endl;

    for(iter = pattern.begin(); iter != pattern.end(); iter++){
            cout << "pattern is = "<<iter->first <<endl;
        
    }
   
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
