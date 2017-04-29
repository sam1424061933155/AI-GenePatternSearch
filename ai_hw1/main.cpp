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
//string geno_line[1000];




struct sig_pattern
{
    vector<string> pattern;
    string source;
    
    sig_pattern(vector<string> pattern, string source)
    {
        this->pattern = pattern;
        this->source = source;
    }
};

bool checkMutation(string pattern, string temp){
    
    int correct=0;
    
    for(int j=0;j<15;j++){
        if(pattern[j]==temp[j]){
            correct++;
        }
    }
    //cout <<"error = "<<error<<endl;
    if(correct>=10){
        //cout << "checkmutation return true"<<endl;
        return true;
    }
    
    return false;
}
bool checRealkMutation(string pattern, string temp){
    
    int error=0;
    
    for(int j=0;j<15;j++){
        if(pattern[j]!=temp[j]){
            error++;
        }
    }
    
    if(error<=7){
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
            if(error<5){
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
/*void findMin(map<string,int>&pattern,string temp_pattern,int pos){
    
    int min_score=10000;
    string min_pattern;
    
   
    cout <<"in finMin, pattern is = "<<temp_pattern<<" pos is = "<<pos<<endl;
    map<string, int>::iterator iter;

    for(iter = pattern.begin(); iter != pattern.end(); iter++){
        
        for(int alpha=4;alpha>0;alpha--){
            int score_f=0;
            int score_b=0;
            int score=0;
            string temp=iter->first;
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
            
            if(score<50){
                cout <<"in finMin mutate pattern is = "<<temp<<" score is = "<<score<<endl;

                if(pattern.find(temp)==pattern.end()){
                    pattern[temp]=score;
                }
            }
            
            if(score<min_score){
                min_score=score;
                min_pattern=temp;
            }
            
            
        }

        
    }
        //cout << "min_string = "<<min_pattern<<endl;
    //return min_pattern;
    
}*/






int main(int argc, const char * argv[]) {

    ifstream inputFile1,inputFile2,inputFile3;
    inputFile1.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q1.data",ifstream::in);
    inputFile2.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q3.data",ifstream::in);


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
    
    string start;
    vector<sig_pattern> goal_pattern;
    vector<string>temp_pattern;

    for(int i=0;i<=985;i++){
        string temp=line[0].substr(i,15);
        for(int j=1;j<50;j++){
            for(int k=0;k<=985;k++){
                string temp_other=line[j].substr(k,15);
                if(checkMutation(temp, temp_other)){
                    temp_pattern.push_back(temp_other);
                }
            }
        }
        goal_pattern.push_back(sig_pattern(temp_pattern, temp));
        temp_pattern.clear();
    }
    cout <<"finish"<<endl;

    cout <<"goal_pattern = "<<goal_pattern.size()<<endl;
    vector<sig_pattern>::iterator iter;
    vector<string> candidate_pattern;
    //map<char,int> char_count;
    for(iter=goal_pattern.begin();iter!=goal_pattern.end();iter++){
        //vector<string>::iterator iter1;
        string combine_pattern="";
        for(int i=0;i<15;i++){
            int a_count=0;
            int t_count=0;
            int c_count=0;
            int g_count=0;
            int max_count=-100;
            string max_char;
            for(int j=0;j<iter->pattern.size();j++){
                if(iter->pattern[j][i]=='A'){
                    a_count++;
                }else if(iter->pattern[j][i]=='T'){
                    t_count++;
                }else if(iter->pattern[j][i]=='C'){
                    c_count++;
                }else if(iter->pattern[j][i]=='G'){
                    g_count++;
                }
                
            }
            //cout <<"a_count = "<<a_count<<" t_count = "<<t_count<<" c_count = "<<c_count<<" g_count = "<<g_count<<endl;
            if(a_count>max_count){
                max_count=a_count;
                max_char="A";
            }
            if(t_count>max_count){
                max_count=t_count;
                max_char="T";
            }
            if(c_count>max_count){
                max_count=c_count;
                max_char="C";
            }
            if(g_count>max_count){
                max_count=g_count;
                max_char="G";
            }
            //cout <<"origin = "<<combine_pattern<<" append string = "<<max_char<<endl;
            combine_pattern=combine_pattern+max_char;
        }
        candidate_pattern.push_back(combine_pattern);
    }
    //cout <<"candidate pattern size is = "<<candidate_pattern.size()<<endl;

    map<string,int> answer;
    for(vector<string>::iterator i=candidate_pattern.begin();i!=candidate_pattern.end();i++){
        for(int j=0;j<50;j++){
            int find=0;
            for(int k=0;k<=985;k++){
                string temp=line[j].substr(k,15);
                //cout <<"origin = "<<*i<<" comapre = "<<temp<<" the same = "<<checRealkMutation(*i, temp)<<endl;
                if(checRealkMutation(*i,temp)){
                    answer[temp]=k;
                    find=1;
                    break;
                }
                
            }
            if(find==0){
                candidate_pattern.erase(i);
                answer.clear();
                i--;
                break;
            }
        }
        if(answer.size()==50){
            cout <<"find answer "<<endl;
            cout <<"root is = "<<*i<<endl;
            break;
        }
    }
    cout <<"answer size "<<answer.size()<<endl;
    map<string, int>::iterator answer_iter;
    for(answer_iter=answer.begin();answer_iter!=answer.end();answer_iter++){
        cout << "pattern is = "<<answer_iter->first<<" pos = "<<answer_iter->second<<endl;
        
    }
    
    
    
    
    //cout <<"start is = "<<start<<endl;
    
    //map<string, int>::iterator iter;
    /*cout <<"pattern size "<<pattern.size()<<endl;

    for(iter = pattern.begin(); iter != pattern.end(); iter++){
            cout << "pattern is = "<<iter->first <<endl;
        
    }*/
   
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
