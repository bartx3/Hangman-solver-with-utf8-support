# Hangman-solver-with-utf8-support

This hangman solver reads a dictionary file (it should bea text file with different phrases in different lines). You ask for a line consisting of appropriate number of __. Then the program outputs a letter. You fill out the previous line with the given letter in places where it occurs. Note that you always input the last line with new letters in their positions like in a normal game with a human plus it is not wrong-letter-proof. 

Note that I was younger when I coded that so I didn't use maps where they would actually be faster than just vectors, but the speed of the code is good enough to solve anything in languages without too many letters. All you have to do is change the dictionary file name in the code and it's ready to run.
