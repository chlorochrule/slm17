// @author: Naoto MINAMI (201720866)
// good-turing + katz

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int bigram_word = 28-1; //て
int trigram_word = 24-1; //し

vector<int> read_sentence() {

    vector<int> sen;
    char sep = ' ';
    string buf;

    while (getline(cin, buf)) {
        stringstream ss(buf);
        while (getline(ss, buf, sep)) {
            sen.push_back(stoi(buf)-1);
        }
    }

    return sen;
}

int main(int argc, char const *argv[]) {

    vector<int> sen = read_sentence();
    int n_sen = sen.size();
    int n_words = *max_element(sen.begin(), sen.end()) + 1;

    vector<double> unigram(n_words);
    vector<double> bigram(n_words);
    vector<double> trigram(n_words);

    vector<int> freq(n_words, 0);
    vector<int> n_freq(n_sen, 0);


    // unigram
    double total_unigram = 0.0;

    for(int i = 0; i < n_sen; i++) {
        freq[sen[i]]++;
    }

    for (int i = 0; i < n_words; i++) {
        n_freq[freq[i]]++;
    }

    for (int i = 0; i < n_words; i++) {
        if (n_freq[freq[i]+1] == 0 or freq[i] > 20) {
            unigram[i] = (double)(freq[i]) / (double)n_sen;
        } else {
            unigram[i] = (double)(n_freq[freq[i]+1] * (freq[i]+1)) / (double)(n_sen * n_freq[freq[i]]);
        }
        total_unigram += unigram[i];
    }
    for (int i = 0; i < n_words; i++) {
        unigram[i] /= total_unigram;
        // initialize
        n_freq[freq[i]] = 0;
        freq[i] = 0;
    }


    // bigram
    double total_bigram = 0.0;
    int bigram_freq = 0;

    for (int i = 0; i < n_sen-1; i++) {
        if (sen[i] == bigram_word) {
            freq[sen[i+1]]++;
            bigram_freq++;
        }
    }

    for (int i = 0; i < n_words; i++) {
        n_freq[freq[i]]++;
    }

    for (int i = 0; i < n_words; i++) {
        if (freq[i] == 0) {
            bigram[i] = unigram[i] * (double)n_freq[1] / (double)bigram_freq;
        } else if (n_freq[freq[i]+1] > n_freq[i] or n_freq[freq[i]+1] == 0 or freq[i] > 15) {
            bigram[i] = (double)(freq[i]) / (double)bigram_freq;
        } else {
            bigram[i] = (double)(n_freq[freq[i]+1] * (freq[i]+1)) / (double)(bigram_freq * n_freq[freq[i]]);
        }
        total_bigram += bigram[i];
    }

    for (int i = 0; i < n_words; i++) {
        bigram[i] /= total_bigram;
        // initialize
        n_freq[freq[i]] = 0;
        freq[i] = 0;
    }


    // trigram
    int trigram_freq = 0;
    double total_trigram = 0.0;

    for (int i = 0; i < n_sen-2; i++) {
        if (sen[i] == trigram_word and sen[i+1] == bigram_word) {
            freq[sen[i+2]]++;
            trigram_freq++;
        }
    }

    for (int i = 0; i < n_words; i++) {
        n_freq[freq[i]]++;
    }

    for (int i = 0; i < n_words; i++) {
        if (freq[i] == 0) {
            trigram[i] = bigram[i] * (double)n_freq[1] / (double)trigram_freq;
        } else if (n_freq[freq[i]+1] > n_freq[i] or n_freq[freq[i]+1] == 0 or freq[i] > 10) {
            trigram[i] = (double)(freq[i]) / (double)trigram_freq;
        } else {
            trigram[i] = (double)(n_freq[freq[i]+1] * (freq[i]+1)) / (double)(trigram_freq * n_freq[freq[i]]);
        }
        total_trigram += trigram[i];
    }

    for (int i = 0; i < n_words; i++) {
        trigram[i] /= total_trigram;
        // initialize
        n_freq[freq[i]] = 0;
        freq[i] = 0;
    }

    for (int i = 0; i < n_words; i++) {
        printf("%20.17e\n",	bigram[i]);
        // printf("%20.17e\n",	trigram[i]);
    }

    return 0;
}
