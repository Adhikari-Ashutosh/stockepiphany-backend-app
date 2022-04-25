#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define std_num 50
struct hashblock{
    //Basic Building block of the hashmap
    int status;//Contains info if the hashblock is full
    string key;//Key of the hashblock
    string data;//Data containing all of the ML models
    hashblock(){
        status=0;//A zero status indicates an empty hash block
    }

};
class hashmap{
    public:
        hashblock hashtree[std_num];
        //Hashtree Is an array of hashblocks
        void add(string key,string data){
            int a=hashfunctionA(key);
            int b=hashfunctionB(key);
            if(hashtree[a].status==0){
                //If Primary Hash function returns a empty hashblock i.e.-no collision
                hashtree[a].key=key;
                hashtree[a].data=data;
                hashtree[a].status=1;
            }
            else if(hashtree[b].status==0){
                //If Secondary Hash function returns a empty hashblock i.e.-no collision
                hashtree[b].key=key;
                hashtree[b].data=data;
                hashtree[b].status=1;
            }
            else{
                //Absolute collision
                //HANDLING
                 
                while(true){
                    a++;
                    b++;
                    a=a%std_num;
                    b=b%std_num;
                    if(hashtree[a].status==0){  
                        //We found an empty hashblock here                  
                        hashtree[a].key=key;
                        hashtree[a].data=data;
                        hashtree[a].status=1;
                        break;
                    }
                    else if(hashtree[b].status==0){
                        //We found an empty hashblock here   
                        hashtree[b].key=key;
                        hashtree[b].data=data;
                        hashtree[b].status=1;
                        break;
                    }
                }
            }
        }
        void search(string key){
            int a=hashfunctionA(key);
            int b=hashfunctionB(key);
            //Here since data is limited and known we have ignored the possibility that the hashtree is empty
            //Due to smart handling we have eliminated the need for searching a 
            if(hashtree[a].key==key){
                //Primary hash function
                 cout<<hashtree[a].data;
             }
            
            else  if(hashtree[b].key==key){
                //Secondary hash function
                cout<<hashtree[b].data;
            }
            else{
                //We have encountered a repositioned element
                 while(true){
                    a++;
                    b++;
                    a=a%std_num;
                    b=b%std_num;
                    if(hashtree[a].key==key){                    
                        cout<<hashtree[a].data;
                        break;
                    }
                    else if(hashtree[b].key==key){
                        cout<<hashtree[b].data;
                        break;
                    }
                }
            }
            cout<<"\n";
        }
        int hashfunctionA(string input){
            int sum=0,p=31,q=1;
            for(char ch:input){
                sum=sum+((int)(ch-'A')+1)*q%((int)1e9 + 7);
                q=(q*p)%((int)1e9 + 7);//Modulo to ensure no overflow
                //sum=((int)input[0]-65)*p+((int)input[1]-65)*p^2+((int)input[2]-65)*p^3+((int)input[4]-65)*p^4....+((int)input[length-1]-65)*p^length
            }     
            return (sum%std_num);
        }
        int hashfunctionB(string input){
            int sum=0,p=37,q=1;
            for(char ch:input){
                sum=sum+((int)(ch-'A')+1)*q%((int)1e9 + 9);
                q=(q*p)%((int)1e9 + 9);
            }
            return (sum%std_num);
        }
};

int main(){
    hashmap hm;
    string line;
    string temp;
    int i=0;
    ifstream data("stuff.txt");//Open Data file
    while(getline(data,line)){  
        if(i%2==0){
            temp=line;
        }
        else{
            hm.add(temp,line);  
        }
        i++;
    }
    data.close();
    cin>>line;
    hm.search(line);  
}