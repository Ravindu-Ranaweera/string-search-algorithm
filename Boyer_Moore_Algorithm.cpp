#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include <algorithm>
#include <string>

using namespace std;

int max(int a, int b)
{
	if(a > b)
		return a;
	else 
		return b;
}

void computeLastOcc(string ptr, int ptrLen, int badchar[128])
{
    int i=0,j=0;
	 
	while( i < 128){
		badchar[i] = -1;
		i++;
	}
	while( j < ptrLen){
		//cout << ptr[j] << badchar[(int) ptr[j]]<< endl;
		badchar[(int) ptr[j]] = j;
		j++;
	}
}

void boyerMooreSearch(vector<char>& text, string pattern)
{
    long int n = text.size();
    int m = pattern.length();
    int badchar[128];  //// assume ASCII character set
	int count=0;
	
    computeLastOcc(pattern, m, badchar); 		// Find last occurence of all characters in pattern
    int s = 0; 
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0){
        	count++;
            cout << count << ". pattern occurs at shift " << s <<endl;

            s += (s + m < n) ? m - badchar[text[s + m]] : 1;

        }else
            s += max(1, j - badchar[text[s + j]]);
    }
}

int main()
{
vector<char> text;
	string pattern="970721";
	string number;
	string line;
	ifstream file;
	file.open("pi.txt");
	if(file.is_open()){
		while(!file.eof()){
			getline(file,line);
			if(isdigit(line[0])){
				for(int i=0,len=line.size();i<len;i++){
					if(!isalnum(line[i])){
						if(line[i]==':'){
							line.erase(line.begin()+i--,line.end());
							break;
						}
						 if (isspace(line[i])) {
							line.erase(i--,1);
							len = line.size();
						}
					}
				}
				for(int a=0;a<line.size();a++){
					text.push_back(line[a]);
				}
			}
		}

	}else{
		cout << "Unable to open file"; 
	}
//	for (int i = 0; i < text.size(); i++) {
//		cout << text.at(i) << ' ';
//		}
    
    boyerMooreSearch(text, pattern);
    return 0;
}
