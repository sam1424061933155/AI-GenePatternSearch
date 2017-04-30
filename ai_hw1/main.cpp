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

struct ans_pattern
{
    string pattern;
    int  pos;
    
    ans_pattern(string pattern, int pos)
    {
        this->pattern = pattern;
        this->pos = pos;
    }
};

bool checkMutation(string pattern, string temp,int accept){
    
    int correct=0;
    
    for(int j=0;j<15;j++){
        if(pattern[j]==temp[j]){
            correct++;
        }
    }
    //cout <<"error = "<<error<<endl;
    if(correct>=15-accept){                   // correct>=10 for q2 ,correct>=8 for q3
        //cout << "checkmutation return true"<<endl;
        return true;
    }
    
    return false;
}
bool checkRealMutation(string pattern, string temp,int accept){
    
    int error=0;
    
    for(int j=0;j<15;j++){
        if(pattern[j]!=temp[j]){
            error++;
        }
    }
    
    if(error<=accept){   //5 for q2 , 7 for q3
        return true;
    }
    
    return false;
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

void findSimilar(string *line ,vector<sig_pattern> &goal_pattern , vector<string> &temp_pattern,int accept){
    
    for(int i=0;i<=985;i++){
        string temp=line[0].substr(i,15);
        for(int j=1;j<50;j++){
            for(int k=0;k<=985;k++){
                string temp_other=line[j].substr(k,15);
                if(checkMutation(temp, temp_other,accept)){
                    temp_pattern.push_back(temp_other);
                }
            }
        }
        goal_pattern.push_back(sig_pattern(temp_pattern, temp));
        temp_pattern.clear();
    }
}

void findPossibleString(vector<sig_pattern> &goal_pattern , vector<string> &candidate_pattern){
    
    vector<sig_pattern>::iterator iter;
    
    for(iter=goal_pattern.begin();iter!=goal_pattern.end();iter++){
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
            combine_pattern=combine_pattern+max_char;
        }
        //cout <<"candidate pattern is = "<<combine_pattern<<endl;
        candidate_pattern.push_back(combine_pattern);
    }


}

void findMutation(string *line, vector<ans_pattern> &answer, vector<string> &candidate_pattern,int accept){
    
    for(vector<string>::iterator i=candidate_pattern.begin();i!=candidate_pattern.end();i++){
        for(int j=0;j<50;j++){
            int find=0;
            for(int k=0;k<=985;k++){
                string temp=line[j].substr(k,15);
                if(checkRealMutation(*i,temp,accept)){
                    //answer[temp]=k;
                    answer.push_back(ans_pattern(temp,k));
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
            //cout <<"find answer "<<endl;
            cout <<"root is = "<<*i<<endl;
            break;
        }
    }

    
}







int main(int argc, const char * argv[]) {

    ifstream inputFile1,inputFile2,inputFile3;
    inputFile1.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q1.data",ifstream::in);
    inputFile2.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q2.data",ifstream::in);
    inputFile3.open("/Users/sam/Desktop/course/AI/ai_hw1/ai_hw1/q3.data",ifstream::in);


    string temp_line;
    string line[50];

    int i=0;
    map<string, int> pattern;
    cout << "----q1-----"<<endl;


    while(getline(inputFile1,temp_line))
    {
        line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
   
    for(int j=0;j<=985;j++){
        
        string temp = line[0].substr(j,15);  //substr(starPos,length)
      
        
        if(pattern.find(temp)!=pattern.end()){  //find in map
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
        if(pattern.size()==50){
            break;
        }
    }
    
    map<string, int>::iterator iter_q1;
    
    for(iter_q1 = pattern.begin(); iter_q1 != pattern.end(); iter_q1++){
        for(int i=0;i<50;i++){
            cout << "S"<<i+1<<": {( "<<iter_q1->first<< " , "<<line[i].find(iter_q1->first)<<" )} "<<endl;
        }
    }
    
    /*question2*/
    cout << "----q2-----"<<endl;
    i=0;

    while(getline(inputFile2,temp_line))
    {
        line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
    
    vector<sig_pattern> goal_pattern;
    vector<string>temp_pattern;

    
    findSimilar(line, goal_pattern, temp_pattern,5);

    vector<string> candidate_pattern;

    
    findPossibleString(goal_pattern, candidate_pattern);

    vector<ans_pattern> answer;
    findMutation(line, answer, candidate_pattern,5);
    
    vector<ans_pattern>::iterator answer_iter;
    int num=0;
    for(answer_iter=answer.begin();answer_iter!=answer.end();answer_iter++){
        //cout << "pattern is = "<<answer_iter->first<<" pos = "<<answer_iter->second<<endl;
        cout << "S"<<num+1<<": {( "<<answer_iter->pattern<< " , "<<answer_iter->pos<<" )} "<<endl;
        num++;

    }
    
    /*question3*/
    cout << "----q3-----"<<endl;
    i=0;
    
    while(getline(inputFile3,temp_line))
    {
        line[i]=temp_line.substr(0,temp_line.length()-1);
        i++;
    }
    
    vector<sig_pattern> goal_pattern3;
    vector<string>temp_pattern3;
    
    
    findSimilar(line, goal_pattern3, temp_pattern3,7);
    
    vector<string> candidate_pattern3;
    
    
    findPossibleString(goal_pattern3, candidate_pattern3);
    
    vector<ans_pattern> answer3;
    findMutation(line, answer3, candidate_pattern3,7);
    
    vector<ans_pattern>::iterator answer_iter_q3;
    num=0;
    for(answer_iter_q3=answer3.begin();answer_iter_q3!=answer3.end();answer_iter_q3++){
        //cout << "pattern is = "<<answer_iter->first<<" pos = "<<answer_iter->second<<endl;
        cout << "S"<<num+1<<": {( "<<answer_iter_q3->pattern<< " , "<<answer_iter_q3->pos<<" )} "<<endl;
        num++;
        
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
