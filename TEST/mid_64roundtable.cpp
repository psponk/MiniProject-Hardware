#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int main()
{
   int N,F;
   cin >> N;
   list <int> l;
   for(int i=0;i<N;i++){
       cin >> F;
       l.push_back(F);
   }
   int max = 0;
   for(int i=0;i<N;i++){
       int count = 0;
       int index = 1;
       for (list<int>::iterator i=l.begin(); i!=l.end(); i++){
           if(*i == index){
               count ++;
           }
           index ++;
       }
       if(count >= max){
           max = count;
       }
    int tmpback= l.back();
    l.push_front(tmpback);
    l.pop_back();
   }
   cout << max;
    return 0;
}