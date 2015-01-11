// ----------------------------
// UVaTex.c++
// Copyright (C) 2014
// Kevin W. Kenyon
// Status: Accepted By UVa
// ----------------------------

// --------
// includes
// --------
#include <iostream>
#include <cassert>

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif



std::string replace(char,std::string,std::string,std::string&);
bool first = false;

void tex_read(std::istream& r) {
	using namespace std;
	string line;
	while(getline(r, line)) {
		cout << replace('"', "``","''",line) << endl;
	}
}

std::string replace(char search, std::string replace_frst,
							std::string repalce_scd, 
							std::string& line) {
	int searchCount = 0;
	for (int i = 0; i < line.length(); ++i) {
		if(line[i] == search)
			++searchCount;
	}

	int addedSpace = 
		(replace_frst.length() * searchCount) - searchCount;

	std::string str;
	str.resize(addedSpace + line.length());
	int k = 0;
	for (int i = 0; i < line.length(); ++i) {
		if(line[i] == search) {
			if (!first) {
				for (int j = 0; j < replace_frst.length(); ++j) {
					str[k] = replace_frst[j];
					++k;
				}
				first = true;
			} else {
				for (int j = 0; j < repalce_scd.length(); ++j) {
					str[k] = repalce_scd[j];
					++k;
				}
				first = false;
			}

		} else {
			str[k] = line[i];
			++k;
		}
	}

	return str;
}


int main() {
	using namespace std;
	tex_read(cin);
}