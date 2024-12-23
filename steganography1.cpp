#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<unsigned char> readBMP(const string& filename) 
{
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    // Read the entire file into a vector
    vector<unsigned char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return buffer;
}

// Function to write BMP file from a vector
void writeBMP(const string& filename, const vector<unsigned char>& data) 
{
    ofstream file(filename, ios::binary);
    if (!file) 
    {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
}

// Function to hide a message in BMP image
void hideMessage(vector<unsigned char>& image, const string& message) {
    size_t headerSize = *(reinterpret_cast<unsigned int*>(&image[10])); // Offset to pixel data
    size_t pixelDataSize = image.size() - headerSize;

    if (message.size() * 8 > pixelDataSize) 
    {
        cerr << "Error! Message is too large..." << endl;
        exit(1); // end in error
    }

    
    string messageWithDelimiter = message + '\0'; // add delimiter on end

    size_t messageIndex = 0;
    for (size_t i = headerSize; i < image.size() && messageIndex < messageWithDelimiter.size(); ++i) 
    {
        image[i] = (image[i] & ~1) | ((messageWithDelimiter[messageIndex] >> (i - headerSize) % 8) & 1);

        if ((i - headerSize + 1) % 8 == 0) 
        {
            messageIndex++;
        }
    }
}

string extractMessage(const vector<unsigned char>& image) 
{
    size_t headerSize = *(reinterpret_cast<const unsigned int*>(&image[10]));
    string message;
    char currentChar = 0;
    size_t bitIndex = 0;

    for (size_t i = headerSize; i < image.size(); ++i) 
    {
        currentChar |= (image[i] & 1) << bitIndex;
        bitIndex++;
        // iterate in 8 iter8? lol
        if (bitIndex == 8) 
        {
            if (currentChar == '\0') break; // End of message
            message += currentChar;
            currentChar = 0;
            bitIndex = 0;
        }
    }

    return message;
}
// begin main:
int main() 
{
    string inputImage = "cover_image.bmp";
    string outputImage = "encoded_image.bmp";
    string hiddenMessage = "This is my secret message, hello world!";

    // Read the cover image
    vector<unsigned char> image = readBMP(inputImage);

    // Hide the message
    hideMessage(image, hiddenMessage);

    // Save the encoded image
    writeBMP(outputImage, image);
    cout << "Message hidden in " << outputImage << endl;

    // Read the encoded image
    vector<unsigned char> encodedImage = readBMP(outputImage);

    // Extract the message
    string extractedMessage = extractMessage(encodedImage);
    cout << "Extracted message - " << extractedMessage << endl;

    return 0; // end
}
