//CS300/Homework2
//Filiz Ipek Oktay - 30780
#include <iostream>
#include "AVLSearchTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;

// Struct for storing the document info
struct DocumentItem {
    string documentName;
    int count = 1; // Assigning the word count 1 as default
};

// Function for AVLTree removal
bool isRemove(vector<string> &wordList, AVLSearchTree<string, WordItem<string, vector<DocumentItem>>*> &avlTree) {
    // Checking if the REMOVE is given in the query
    if (wordList[0] == "REMOVE") {
        // Deleting the second word in the query from the AVLTree
        avlTree.remove(wordList[1]);
        cout << wordList[1] << " has been REMOVED\n";
        return true;
    } else {
        return false;
    }
}

int main() {
    int fileNum = 0;
    vector<string> fileName;

    // Getting input of files
    cout << "Enter number of input files: ";
    cin >> fileNum;

    // Storing the filenames in a vector
    for (int i = 0; i < fileNum; i++) {
        string file;
        cout << "Enter " << i + 1 << ". file name: ";
        cin >> file;
        fileName.push_back(file);
    }

    // Creating the AVLTree
    AVLSearchTree<string, WordItem<string, vector<DocumentItem>>*> avlTree;

    // For each file, placing the words into the AVLTree
    for (int j = 0; j < fileName.size(); j++) {
        ifstream input;
        string word, openFile = fileName[j];
        input.open(openFile.c_str()); // Opening the file

        while (input >> word) {
            // Providing case-insensitivity by turning words into lowercase
            string alphabeticChars;
            for (char c : word) {
                char lowercaseChar = tolower(c);
                if (isalpha(lowercaseChar)) {
                    alphabeticChars += lowercaseChar;
                } else {
                    break;
                }
            }

            if (alphabeticChars != "") {
                word = alphabeticChars;
                // Checking if the word is already in the AVLTree
                if (avlTree.findVal(word) != nullptr) {
                    bool newDoc = true;
                    for (int k = 0; k < avlTree.findVal(word)->value->value.size(); k++) {
                        if (avlTree.findVal(word)->value->value[k].documentName == fileName[j]) {
                            avlTree.findVal(word)->value->value[k].count++;
                            newDoc = false;
                            break;
                        }
                    }
                    if (newDoc) {
                        DocumentItem doc;
                        doc.documentName = fileName[j];
                        avlTree.findVal(word)->value->value.push_back(doc);
                    }
                } else if (avlTree.findVal(word) == nullptr) {
                    // If the word is not in the AVLTree, add it
                    vector<DocumentItem> docVec;
                    DocumentItem doc;
                    doc.documentName = fileName[j];
                    docVec.push_back(doc);
                    auto *ptr = new WordItem<string, vector<DocumentItem>>(word, docVec, nullptr, nullptr, 0);
                    avlTree.insert(word, ptr);
                }
            }
        }
        input.close();
    }

    string inputline;
    bool tryVal = false;

    // Main loop for processing user queries
    while (inputline != "ENDOFINPUT") {
        cout << "Enter queried words in one line: ";
        if (!tryVal) {
            cin.ignore();
            tryVal = true;
        }
        getline(cin, inputline);
        istringstream iss(inputline);
        vector<string> wordList;
        bool finish = false;

        // Parsing user input to create a list of words to query
        while (iss >> inputline) {
            if (inputline == "ENDOFINPUT") {
                finish = true;
                break;
            } else if (inputline == "REMOVE") {
                // If the user wants to remove a word, add "REMOVE" to the list
                string newWord = "REMOVE";
                wordList.push_back(newWord);
            } else {
                // Convert the word to lowercase before adding to the list
                string newWord;
                for (char c : inputline) {
                    char lowercaseChar = tolower(c);
                    newWord += lowercaseChar;
                }
                wordList.push_back(newWord);
            }
        }

        if (finish) {
            break; // Exit the loop if the user inputs "ENDOFINPUT"
        } else if (!isRemove(wordList, avlTree)) {
            // Check if the user wants to remove a word, if not, proceed with querying

            bool queryExistsInAnyDocument = false;

            // For each file, check if all words in the query exist
            for (int h = 0; h < fileName.size(); h++) {
                bool allWordsFoundInDocument = true;

                for (int p = 0; p < wordList.size(); p++) {
                    string temp = wordList[p];

                    if (avlTree.findVal(temp) != nullptr) {
                        bool wordFoundInDocument = false;

                        for (int j = 0; j < avlTree.findVal(temp)->value->value.size(); j++) {
                            if (avlTree.findVal(temp)->value->value[j].documentName == fileName[h]) {
                                wordFoundInDocument = true;
                                break;
                            }
                        }

                        if (!wordFoundInDocument) {
                            allWordsFoundInDocument = false;
                            break;
                        }
                    } else {
                        allWordsFoundInDocument = false;
                        break;
                    }
                }

                if (allWordsFoundInDocument) {
                    queryExistsInAnyDocument = true;

                    cout << "in Document " << fileName[h] << ", ";
                    bool first = true;

                    // Output the result for each word in the query
                    for (int y = 0; y < wordList.size(); y++) {
                        string newestWord = wordList[y];
                        if (avlTree.findVal(newestWord) != nullptr) {
                            int count = avlTree.findVal(newestWord)->value->value[h].count;
                            if (count > 0) {
                                if (!first) {
                                    cout << ", ";
                                }
                                if (count == 1) {
                                    cout << newestWord << " found 1 times";
                                } else {
                                    cout << newestWord << " found " << count << " times";
                                }
                                first = false;
                            }
                        }
                    }
                    cout << endl;
                }
            }

            // If the query doesn't exist in any document
            if (!queryExistsInAnyDocument) {
                cout << "No document contains the given query\n";
            }
        }

        cout << endl;
    }

    return 0;
}
