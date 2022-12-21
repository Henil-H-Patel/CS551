#include<bits/stdc++.h>
#include<fstream>
#include <iostream>
#include <string>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <chrono>
#include <errno.h>
#include <mutex>
extern int errno;
using namespace std;


std:: mutex mtx;
void example(int i)
{
	mtx.lock();
	
  	char buff[5000];
  	for(int i=0 ; i<5000 ; i++){
  		
  		buff[i] = 'a';	
  		
  	}
  	char readFile[20];
    string base = ".txt";
    string full = to_string(i) + base;
    int n = full.length();
    char char_array[n];
    strcpy(char_array, full.c_str());
    int data;
    int file_descriptor_write;
    // here we we use the open system call for creating the 1.txt, 2.txt and so on files, here this call creates the new file for the writing purpose only
    // now here we take the file descriptor, now the last parameters is usefull for the creating new file with the write permission only
    file_descriptor_write = open(char_array, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file_descriptor_write == -1)
    {
        // if we got value of file_descriptor is -1 then it is the failure of the case
        // we print the which types of error is occured in the code
        cout << errno;
    }
    if (file_descriptor_write < 0)
    {
        perror("r1");
        exit(1);
    }
    // now here we use the write system, here we pass the value of the open file descriptor as the reference
    // the second paramter is the buffer means write the data you want to in the file
    // and the last is the length of the buffer through these three parameters we are able write the data into the file
    // and it successfully created the 5k bytes of data in each file
    data = write(file_descriptor_write, buff,sizeof(buff));
    // now after writing the data into file, we make sure that we need to close the file
    if (close(file_descriptor_write < 0))
    {
        // if this the case this means it got the error
        perror("c1");
        exit(1);
    }
    // if we got the file_descriptor value is zero means, it is successful.
    
    int file_descriptor_read = open(char_array, O_RDONLY);
    // now here we call the read function
    int readData = read(file_descriptor_read, readFile, sizeof(readFile));
    cout << readFile << endl;
    close(file_descriptor_read);
    mtx.unlock();
}

int main()
{
    auto start = chrono::steady_clock::now();
    vector<thread> threads;

    for (int i = 0; i < 100; i++)
    {
        threads.push_back(thread(example, i));
    }
    for (auto &th : threads)
    {
        th.join();
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Time taken for 100 files " + to_string(elapsed_seconds.count()) << endl;

    return 0;
}