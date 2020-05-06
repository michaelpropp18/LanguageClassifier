# LanguageClassifier
A simple C++ program that classifies a user's input as English, Spanish, German, or French.  

Type "g++ Main.cpp" to compile and "./a.out" to run. Enter your phrase (preferably a few sentences long) and hit enter. 

How it works:

For each language, we create a markov chain represented by a 26 x 26 transition matrix with each column / row representing a character. Using training data, we calculate the probability of transitioning between any two characters in each language. In the matrix, matrix[x][y] = the probability of going from character x to character y.

Next, we are given a new string (the user's input). We initialize the probability to 1. For each two adjacent characters in the string, we multiply the probability variable by matrix[first_character][second_character] to find the probability of transitioning between the given sequences of characters. We ignore all non-characters in this calculation.

We then repeat this process for each of the languages. We now have 4 very small values representing the approximate probability of seeing that string in each language. We then standardize these 4 probabilities so that they add to 1, and display these to the user. 
