# Search Engine Project
**Author:** Filiz İpek Oktay - 30780

### Overview
This C++ program, developed for CS300 Homework 2, serves as a search engine using AVL Trees. The application reads input from multiple files, builds an AVL Tree to store word frequencies across documents, and allows users to query the frequency of specific words. Additionally, users can remove words from the AVL Tree.

### Program Structure
- **Main Program:**
  - Reads a specified number of input files, extracts words, and constructs an AVL Tree to store word frequencies.
  - Processes user queries, allowing word frequency queries and word removal operations from the AVL Tree.

- **AVLSearchTree:**
  - An AVL Tree implementation for efficient storage and retrieval of word frequencies.
  
- **WordItem Structure:**
  - Represents a word in the AVL Tree with associated document information.

- **DocumentItem Structure:**
  - Holds information about a document, including its name and the frequency of the associated word.

### Instructions
1. **Input Files:**
   - Enter the number of input files.
   - Provide names for each input file.

2. **Query Words:**
   - Enter words or queries in a single line.
   - Type "REMOVE" followed by a space and the word to remove it from the AVL Tree.

3. **End of Input:**
   - Type "ENDOFINPUT" to end the program.

### Example Usage
1. **Build AVL Tree:**
   - Input: Number of files and file names.
   - The program reads the files, extracts words, and constructs an AVL Tree.

2. **Query Word Frequencies:**
   - Input words to query their frequencies across documents.

3. **Remove Words:**
   - Input "REMOVE" followed by a space and the word to remove it from the AVL Tree.

4. **End the Program:**
   - Type "ENDOFINPUT" to exit the program.

### Notes
- This program was created as part of CS300 Homework 2.
- Users can explore, modify, and adapt the program according to their needs.
- For any questions or suggestions, please contact the author, Filiz İpek Oktay.

### Happy Word Analyzing!
Explore the power of AVL Trees in search engine with this C++ application. Analyze documents, query word frequencies, and remove unwanted words efficiently!
