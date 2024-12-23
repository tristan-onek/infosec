// My personal home baked approach to B&N
// Don't use this, this is for educational purposes only, it won't work even if you try to use it without your own finishes

#include <iostream>
#include <fstream>
#include <random>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

using namespace std;

// Function to open the raw device file
int openRawDisk(const string& devicePath) 
{
    int fd = open(devicePath.c_str(), O_RDWR);
    if (fd == -1) 
    {
        cerr << "Error - Can't open device: " << devicePath << endl;
        exit(1);
    }
    return fd;
}

// Function to overwrite the disk with random data
void overwriteDisk(int fd) 
{
    const size_t blockSize = 4096; // 4 kilobyte block size
    char buffer[blockSize];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255); //Random byte

    ssize_t bytesWritten;
    size_t totalBytesWritten = 0;

    cout << "Begin disk overwrite process..." << endl;
    
    // Overwrite the disk in blocks
    while (true) 
    {
        for (size_t i = 0; i < blockSize; ++i) 
        {
            buffer[i] = static_cast<char>(dist(gen)); // random byte
        }

        bytesWritten = write(fd, buffer, blockSize);
        if (bytesWritten < 0) 
        {
            cerr << "Error - Can't write to disk..." << endl;
            break;
        }

        totalBytesWritten += bytesWritten;
        cout << "Bytes written: " << totalBytesWritten << endl;

        // Check if we've reached the end of the disk if needed?
    }

    cout << "Disk overwrite complete." << endl;
}

void deletePartitionTable(int fd) 
{
    // Imagine overwriting the partition table area goes here
    cout << "Deleting partition table (not implemented in this example)." << endl;
}

//begin main:
int main() 
{
    string devicePath = "/dev/sda"; // depends on targeted device e.g. Linux/Max/Windows/etc.
    
    // Open the raw disk (requires root privileges)
    int fd = openRawDisk(devicePath);
    
    // Overwrite the entire disk with random data
    overwriteDisk(fd);

    // Optionally delete partition tables (conceptual)
    deletePartitionTable(fd);

    // Close the disk file descriptor
    close(fd);
    
    cout << "Data wipe complete." << endl;

    return 0; // end
}
