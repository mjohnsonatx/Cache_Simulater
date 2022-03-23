// ExtraCredit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int main()
{

    int MainMemory = pow(2, 24);
    int blockSize = pow(2, 16);
    int numBlocks = pow(2, 256)/blockSize;
    int numBlocks2 = pow(2, 128)/ blockSize;
    int i = 0;
    int a;

    int indexAddress = 0,
        tagAddress = 0,
        blockCounter = 0,
        address,
        flag,
        shift;

    double CompulsryMiss = 0.0,
        CompulsryMiss2 =0.0,
        miss = 0.0000, miss2 = 0.0000,
        hit = 0.0000, hit2 =0.0000,
        total = 0.0000, total2 =0.0000;

    double hitRatio = hit / (total + miss),
        hitRatio2 = hit2/(total2+miss2),
        CMratio = CompulsryMiss / (total + hit),
        CMratio2 = CompulsryMiss2 / (total2 + hit2);

    string str;

    int cacheArray[2][100000],
        cacheArray2[2][100000];


    for (int i = 0; i < 2; i++)   // setting all the cash with -1
        for (int j = 0; j < numBlocks; j++) {
            cacheArray[i][j] = -1;
            cacheArray2[i][j] = -1;
        }

    ifstream myFile;
    myFile.open("Trace.txt");


    if (!myFile) {
        cout << "File input failed";
        return 1;
    }
    while (myFile) {
        myFile >> str;
        myFile >> hex >> a;
        myFile.ignore();
        cout << a << endl;

        a = stoi(str, 0, 16);
////////////////////////////////////////
////////// 256 version /////////////////
////////////////////////////////////////
        address = a;
        cout << "Address: " << a << endl;
        shift = log2(blockSize);
        cout << "Shift: " << shift << endl;
        indexAddress = (address >> shift) % numBlocks;
        cout << "IndexAddress: " << indexAddress << endl;
        shift = log2(numBlocks + blockSize);
        cout << "Shift2: " << shift << endl;
        tagAddress = address >> shift;
        cout << "Tag Address: " << tagAddress << endl;

        if (cacheArray[0][indexAddress] == tagAddress){
            hit++;
            cout << "hit working" << endl;
            total++;
            }

        else {
            cacheArray[0][indexAddress] = tagAddress;
            for (int i = 0; i < numBlocks; i++) {
                if (cacheArray[1][i] != 1) {
                    i = numBlocks;
                    }
                }



                if (cacheArray[1][indexAddress] == 1) {
                    miss++;
                    total++;
                    //cout << "Miss" << endl;
                    }

                else {
                    CompulsryMiss++;
                    total++;
                    //cout << "CM " << endl;
                    }
                }
            cacheArray[1][indexAddress] = 1;
/////////////////////////////////////////////////
///////////////// 128 version ///////////////////
/////////////////////////////////////////////////
            address = a;
            cout << "Address: " << a << endl;
            shift = log2(blockSize);
            cout << "Shift: " << shift << endl;
            indexAddress = (address >> shift) % numBlocks2;
            cout << "IndexAddress: " << indexAddress << endl;
            shift = log2(numBlocks2 + blockSize);
            cout << "Shift2: " << shift << endl;
            tagAddress = address >> shift;
            cout << "Tag Address: " << tagAddress << endl;

            if (cacheArray2[0][indexAddress] == tagAddress){
                hit2++;
                cout << "hit working" << endl;
                total2++;
            }

            else {
                cacheArray2[0][indexAddress] = tagAddress;
                for (int i = 0; i < numBlocks2; i++) {
                    if (cacheArray2[1][i] != 1) {
                        i = numBlocks2;
                    }
                }



                if (cacheArray2[1][indexAddress] == 1) {
                    miss2++;
                    total2++;
                    cout << "Miss2" << endl;
                    }

                else {
                    CompulsryMiss2++;
                    total2++;
                    cout << "CM2 " << endl;
                    }
                }
            cacheArray2[1][indexAddress] = 1;
            }

        cout << "CM: " << CompulsryMiss << " Miss: " << miss << " Hit: " << hit << endl
             << "Hit Ratio : " << hitRatio << ", " << " Compulsory Miss: "
             << endl << CMratio << endl;
        cout << "CM2: " << CompulsryMiss << " Miss2: " << miss << " Hit2: " << hit << endl
             << "Hit Ratio2 :" << hitRatio2 << ", " << " Compulsory Miss ratio"
             << endl << CMratio2 << endl;

        return EXIT_SUCCESS;
    }
