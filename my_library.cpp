

#include <iostream>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
#include <typeinfo>
#include <limits>
#include <functional>

using namespace std;


int ntpdatesync(const std::string &host_url, int port, std::string& str_error) {
	int ret = 0;
	struct protoent *proto;
	int sock;

	proto = getprotobyname("udp");
	ret = sock = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
	if (-1 != ret) {
		struct sockaddr_in server_addr;
		int __port = port;         //NTP is port 123
		char *hostname = (char *) host_url.data();
		unsigned char msg[48] = { 010, 0, 0, 0, 0, 0, 0, 0, 0 };

		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(hostname);
		server_addr.sin_port = htons(__port);
		ret = sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *) &server_addr,
				sizeof(server_addr));

		if (-1 != ret) {
			int maxlen = 1024;
			unsigned long buf[maxlen];
			struct sockaddr saddr;

			socklen_t saddr_l = sizeof(saddr);
			ret = recvfrom(sock, buf, 48, 0, &saddr, &saddr_l);
			if (-1 != ret) {
				long tmit;
				tmit = ntohl((time_t) buf[4]);
				tmit -= 2208988800U;
				std::cout << "npt server time is " << std::put_time(std::localtime(&tmit), "%c %Z") << std::endl;
				auto tdiff = time(0) - tmit;
				if (0 != tdiff){
					ret = stime(&tmit);
					if (-1 == ret) {
						str_error = std::strerror(errno);
					}
				} else {
					ret = 1;
				}
			} else {
				str_error = std::strerror(errno);
			}
		} else {
			str_error = std::strerror(errno);
		}
	} else {
		str_error = std::strerror(errno);
	}
 return ret;
}

int dns_lookup(const char *host, sockaddr_in *out, std::string& str_error)
{
    struct addrinfo *result;
    int ret = getaddrinfo(host, "ntp", NULL, &result);
	if (0 == ret) {
		for (struct addrinfo *p = result; p; p = p->ai_next) {
			if (p->ai_family != AF_INET)
				continue;

			memcpy(out, p->ai_addr, sizeof(*out));
		}
	} else {
		str_error = std::strerror(errno);
	}

    freeaddrinfo(result);
    return ret;
}

unsigned long long combine(unsigned int low, unsigned int high) {
	return (((unsigned long long) high) << 32) | ((unsigned long long) low);
}

unsigned int high(unsigned long long combined) {
	return combined >> 32;
}

unsigned int low(unsigned long long combined) {
	int ntpdatesync(const std::string &host_url, int port, std::string& str_error) {
	int ret = 0;
	struct protoent *proto;
	int sock;

	proto = getprotobyname("udp");
	ret = sock = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
	if (-1 != ret) {
		struct sockaddr_in server_addr;
		int __port = port;         //NTP is port 123
		char *hostname = (char *) host_url.data();
		unsigned char msg[48] = { 010, 0, 0, 0, 0, 0, 0, 0, 0 };

		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(hostname);
		server_addr.sin_port = htons(__port);
		ret = sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *) &server_addr,
				sizeof(server_addr));

		if (-1 != ret) {
			int maxlen = 1024;
			unsigned long buf[maxlen];
			struct sockaddr saddr;

			socklen_t saddr_l = sizeof(saddr);
			ret = recvfrom(sock, buf, 48, 0, &saddr, &saddr_l);
			if (-1 != ret) {
				long tmit;
				tmit = ntohl((time_t) buf[4]);
				tmit -= 2208988800U;
				std::cout << "npt server time is " << std::put_time(std::localtime(&tmit), "%c %Z") << std::endl;
				auto tdiff = time(0) - tmit;
				if (0 != tdiff){
					ret = stime(&tmit);
					if (-1 == ret) {
						str_error = std::strerror(errno);
					}
				} else {
					ret = 1;
				}
			} else {
				str_error = std::strerror(errno);
			}
		} else {
			str_error = std::strerror(errno);
		}
	} else {
		str_error = std::strerror(errno);
	}
 return ret;
}

int dns_lookup(const char *host, sockaddr_in *out, std::string& str_error)
{
    struct addrinfo *result;
    int ret = getaddrinfo(host, "ntp", NULL, &result);
	if (0 == ret) {
		for (struct addrinfo *p = result; p; p = p->ai_next) {
			if (p->ai_family != AF_INET)
				continue;

			memcpy(out, p->ai_addr, sizeof(*out));
		}
	} else {
		str_error = std::strerror(errno);
	}

    freeaddrinfo(result);
    return ret;
}unsigned long long mask = numeric_limits<unsigned int>::max();
	return mask & combined;
}

template<unsigned int byte> class BITS_SET {
public:
	enum {
		B0 = (byte & 0x01) ? 1 : 0, B1 = (byte & 0x02) ? 1 : 0, 
		B2 = (byte & 0x04) ? 1 : 0, B3 = (byte & 0x08) ? 1 : 0, 
		B4 = (byte & 0x10) ? 1 : 0, B5 = (byte & 0x20) ? 1 : 0, 
		B6 = (byte & 0x40) ? 1 : 0, B7 = (byte & 0x80) ? 1 : 0,
		B8 = (byte & 0x100) ? 1 : 0, B9 = (byte & 0x200) ? 1 : 0, 
		B10 =(byte & 0x400) ? 1 : 0, B11 = (byte & 0x800) ? 1 : 0, 
		B12 =(byte & 0x1000) ? 1 : 0, B13 = (byte & 0x2000) ? 1 : 0, 
		B14 =(byte & 0x4000) ? 1 : 0, B15 = (byte & 0x8000) ? 1 : 0
	};
public:
	enum {
		RESULT = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11
				+ B12 + B13 + B14 + B15
	};
};

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

vector <int> suffixArray(string s){
	vector <int> r;
	vector <string> vs;

	vs.clear();
	for(int i = 0; i < (int)s.length(); vs.push_back(s.substr(i,s.length())), i++);

	cout << " suffixes without sorting" << endl;
	for (vector <string>::iterator it = vs.begin(); it != vs.end(); cout << *it << endl,  it++);

	sort(vs.begin(), vs.end());

	cout << " suffixes after  sorting" << endl;
	for (vector <string>::iterator it = vs.begin(); it != vs.end(); cout << *it << endl,  it++);

	int cnt[26];
	int n = s.length();
	int ind[26];
	for (int i = 0; i < 26; ind[i] = i, i++);
	for (int i = 0; i < n; cnt[i] = s[i]-'a', i++);

	cout << "before " << endl;
	// printing the position
	for (int i = 0; i < n; cout << ind[i] << "\t", i++)
		;
	cout << endl;
	// printing string
	for (int i = 0; i < n; cout << s[i] << "\t", i++)
		;
	cout << endl;
	// printing cnt
	for (int i = 0; i < n; cout << cnt[i] << "\t", i++)
		;
	cout << endl;


	int o_cnt[26];
	int o_ind[26];
	int ii =0;
	sort(cnt, ind, 0, ii, o_cnt, o_ind );

	cout << "after " << endl;
	// printing the position
	for (int i = 0; i < n; cout << o_ind[i] << "\t", i++)
		;
	cout << endl;
	// printing string
	for (int i = 0; i < n; cout << s[i] << "\t", i++)
		;
	cout << endl;
	// printing cnt
	for (int i = 0; i < n; cout << o_cnt[i] << "\t", i++)
		;
	cout << endl;

	return r;
}
void merge(vector<int>& a, size_t begin, size_t end, size_t mid) {

	size_t n = end - begin;
	std::vector<size_t> temp(n);

	size_t i = begin, j = mid, k = 0;

	while (i < mid && j < end) {
		temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
	}
	while (i < mid) {
		temp[k++] = a[i++];
	}
	while (j < end) {
		temp[k++] = a[j++];
	}

	for (size_t k = 0; k < n; k++) {
		a[begin + k] = temp[k];
	}

}

void merge_sort(vector<int>& ar, size_t begin, size_t end) {
	int mid;
	if ((end - begin) <= 1)
		return;
	mid = ((end + begin) / 2);
	merge_sort(ar, begin, mid);
	merge_sort(ar, mid, end);
	merge(ar, begin, end, mid);
}

size_t count_split_inv(vector<int>& a, size_t begin, size_t end, size_t mid) {

	size_t n = end - begin;
	std::vector<size_t> temp(n);

	size_t i = begin, j = mid, k = 0;
	size_t inv_count = 0;

	//cout << "comparing: " << endl;
			//print_list(a, begin, mid);
			//cout << "and " << endl;
			//print_list(a, mid, end);

	while (i < mid && j < end) {


		if (a[i] < a[j]) {
			temp[k++] = a[i++];
		} else {
			//cout << a[i] << " > " << a[j] << " inversion" << endl;
			temp[k++] = a[j++];
			inv_count = inv_count + (mid-i);
		}
	}
	while (i < mid) {
		temp[k++] = a[i++];
	}
	while (j < end) {
		temp[k++] = a[j++];
	}

	for (size_t k = 0; k < n; k++) {
		a[begin + k] = temp[k];
	}

	return inv_count;
}

size_t count_inv(vector<int>& ar, size_t begin, size_t end) {
	int mid;
	size_t inv_count = 0;
	if ((end - begin) > 1) {
		mid = ((end + begin) / 2);
		//cout << "begin = " << begin << " mid = " << mid << " end = " << end << endl;
		inv_count = count_inv(ar, begin, mid);
		inv_count += count_inv(ar, mid, end);
		inv_count += count_split_inv(ar, begin, end, mid);
	}

	return inv_count;
}

bool is_vowel(char a) {
	if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y') {
		return true;
	}
	return false;
}

void beautiful_world(string str) {
	size_t i = 1;
	while (i < str.length()) {
		if (str[i] == str[i - 1]) {
			cout << "No" << endl;
			return;
		}
		if (is_vowel(str[i]) && is_vowel(str[i - 1])) {
			cout << "No" << endl;
			return;
		}
		i++;
	}
	cout << "Yes" << endl;
}


size_t make_equal_length(string &str1, string &str2) {
	size_t len1 = str1.length();
	size_t len2 = str2.length();
	if (len1 < len2) {
		for (size_t i = 0; i < len2 - len1; i++)
			str1 = '0' + str1;
		return len2;
	} else if (len1 > len2) {
		for (size_t i = 0; i < len1 - len2; i++)
			str2 = '0' + str2;
	}
	return len1; // If len1 >= len2
}

string substring(string n1, size_t begin, size_t end) {
	string ret;
	for (size_t i = begin; i < end; i++) {
		ret += n1[i];
	}
	return ret;
}

string add_str(string str1, string str2) {
	string result;

	size_t length = make_equal_length(str1, str2);

	//cout << "str1=" << str1 << endl;
	//cout << "str2=" << str2 << endl;
	//cout << "+-----------------" << endl;
	//cout << "length = " << length << endl;

	int carry = 0;
	for (int i = length - 1; i >= 0; i--) {

		//cout << "i = " << i << endl;
		int a = (int) str1[i] - 48;
		//cout << "a = " << a << endl;
		int b = (int) str2[i] - 48;
		//cout << "b = " << b << endl;
		int val = a + b + carry;
		//cout << "val = " << val << endl;
		//cout << "carry " << carry << endl;
		if (val >= 10) {
			carry = 1;
			val = val - 10;
		} else {
			carry = 0;
		}
		result = to_string(val) + result;
	}
	if (carry > 0)
		result = to_string(carry) + result;

	//cout << "= " << result << endl;
	//cout << endl;
	return result;
}

string substract_str(string str1, string str2) {
	stringstream strm_result;
	string result;
	bool negative = false;
	if (strcmp(str2.c_str(), "0") == 0) {
		return str1;
	}
	if (strcmp(str1.c_str(), "0") == 0) {
		return "-" + str1;
	}

	size_t length = make_equal_length(str1, str2);

	//cout << "str1=" << str1 << endl;
			//cout << "str2=" << str2 << endl;
			//cout << "-_____________" << endl;

	if ( str1[0]-str2[0] < 0 ){
		string temp = str1;
		str1=str2;
		str2=temp;
		negative =true;
	}



	int carry = 0;
	int val = 0;
	for (int i = length - 1; i >= 0; i--) {
		//cout << "i = " << i << endl;
		int a = (int) str1[i] - 48;
		//cout << "a = " << a << endl;
		int b = (int) str2[i] - 48;
		//cout << "b = " << b << endl;
		if ((b + carry) > a) {
			val = a + 10 - (b + carry);
			carry = 1;
		} else {
			val = a - (b + carry);
			carry = 0;
		}
		//cout << "carry " << carry << endl;
		//cout << "val = " << val << endl;
		result = to_string(val)+result;
	}
	//result = strm_result.str();
//if (result[result.length() - 1] == 0)


	while (result[0] == '0')
		result.erase(0, 1);

	if (negative)
			result = "-"+result;
	//cout << "= " << result << endl;

	return result;
}

string add_zeroes(string str, int count) {
	string ret = str;
	for (int i = 0; i < count; i++) {
		ret = ret + "0";
	}
	return ret;
}

string str_base10_pow(string str, int exp) {
	if (strcmp(str.c_str(), "0") == 0) {
		return "0";
	}
	//int num = pow(10, exp);
	//int zero_count = digit_count(num) - 1;
	string ret = str;
	for (int i = 0; i < exp; i++) {
		ret = ret + "0";
	}
	return ret;
}

string str_karatsuba(string n1, string n2) {

#ifdef DEBUG
	cout << "str_n1=" << n1 << " str_n2=" << n2 << endl;
#endif

	if (n1.length() < 2 || n2.length() < 2) {
		std::stringstream ss;
		unsigned long val = strtoul(n1.c_str(), NULL, 0)
				* strtoul(n2.c_str(), NULL, 0);
		return to_string(val);
	}

	size_t m = n1.length();
	size_t n = n2.length();
	m = (m > n) ? m : n;
	size_t m2 = (m / 2) + (m % 2);

#ifdef DEBUG
	cout << "str_m2=" << m2 << endl;
#endif
	string h1 = substring(n1, 0, n1.length() - m2); //n1 / pow(10, m2);l
	h1 = (!h1.empty()) ? h1 : "0";
	string l1 = substract_str(n1, add_zeroes(h1, m2)); //n1 - h1*pow(10, m2);
	l1 = (!l1.empty()) ? l1 : "0";

	string h2 = substring(n2, 0, n2.length() - m2); //n2 / pow(10, m2);
	h2 = (!h2.empty()) ? h2 : "0";
	string l2 = substract_str(n2, add_zeroes(h2, m2)); //n2 - h2*pow(10, m2);
	l2 = (!l2.empty()) ? l2 : "0";

#ifdef DEBUG
	cout << "str_h1=" << h1 << endl;
	cout << "str_l1=" << l1 << endl;
	cout << "str_h2=" << h2 << endl;
	cout << "str_l2=" << l2 << endl;
#endif

	string z0 = str_karatsuba(l1, l2);
	string z1 = str_karatsuba(add_str(l1, h1), add_str(l2, h2));
	string z2 = str_karatsuba(h1, h2);

#ifdef DEBUG
	if ( z0[0] == '-' ){
		cout << " str_z0 negative value" << endl;
		cout << " l1 ="<< l1 <<" l2="<<l2 << endl;
	}
	if ( z1[0] == '-' ){
			cout << "str_z1 negative value" << endl;
			cout << " l1 ="<< l1 <<" l2="<<l2 << endl;
			cout << " h1 ="<< h1 <<" h2="<<h2 << endl;
	}
	if ( z2[0] == '-' ){
			cout << "str_z2 negative value" << endl;
			cout << " h1 ="<< h1 <<" h2="<<h2 << endl;
	}
#endif


#ifdef DEBUG
	cout << "str_z0=" << z0 << endl;
	cout << "str_z1=" << z1 << endl;
	cout << "str_z2=" << z2 <<endl;
#endif

	string a = str_base10_pow(z2, 2 * m2);
	string b = str_base10_pow(substract_str(substract_str(z1, z2), z0), m2);
	string c = add_str(add_str(a, b), z0);

#ifdef DEBUG
	cout << "here m2=" << m2 << endl;
	cout << "str_a=" << a << endl;
	cout << "str_b=" << b << endl;
	cout << "str_c=" << c <<endl;
	if ( c[0] == '-' ){
				cout << "str_c negative value" << endl;
		}
#endif

	return c; //(z2*pow(10,2*m2))+((z1-z2-z0)*pow(10,m2))+z0;
}

vector<int> load_vector_from_file(string file_name) {
	vector<int> ret;
	ifstream in_stream;
	string line;
	in_stream.open(file_name.c_str(), std::ifstream::in);
	if ( !in_stream.is_open() ) {
		cout << "error while opening file" << endl;
	}
	while (getline(in_stream, line)) {

		// processing line
		long int num = strtol(line.c_str(), NULL, 0);
		ret.push_back(num);

	}
	if (in_stream.bad())
		cout << "error while reading file" << endl;
	in_stream.close();

	return ret;
}

static void swap(vector<int> &arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

static int left_partition(vector<int> &arr, int l, int r) {
	int pivot = arr[l];
	int i = l + 1;

	for (int j = i; j < r; j++) {
		if (arr[j] < pivot) {
			if (i != j)
				swap(arr, j, i);
			i++;
		}
	}
	swap(arr, i - 1, l);
	return i - 1;
}

static int right_partition(vector<int> &arr, int l, int r) {
	int pivot = arr[r - 1];

	int i = l;
	for (int j = i; j < r - 1; j++) {
		if (arr[j] < pivot) {
			if (i != j)
				swap(arr, i, j);
			i++;
		}
	}
	swap(arr, i, r - 1);
	return i;
}

int get_median(vector<int> arr, int a, int b, int c) {
	if ((arr[a] - arr[b]) * (arr[b] - arr[c]) > 0)
		return b;
	if ((arr[a] - arr[b]) * (arr[a] - arr[c]) > 0)
		return c;
	return a;
}

static int median_partition(vector<int> &arr, int l, int r) {
	int lo = l;
	int pivot = arr[lo];
	int i = l + 1;
	for (int j = i; j < r; j++) {
		if (arr[j] < pivot) {
			if (i != j)
				swap(arr, j, i);
			i++;
		}
	}
	swap(arr, i - 1, lo);
	return i - 1;
}

static int quik_sort_left_pivot(vector<int> &arr, int l, int r) {
	int m = 0;
	if (l < r) {
		m = (r - l) - 1;
		int p = left_partition(arr, l, r);
		m += quik_sort_left_pivot(arr, l, p );
		m += quik_sort_left_pivot(arr, p + 1, r);
	}
	return m;
}

static int quik_sort_right_pivot(vector<int> &arr, int l, int r) {
	int m = 0;
	if (l < r) {
		swap(arr, l, r-1);
		m = (r - l) - 1;
		int p = left_partition(arr, l, r);
		m += quik_sort_right_pivot(arr, l, p);
		m += quik_sort_right_pivot(arr, p + 1, r);
	}
	return m;
}


static int quik_sort_median_pivot(vector<int> &arr, int l, int r) {
	int m = 0;
	if (l < r) {
		int mid_index = ( ((r + l) % 2) > 0 )?((r + l) / 2):((r + l) / 2) - 1;
		mid_index = (mid_index < l) ? l : mid_index;
		int median_index = get_median(arr, l, mid_index, r - 1);

		swap(arr, l, median_index);
		m = (r - l) - 1;
		int p = left_partition(arr, l, r);
		m += quik_sort_median_pivot(arr, l, p);
		m += quik_sort_median_pivot(arr, p + 1, r);
	}
	return m;
}

// Implementation for RSelection
//....
//


struct Vertex
{
    int val;
};

struct Edge
{
    int src, dest;
};

struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    Vertex* vertices;
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};

// A structure to represent a subset for union-find
struct subset
{
    int parent;
   // int rank;
};

// Function prototypes for union-find (These functions are defined
// after kargerMinCut() )
int find(int subsets[], int i);
void Union(int subsets[], int x, int y);

// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always
int kargerMinCut(struct Graph* graph){
    // Get data of given graph
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;

    // Allocate memory for creating V subsets.
    int *subsets = new int[V];

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v] = v;
    }

    // Initially there are V vertices in
    // contracted graph
    int vertices = V;

    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices > 2)
    {
       // Pick a random edge
       int i = rand() % E;

       // Find vertices (or sets) of two corners
       // of current edge
       int subset1 = find(subsets, edge[i].src);
       int subset2 = find(subsets, edge[i].dest);

       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
         continue;

       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
          //printf("Contracting edge %d-%d\n",
          //       edge[i].src, edge[i].dest);
          vertices--;
          Union(subsets, subset1, subset2);
       }
    }

    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2)
          cutedges++;
    }

    return cutedges;
}

int find_vertex_index(vector<int> vertices, int val) {
	size_t ret = -1;
	for (size_t i = 0; i < vertices.size(); i++) {
		if ( vertices.at(i) == val ) {
			ret = i;
			break;
		}
	}
	return ret;
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(int subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i] != i)
      subsets[i] = find(subsets, subsets[i]);

    return subsets[i];
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(int subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
//    if (subsets[xroot].rank < subsets[yroot].rank)
//        subsets[xroot].parent = yroot;
//    else if (subsets[xroot].rank > subsets[yroot].rank)
//        subsets[yroot].parent = xroot;
//
//    // If ranks are same, then make one as root and
//    // increment its rank by one
//    else
//    {
        subsets[yroot] = xroot;
       // subsets[xroot].rank++;
//    }
}

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;

    graph->vertices = new Vertex[V];
    graph->edge = new Edge[E];
    return graph;
}

void load_graph_from_file(string file_name, vector <int> *vertices, vector < pair <int,int> >* edges) {

	ifstream in_stream;
	string line;
	in_stream.open(file_name.c_str(), std::ifstream::in);
	if (!in_stream.is_open()) {
		cout << "error while opening file" << endl;
	}
	while (getline(in_stream, line)) {
		char *s_nxt;
		char * pch;

		long int __src = strtol(line.c_str(), &s_nxt, 0);
		vertices->push_back(__src);
		s_nxt++;
		pch = strtok(s_nxt, "\t\r");
		while (pch != NULL) {
			int __dest = atoi(pch);
			edges->push_back(make_pair(__src,__dest));
			pch = strtok(NULL, "\t\r");
		}
	}
	if (in_stream.bad())
		cout << "error while reading file" << endl;
	in_stream.close();
}

//reimplement
void print_graph(st_graph *graph) {
	for (size_t i = 0; i < graph->_vertices.size(); i++) {
		cout << "vertex[" << i << "] = " << graph->_vertices.at(i).val << endl;
	}

	cout << "edges count = " << graph->_edges.size() << endl;
	for (size_t i = 0; i < graph->_edges.size(); i++) {
		cout << "edge[" << i << "] = ( " << graph->_edges.at(i).src->val
				<< " ) ==== ( " << graph->_edges.at(i).dest->val << " )"
				<< endl;
	}
}

int strfind(string str1, string str2){
	for (size_t i = 0; i < str1.length(); i++) {
		size_t j = 0, k = i;
		while (str1[k] == str2[j] && j < str2.length()) {
			k++;j++;
		}
		if (j == str2.length() )
			return i;
	}
	return -1;
}

string str_exp_to_str_int(string exp_str){
	string num;
	// find if the string has the pattern e|symbol|exponent looking for the first element e
	int i = strfind(exp_str,"e");
	char str_t[i+1];

	if (i > 0) { // if it doe not have e is a regular number
		// copy the first element
		strncpy(str_t, exp_str.c_str(), i);
		str_t[i] = '\0';
		num += str_t[0];
		// jump the point or comma and copy the rest of the elements
		for (size_t j = 2; j < (sizeof(str_t) / sizeof(char)) -1 ; j++) {
			num += str_t[j];
		}
		// determine if the symbol is + or - (for radios we will always work with positives)
		if (exp_str[i + 1] == '+') {
			i++;
			// get the exponent number
			string exp;
			for (size_t j = i + 1; j < sizeof(exp_str) / sizeof(char); j++) {
				exp += exp_str[j];
			}
			size_t i_exp = atoi(exp.c_str());
			//add exponent amount of zeroes
			while (num.length() < (i_exp+1) ){
				num += "0";
			}
		}
	}
	else {
		num = exp_str;
	}
	return num;
}

typedef priority_queue<unsigned int> type_H_low;
typedef priority_queue<unsigned int, std::vector<unsigned int>, std::greater<unsigned int> > type_H_high;

size_t signum(int left, int right) {
	if (left == right){
		return 0;
	}
	return (left < right)?-1:1;
}

void getMedian( unsigned int x_i, unsigned int &m, type_H_low *l, type_H_high *r) {
	int sig = signum( l->size(), r->size() );

	switch (sig) {
	case 1: // There are more elements in left (max) heap
		if (x_i < m) {
			r->push(l->top());
			l->pop();
			l->push(x_i);
		} else {
			r->push(x_i);
		}
		break;

    case 0: // The left and right heaps contain same number of elements
		if (x_i < m){
			l->push(x_i);
		} else {
			r->push(x_i);
		}
        break;

    case -1: // There are more elements in right (min) heap
		if (x_i < m){
			l->push(x_i);
		} else {
			l->push(r->top());
			r->pop();
			r->push(x_i);
		}
        break;
    }

	if (l->size() == r->size()){
		m = l->top();
	} else if (l->size() > r->size()){
		m = l->top();
	} else {
		m = r->top();
	}

    return;
}

void printMedian(vector<unsigned int> v) {
	unsigned int median = 0;
	long int sum = 0;
	type_H_low  H_low;
	type_H_high H_high;

	for (vector<unsigned int>::iterator x_i = v.begin(); x_i != v.end(); x_i++) {
		getMedian(*x_i, median, &H_low, &H_high);
		sum += median;
		cout << median << endl;
	}

	cout << " sum = " << sum%10000 << endl;
}

void print2Sum(tr1::unordered_set<long int> v, long int low, long int high) {
	tr1::unordered_set<long int> set;
	size_t count = 0;
	tr1::unordered_set<long int>::iterator x = v.begin();
	while (x != v.end()) {
		long int y = low - *x;
		while (y <= high - *x) {
			if (v.find(y) != v.end()) {
				if (set.find(*x + y) == set.end()) {
					set.insert(*x + y);
					count++;
				}
			}
			y++;
		}
		x++;
	}
	cout << "total number of distinctive pairs = " << count << endl;
}

struct job {
	int num;
	int weight;
	int length;
};

bool difference(job a, job b) {

	int l = (a.weight - a.length);
	int r = (b.weight - b.length);

	if (l == r) {
		return (a.weight > b.weight);
	}
	return (l > r);
}

bool ratio(job a, job b) {

	float l = ((float) a.weight / (float) a.length);
	float r = ((float) b.weight / (float) b.length);

	if (l == r) {
		return (a.weight > b.weight);
	}
	return (l > r);
}

void load_jobs(string file_name, vector<job> &jobs) {
	ifstream in_stream;
	string line;
	in_stream.open(file_name.c_str(), std::ifstream::in);
	if (!in_stream.is_open()) {
		cout << "error while opening file" << endl;
		return;
	}
	getline(in_stream, line);
	size_t count = 0;
	count = strtol(line.c_str(), NULL, 0);

	for (size_t i = 0; i < count && !in_stream.bad(); i++) {
		getline(in_stream, line);
		job a;
		char *s_nxt;
		a.num = i + 1;
		a.weight = strtol(line.c_str(), &s_nxt, 0);
		s_nxt++;
		a.length = strtol(s_nxt, NULL, 0);

		jobs.push_back(a);
	}
	if (in_stream.bad())
		cout << "error while reading file" << endl;
	in_stream.close();
}

void print_jobs(vector<job> jobs) {
	for (vector<job>::iterator it = jobs.begin(); it != jobs.end(); it++) {
		cout << "job[" << (*it).num << "] weight = " << (*it).weight
				<< " length = " << (*it).length << endl;
		;
	}
}

long int weighted_sum_of_completion_times(vector<job> jobs) {
	long ret = 0;
	long sum_length = 0;
	for (vector<job>::iterator it = jobs.begin(); it != jobs.end(); it++) {
		sum_length += (*it).length;
		ret += ((*it).weight * sum_length);
	}
	return ret;
}

struct node {
	int dest;
	int weight;
};

typedef vector<node> adj_nodes;

struct adj_list_elem {
	long vertex;
	adj_nodes adj_list_node;
};

struct graph {
	size_t V, E;
	vector<adj_list_elem> array;
};

int find(vector<adj_list_elem> array, long element) {
	int ret = 0;
	for (vector<adj_list_elem>::iterator it = array.begin(); it != array.end();
			it++) {
		if ((*it).vertex == element) {
			return ret;
		}
		ret++;
	}
	return -1;
}

void load_graph_from_file3(string file_name, graph &graph) {

	ifstream in_stream;
	string line;
	in_stream.open(file_name.c_str(), std::ifstream::in);
	if (!in_stream.is_open()) {
		cout << "error while opening file" << endl;
		return;
	}
	char *s_nxt, *s_nxt1;

	getline(in_stream, line);
	graph.V = strtol(line.c_str(), &s_nxt, 0);
	s_nxt++;
	graph.E = strtol(s_nxt, NULL, 0);

	while (getline(in_stream, line)) {

		long __src = strtol(line.c_str(), &s_nxt, 0);
		s_nxt++;
		long __dest = strtol(s_nxt, &s_nxt1, 0);
		s_nxt1++;
		long __weight = strtol(s_nxt1, NULL, 0);

		node src_dest_edge;
		src_dest_edge.dest = __dest;
		src_dest_edge.weight = __weight;

		node dest_src_edge;
		dest_src_edge.dest = __src;
		dest_src_edge.weight = __weight;

		int find_res;

		find_res = find(graph.array, __src);
		if (find_res == -1) {
			adj_list_elem adj_list_node;
			adj_list_node.vertex = __src;
			adj_list_node.adj_list_node.push_back(src_dest_edge);
			graph.array.push_back(adj_list_node);
		} else {
			graph.array[find_res].adj_list_node.push_back(src_dest_edge);
		}

		find_res = find(graph.array, __dest);
		if (find_res == -1) {
			adj_list_elem adj_list_node;
			adj_list_node.vertex = __dest;
			adj_list_node.adj_list_node.push_back(dest_src_edge);
			graph.array.push_back(adj_list_node);
		} else {
			graph.array[find_res].adj_list_node.push_back(dest_src_edge);
		}
	}
	if (in_stream.bad())
		cout << "error while reading file" << endl;
	in_stream.close();
}

void print_st_graph(graph graph) {
	cout << "graph.V = " << graph.V << endl;
	cout << "graph.E = " << graph.E << endl;
	for (vector<adj_list_elem>::iterator it = graph.array.begin();
			it != graph.array.end(); it++) {
		for (adj_nodes::iterator node = (*it).adj_list_node.begin();
				node != (*it).adj_list_node.end(); node++) {
			cout << (*it).vertex << "-" << (*node).dest << " ("
					<< (*node).weight << ")" << endl;
		}

	}
}

adj_nodes& find(graph i_graph, long element){
	adj_nodes ret;
	for ( vector<adj_list_elem>::iterator it = i_graph.array.begin(); it != i_graph.array.end(); it++){
		if ( (*it).vertex == element){
			return (*it).adj_list_node;
		}
	}
	return ret;
}

adj_list_elem get_cheap_edge(vector<long> &X, graph i_graph) {

	adj_list_elem r;
	node ret;
	ret.weight = INT_MAX;
	ret.dest = 0;

	for (vector<long>::iterator it = X.begin(); it != X.end(); it++) {
		adj_nodes nodes = find(i_graph, (*it));
		for (adj_nodes::iterator jt = nodes.begin(); jt != nodes.end(); jt++) {
			if (((*jt).weight < ret.weight)
					&& (find(X.begin(), X.end(), (*jt).dest) == X.end())) {
				ret.weight = (*jt).weight;
				ret.dest = (*jt).dest;
				r.vertex = (*it);
			}
		}
	}
	r.adj_list_node.push_back(ret);
	X.push_back(ret.dest);
	return r;
}

void prim_mst(graph graph, long &prim_result) {

	vector<long> X;
	X.push_back(graph.array[0].vertex);
	vector<adj_list_elem> T;

	while (X.size() < graph.V) {
		adj_list_elem ret = get_cheap_edge(X, graph);
		T.push_back(ret);
	}

	for (vector<adj_list_elem>::iterator it = T.begin(); it != T.end(); it++) {
		for (adj_nodes::iterator node = (*it).adj_list_node.begin();
				node != (*it).adj_list_node.end(); node++) {
			prim_result += (*node).weight;
		}
	}
}

void* memcpy_s(void *__restrict dest, size_t offset, const void *__restrict src, size_t count){
	return memcpy((char*)dest+offset, src, count );
}

int main() {

	std::string error;
	sockaddr_in addr_in;
	int port = 123;
	int i = 0;

	std::string host = "0.pool.ntp.org";

	i = dns_lookup(host.c_str(), &addr_in, error);
	if (0 == i) {
		char buffer[INET_ADDRSTRLEN];
		inet_ntop( AF_INET, &addr_in.sin_addr, buffer, sizeof(buffer));

		std::cout << "addr: " << buffer << " port: " << addr_in.sin_port << std::endl;
		int i = ntpdatesync(buffer, port, error);
		if (0 == i) {
			std::cout << "system time has been synchronized with ntp server"
					<< std::endl;
		} else if (1 == i) {
			std::cout << "system time is synchronized with ntp server"
					<< std::endl;
		} else {
			std::cout << "ntpdate error: " << error << std::endl;
		}
	} else {
		std::cout << "dns_lookup error: " << error << std::endl;
	}
		
	vector <int> vertices;
	vector < pair <int,int> > edges;
	load_graph_from_file("kargerMinCut.txt", &vertices, &edges);
	int V = vertices.size();  // Number of vertices in graph
	int E = edges.size();  // Number of edges in graph
	struct Graph* graph = createGraph(V, E);
	
	for (int i = 0; i< E; i++){
		graph->edge[i].src = edges[i].first-1;
		graph->edge[i].dest = edges[i].second-1;
	}
	
	int min = E; //_graph._edges.size();
	srand(time(NULL));
	for (int i = 0; i < E; i++) {
		int temp = kargerMinCut(graph); //karger_min_cut(&_graph);
		//cout << "temp = " << temp << endl;
		if ( min > temp )
			min = temp;
	}
	
	cout << "min cut = " <<  min << endl;
	
	return 0;
}
	
	
	
	
	
	
	
	

