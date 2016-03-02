

#include <iostream>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

double sqrt(const double n) {
	double g = 4;
	while (true) {
		double e = (g + n / g) / 2;
		cout << e << endl;
		if (e == g) {
			return e;
			break;
		}
		g = e;
	}
	return 0;
}

int factorial(int n){
	if (n == 1)
		return 1;
	else
		return n*factorial(n-1);
}

int fibonacci_r (int n){
	if (n == 0)
		return 1;
	if (n ==1)
		return 1;
	else
		return fibonacci_r(n-1)+fibonacci_r(n-2);
}

bool isalphanum (char c){
	if ((int) c >= 97 && (int) c <= 122)
		return true;
	if ((int) c >= 65 && (int) c <= 90)
		return true;
	if ((int) c >= 48 && (int) c <= 57)
		return true;
	return false;
}

void swap(string arr, int i, int j){
	char temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int l_partition(string arr, int l, int r){
	char pivot = arr[r];
	int i = l;
	int j = l;
	while (j < r){
		if (arr[j] <= pivot){
			swap(arr, i, j);
			i++;
		}
		j++;
	}
	swap(arr, i, r);
	return i;
}

int h_partition(string arr, int l, int r) {
	char pivot = arr[r];
	int i = r;
	int j = r;
	for (;;) {
		while (arr[j] <= pivot) {
			j--;
		}
		while (arr[i] < pivot) {
			i--;
		}
		if (i > j) {
			swap(arr, j, i);
		} else {
			return j;
		}
	}
	return j;
}

void quik_sort(char* arr, int l, int r){
	if (l < r){
		int p = h_partition(arr, l, r);
		quik_sort(arr, l, p - 1);
		quik_sort(arr, p + 1, r);
	}
}

string dec2str_bin(int n){
	string r = "";
	while (n != 0){
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	return r;
}

string maxstr_bin(string r){
	for (int i = 0; i < (int)r.length(); i++){
		if (r[i] != '1' ) r[i] = '1';
	}
	return r;
}

int str_bin2dec(string str){
	int n = 0;
	int i = 0;
	int size = str.length() - 1;
	int count = 0;
	while (i < (int)str.length() ){
		if (str[i] == '1')
		n = n + (int)pow(2, size - count);
		count++;
		i++;
	}
	return n;
}

int get_complement(int n) {
	return (str_bin2dec(maxstr_bin(dec2str_bin(n))) - n);
}

int cesar_cipher(int c, int l, int r, int k) {
	int j = 0;
	if (c < l || c > r) {
		return c;
	}
	while (j < k) {
		c++;
		if (c > r)
			c = l;
		j++;
	}
	return c;
}

template<typename T>
string to_string(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

string unique_characters(string str){
	string r_str;
	for(int i = 0; i < (int)str.length(); i++){
		if ( r_str.find(str[i]) == string::npos){
			r_str.push_back(str[i]);
		}
	}
	return r_str;
}

int gems_count(vector<string> v_str){
    int char_count[26];

	for (int i = 0; i < 26; i++) {
		char_count[i] = 0;
	}

	for (vector<string>::iterator it = v_str.begin(); it != v_str.end(); it++) {
		string w_str = unique_characters((*it));
		for (int i = 0; i < (int)w_str.length(); i++) {
			char_count[w_str[i] - 'a']++;
		}
	}

	int count = 0;
	for(int i = 0; i < 26; i++){
		if (char_count[i] == (int)v_str.size()){
			count++;
		}
	}

   return count;
}

int chr_deleted_to_anagram(string str1, string str2){

	string c_str2 = str1;
	for (int i = 0; i < (int)c_str2.length(); i++) {
		size_t found_in1 = str1.find(c_str2[i]);
		size_t found_in2 = str2.find(c_str2[i]);
		if (  found_in1 != string::npos && found_in2 != string::npos) {
			str1.erase(found_in1,1);
			str2.erase(found_in2,1);
		}
	}

	return str1.length()+str2.length();
}

int min_swap_to_anagram (string str){

	int n = str.length();
	if ( n%2 != 0){
		return -1;
	}
	string sub_str1 = str.substr(0, n/2);
    string sub_str2 = str.substr(n/2, n);

	return chr_deleted_to_anagram(sub_str1, sub_str2)/2;
}

string common_sub_str(string str1, string str2){
	if (str2.find_first_of(str1) != string::npos) {
		return "YES";
	}
	return "NO";
}

int anagramatic_pair_count(string str){
	int n = str.length();
	int sub_str_n = 1;
	map<string, int> anagrams;

	while (sub_str_n < n) {
		for (int i = 0; i < n - sub_str_n + 1; i++) {
			string sub_str = str.substr(i, sub_str_n);
			sort(sub_str.begin(), sub_str.end());
			if (anagrams.find(sub_str) != anagrams.end()) {
				anagrams[sub_str]++;
			} else {
				anagrams[sub_str] = 1;
			}
		}
		sub_str_n++;
	}

	int pairCount = 0;
	for (map<string, int>::iterator it = anagrams.begin(); it != anagrams.end(); ++it) {
		if (it->second > 1) {
			pairCount += (it->second * (it->second - 1)) / 2;
		}
	}
	return pairCount;
}

int index_to_remove(string str){
    int n = str.length();
	int i = 0;
	int j = n-1;

    while (i < j){
        if ( str[i] == str[j] ){
            j--;
            i++;
        }
        else{
            break;
        }
    }
    
    if(i >= j){
        return -1;
    }
    
    int l_out = i;
    int r_out = j;
    
    i++;
    while (i < j){
        if ( str[i] == str[j] ){
            j--;
            i++;
        }
        else{
            return r_out;
        }
    }
	return l_out;
}

bool is_palindrome(string str){
    int n = str.length();
	int i = 0;
	int j = n-1;

    while (i < j){
        if ( str[i] == str[j] ){
            j--;
            i++;
        }
        else{
            break;
        }
    }
	return (i>=j)?true:false;
}

string small_lexicographic_A (string S){
	if (S.empty()) return "";

	int count_chr[26];
	int needed_chr[26];
	string A;

	for(int i = 0; i < 26; count_chr[i] = 0, i++);
	for(int i = 0; i < 26; needed_chr[i] = 0, i++);
	for (int i = 0; i < (int)S.length(); count_chr[S[i]-'a'] ++, i++);
	for(int i = 0; i < 26; needed_chr[i] = count_chr[i]/2, i++);

	reverse(S.begin(), S.end());

	int index = 0, pos = -1;
	while (A.length() < S.length() / 2) {
		pos = -1;
		while (true) {
			char chr = S[index];
			if ((needed_chr[chr - 'a'] > 0) && (pos < 0 || chr < S[pos]))
				pos = index;
			count_chr[chr - 'a']--;
			if (count_chr[chr - 'a'] < needed_chr[chr - 'a'])
				break;
			index++;
		}

		for (int j = pos + 1; j < index + 1; j++)
			count_chr[S[j] - 'a']++;

		needed_chr[S[pos] - 'a']--;
		A.push_back(S[pos]);

		index = pos + 1;

	}

	return A;
}

int index_to_convert_to_palindrome(string str){
    int n = str.length();
	int i = 0;
	int j = n-1;
    int index = 0;
    
    while (i < j){
    	if ( str[i] == str[j] ){
    		j--;
    		i++;
        }
        else{
        	char chr1 = str[i]
        	char chr2 = str[j];
			if (chr1 < chr2) {
				while (chr1 < chr2 && chr2 > 'a') {
					chr2--;
					index++;
				}
			} else {
				while (chr1 > chr2 && chr1 > 'a') {
					chr1--;
					index++;
				}
			}
			j--;
			i++;
        }
    }
    return index;
}

int maximun_children_length (string str1, string str2){
	string s;
	vector<int> pos1;
	vector<int> pos2;

	if (str1.length() != str2.length()){
		return 0;
	}

	for(int i = 0; i < (int)str2.length(); i++){

		if( str1.find(str2[i]) != string::npos ){
			int pos_in_1 = std::distance(str1.begin(), find(str1.begin(),str1.end(),str2[i]));
			pos1.push_back(pos_in_1);
			int pos_in_2 = std::distance(str2.begin(),
					find(str2.begin(), str2.end(), str2[i]));
			pos2.push_back(pos_in_2);
			s.push_back(str2[i]);
		}
	}



	cout << str1 << endl;
	cout << str2 << endl;

	for (int i = 0; i < (int)str1.length(); cout << i, i++);
	cout << endl;
	for (vector<int>::iterator it = pos1.begin(); it != pos1.end();
				cout << *it, it++)
			;
		cout << endl;
	for (vector<int>::iterator it = pos2.begin(); it != pos2.end();
			cout << *it, it++)
		;
	cout << endl;
	cout << s << endl;

	return s.length();
}

int lcs_memoized(string S, int n, string T, int m){

	int result = 0;
	if (arr[n][m] != -1){
		return arr[n][m];
	}
	if (n == (int)S.length() || m == (int)T.length()){
		return 0;
	}
	if(S[n] == T[m]){
		result = 1+ lcs(S, n+1, T, m+1);
	} else {
		result = max(lcs(S, n+1, T, m), lcs(S, n, T, m+1));
		arr[n][m] = result;
	}
	return result;
}

int lcs(string S, string T){
	int n = S.length();
	    int m = T.length();
	    for (int i = 0; i < n; i++){
	        for(int j = 0; j < m; j++){
	            if (i == 0 || j == 0){
	                arr[i][j] = 0;
	            }
	            if(S[i] == T [j]){
	                arr[i+1][j+1] = arr[i][j]+1;
	            } else{
	              arr[i+1][j+1] = max(arr[i+1][j], arr[i][j+1]);  
	            }
	        }
	    }
	   return arr[n][m];
}
