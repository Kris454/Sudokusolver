#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <fstream>
using namespace std;


int n;
int Colors[82];
bool succes = true;
unordered_set<int>*  _Generategraph(int n){
    unordered_set<int> *Graph = new unordered_set<int>[n*n+1];
    int div = 0; 
    int mul=0;
    int b = 0;
    vector<int> inty = {1,3,9,11};
    vector<int> inty9 = {1,4,7,28,31,34,55,58,61};
    vector<int> group[n+1];
    //x i y połączenia
    for(int i=1; i<=n*n;i++){
        div = (i-1)/n; 
        for(int w=1; w<=n;w++){
            if(i!=((div*n)+w)){
            Graph[i].insert((div*n)+w);}
        }
    mul = i % n;
    if(mul == 0)
    mul = n;
    for(int k=0; k<n;k++){
        if(i!=((n*k)+mul))
            Graph[i].insert((n*k)+mul);
    }
    }//konic
    //grupy na 4;
    if(n==4){
    for(auto const& a: inty) {
            b = b+1;
            group[b].push_back(a);
            group[b].push_back(a+1);
            group[b].push_back(a+4);
            group[b].push_back(a+5);
        
    }
    }
    if(n==9){
       for(auto const& a: inty9) {
       b=b+1;
       group[b].push_back(a);
       group[b].push_back(a+1);
       group[b].push_back(a+2);
       group[b].push_back(a+9);
       group[b].push_back(a+10);
       group[b].push_back(a+11);   
       group[b].push_back(a+18);
       group[b].push_back(a+19);
       group[b].push_back(a+20); 
        }
    }
    for(int i=1; i<=n;i++){
        for(vector<int>::iterator it = group[i].begin(); it != group[i].end(); ++it)
        {
            for(vector<int>::iterator at = group[i].begin(); at != group[i].end(); ++at)
            {
               if(*it!=*at)
                Graph[*it].insert(*at);
            }  
        }
    }

    return Graph;
}
bool Colored(int i){
    if(Colors[i] == 0)
        return false;
    else
        return true;
}
int Saturated(int i, unordered_set<int>* sudoku ){
    int Saturated = 0;
    int tab[n*n+1]; // kept color
    for(int i=0; i<=11;i++) 
        tab[i] = 0;
    for(unordered_set<int>::iterator it = sudoku[i].begin(); it != sudoku[i].end(); ++it){
    int color = Colors[*it];
    if(color != 0){
        if(tab[color] == 0){
            tab[color]=1;
            Saturated++;
        }
    }
    }
    return Saturated;
    }
int Degree(int i, unordered_set<int>* sudoku){    
    return 28;
}
    
void AssignColor(int a, unordered_set<int>* sudoku, int &colorNumber){
    int tab[n*n+1]; // kept Colors
    for(int i=0; i<=n*n;i++)
        tab[i] = 0;
    int Saturated = 0;
    unordered_set<int> Colors_night;
    for(unordered_set<int>::iterator it = sudoku[a].begin(); it != sudoku[a].end(); ++it){
    int color = Colors[*it];
    if(color != 0){
        if(tab[color] == 0){
            tab[color]=1;
            Colors_night.insert(color);
            Saturated++;
        }
    }
    }
    if(Colors_night.size() == colorNumber)// used colors
    {
    colorNumber++;
    Colors[a]=colorNumber;
    }
    else{
        vector<int> used_Colors;
        for(int i=1; i<=colorNumber; i++){
        used_Colors.push_back(i);}
       for(int i=1; i<=n*n;i++) // set first unused color
       {
          if(tab[i]==0){
            Colors[a]=i;
            tab[i]=1;
            if(i>=10)
                 succes = false; // more than 10 color
          break;
        }
       }
    }
}

void Coloring(unordered_set<int> *sudoku, int *Colors){
    int colorNumber = 1;
    int numberOfColoredNodes = 0;
    while ( numberOfColoredNodes <= n*n)
    {
        int max = -1;
        int index = -1;
        for(int i=1 ; i<=n*n;i++)
        {
            if(!Colored(i))
            {
                int d = Saturated(i, sudoku);
                if(d> max)
                {
                max = d;
                index = i;
                }
                else if(d == max)
                {
                    if (Degree(i, sudoku) > Degree(index, sudoku))
                    {
                    index = i;                
                    }
                }
            }
        }
    AssignColor(index, sudoku, colorNumber);
    numberOfColoredNodes++;
    }
}
int main(int argc, char **argv){
    cout << "Sudoku: 3 for 3x3, 9 for 9x9 " << endl;
    cout << "Enter size sudoku: ";
    cin >> n;
    ifstream myReadFile;
    myReadFile.open("plik");
    char a;
    int i = 1; 
    while (myReadFile >> a){ 
        Colors[i] = (a - 48);
        i++;
    }
    myReadFile.close();
    unordered_set<int> *sudoku = _Generategraph(n);
    Coloring(sudoku, Colors);
    if(succes){
    cout << endl;
    for(int i=1 ; i<=n*n ;i++){
        cout << Colors[i];
        if(i % n == 0 )
            cout << endl;

     }
    }
    else{
     cout << "Not solution found";   
    }
    
}

