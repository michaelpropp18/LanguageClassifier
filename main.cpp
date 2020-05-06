#include <iostream>
#include <fstream>

int main() {
    std::string testString;
    std::cout << "Enter a phrase in English, French, Spanish, or German. The phrase should be 1 - 2 sentences.\n";
    std::cin >> testString;
    const std::string files[4] = {"english.txt", "french.txt", "spanish.txt", "german.txt"};
    const int fileCount = 4;
    double probabilities[26][26][fileCount] = {};
    for(int i = 0; i < fileCount; i++) {
        std::string myText;
        std::ifstream myFile(files[i]);
        int matrix[26][26] = {};
        while (std::getline (myFile, myText)) {
            char previous = '\0';
            for(char &c: myText) {
               if(c >= 'a' && c <= 'z') {
                   if (previous) {
                       matrix[previous - 'a'][c - 'a']++;
                       previous = c;
                    } else {
                        previous = c;
                    }
                } else if(c >= 'A' && c <= 'Z') {
                    if (previous) {
                        matrix[previous - 'a'][c - 'A']++;
                        previous = c;
                    } else {
                        previous = c + 32;
                    }
                } else {
                    previous = '\0';
                }
            }
        }
        myFile.close();
        for(int x = 0; x < 26; x++) {
            int sum = 0;
            for(int y = 0; y < 26; y++) {
                sum += matrix[x][y];
            }
            for(int y = 0; y < 26; y++) {
                probabilities[x][y][i] = std::max(0.001, ((double)matrix[x][y]) / sum);
            }
        }
    }
    double finalProbabilities [fileCount];
    for(int i = 0; i < fileCount; i++) {
        double probability = 1.0;
        int index = 0;
        while (index + 1 < testString.length()) {
            char first = testString[index];
            char second = testString[index + 1];
            if(first >= 'A' && first <= 'Z') {
                first = first + 32;
            }   
            if(second >= 'A' && second <= 'Z') {
                second = first + 32;
            }
            if(first >= 'a' && first <= 'z' && second >= 'a' && second <= 'z') {
                probability *= probabilities[first - 'a'][second - 'a'][i];
            }
            index++;
        }
        finalProbabilities[i] = probability;
    }
    double sum = 0;
    for(int i = 0; i < fileCount; i++) {
        sum += finalProbabilities[i];
    }
    for(int i = 0; i < fileCount; i++) {
        finalProbabilities[i] = finalProbabilities[i] / sum;
    }
    for(int i = 0; i < fileCount; i++) {
        std::cout << files[i] << ": " << finalProbabilities[i] << "\n";
    }
    return 0;
}