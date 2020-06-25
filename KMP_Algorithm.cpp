#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include <algorithm>
#include <string>
 
using namespace std;

void ComputePrefix(string s, int next[])
{
    int n = s.length();
    int q, k;
    next[0] = 0;
    for (k = 0, q = 1; q < n; ++q)
    {
        while (k > 0 && s[k] != s[q])
        {
            k = next[k];  
        }
        if (s[k] == s[q])
        {
            ++k;
        }
        next[q] = k;
    }
}
 
void KMPMatcher(vector<char>& text, string pattern)
{
    long int n = text.size();
    //cout << n <<endl;
    int m = pattern.length();
    int next[m];
    ComputePrefix(pattern, next);
 	int count=0;
 	
    for (int i = 0, q = 0; i < n; ++i)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = next[q];
        }
        if (pattern[q] == text[i])
        {
            ++q;
        }
        if (q == m)
        {
        	count++;
            cout << count <<". Pattern occurs with shift " << i - m + 1 << endl;
            q = 0;
        }
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

    KMPMatcher(text, pattern);
 
    return 0;
}
