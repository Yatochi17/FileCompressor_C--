#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Function to compress the file using Run-Length Encoding (RLE)
void compressFile(const string& inputFile, const string& outputFile) {
    // Open the input file in binary mode
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    // Open the output file in binary mode
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    char currentChar;
    char previousChar;
    int count = 1;

    // Read the first character
    if (inFile.get(previousChar)) {
        while (inFile.get(currentChar)) {
            if (currentChar == previousChar) {
                count++;  // If the same character repeats, increment the count
            } else {
                // Write the count and the character to the output file
                outFile.write(reinterpret_cast<char*>(&count), sizeof(count));
                outFile.put(previousChar);

                // Reset count and update previousChar
                count = 1;
                previousChar = currentChar;
            }
        }
        // Write the last group of characters
        outFile.write(reinterpret_cast<char*>(&count), sizeof(count));
        outFile.put(previousChar);
    }

    inFile.close();
    outFile.close();
    cout << "File compressed successfully!" << endl;
}

// Function to decompress the file using Run-Length Encoding (RLE)
void decompressFile(const string& inputFile, const string& outputFile) {
    // Open the input file in binary mode
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    // Open the output file in binary mode
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    int count;
    char currentChar;

    // Read the compressed file and decode it
    while (inFile.read(reinterpret_cast<char*>(&count), sizeof(count)) && inFile.get(currentChar)) {
        // Write the character 'count' times to the output file
        for (int i = 0; i < count; i++) {
            outFile.put(currentChar);
        }
    }

    inFile.close();
    outFile.close();
    cout << "File decompressed successfully!" << endl;
}

int main() {
    string command;
    string inputFile, outputFile;

    while (true) {
        cout << "\nEnter a command (compress, decompress, or exit): ";
        cin >> command;

        if (command == "compress") {
            cout << "Enter the name of the input file: ";
            cin >> inputFile;
            cout << "Enter the name of the output compressed file: ";
            cin >> outputFile;
            compressFile(inputFile, outputFile);
        } else if (command == "decompress") {
            cout << "Enter the name of the input compressed file: ";
            cin >> inputFile;
            cout << "Enter the name of the output decompressed file: ";
            cin >> outputFile;
            decompressFile(inputFile, outputFile);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
