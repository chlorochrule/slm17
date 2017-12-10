// @author: Naoto MINAMI (201720866)
// good-turing + katz

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> read_sentence() {

    vector<int> sen;
    char sep = ' ';
    string buf;

    while (getline(cin, buf, sep)) {
        sen.push_back(stoi(buf)-1);
    }

    return sen;
}

int main(int argc, char const *argv[]) {

    vector<int> sen = read_sentence();
    int n_sen = sen.size();
    int n_words = *max_element(sen.begin(), sen.end()) + 1;
    vector<int> freq(n_words, 0);

    vector<double> unigram(n_words);
    vector<double> bigram(n_words);
    vector<double> trigram(n_words);

    int min = 1000000;

    for(int i = 0; i < n_sen; i++) {
        freq[sen[i]]++;
    }

    int max_freq = *max_element(freq.begin(), freq.end());
    vector<int> dist_freq(max_freq, 0);

    for (int i = 0; i < n_words; i++) {
        dist_freq[freq[i]]++;
    }

    int total_geq2 = 0;
    for (int i = 2; i < max_freq; i++) {
        total_geq2 += dist_freq[i];
    }

    vector<double> dist_gt;

    for (int i = 0; i < n_words; i++) {
        unigram[i] = (double)dist_freq[freq[i]+1] / (double)n_words;
    }



    // for(auto word = sen.begin(); word != sen.end(); ++word) {
    //     cout << *word << endl;
    // }
}
