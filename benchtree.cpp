/*
 *Name: Matthew Schwegler
 *ID: A09293823
 *File Benchtree
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <set>
#include "BST.hpp"
#include "RST.hpp"
#include "countint.hpp"
#include <time.h>

#define TWO 2

using namespace std;

int main(int argc, char * argv[]){

    /* Variable Declarations */
    double stdev = 0;
    double avgTotal =0;
    int maxSize = 0;    //max size of tree
    int index = 1;
    int numRuns = 0;    //Number of benchmark runs to preform
    int N = 1;
    int power = 1;
    bool shuffle = false;
    bool bst = false;
    bool rst = false;
    bool set1 = false;

    //Switch statement to parse user input
    while (argv[index] != NULL ){
        //get argument
        //string word ( argv[index]);

        if( !strcmp(argv[index],"bst") )
        {
            //Code to generate BST
            bst = true;
        }
        else if ( !strcmp (argv[index], "rst") )
        {
            //Code to generate RST
            rst = true;
        }
        else if ( !strcmp(argv[index], "set" ) )
        {
            //Code to generate c++ set
            set1 = true;
        }
        else if ( !strcmp(argv[index], "shuffled" ) )
        {
            //Code to shuffle input
            shuffle = true;    
        }

        index++;
    }

    //Get the max size as 3rd user argument
    maxSize = atoi( argv[3] );


    //Get the number of benchmark runs to preform
    numRuns = atoi( argv[4] ) - 1;


    if (bst){
        BST<countint> s;

        //cout messages to user
        cout << "# Benchmarking average number of comparisons for successful find" << endl;
        cout << "# Data Structure: " << argv[1] << endl;
        cout << "# Data: " << argv[2] << endl;
        cout << "# N is powers of 2, minus 1, from 1 to " << argv[3] << endl;
        cout << "# Averaging over 5 runs for each N" << endl;
        cout << "#" << endl;
        cout << "# N    avgcomps    stdev"<< endl;

        while ( N < maxSize ){


            vector<countint> v;
            v.clear();
            for(int i = N; 0 < i  ; --i) {
                v.push_back(i);
            }


            vector<countint>::iterator vit = v.begin();
            vector<countint>::iterator ven = v.end();


            double totalSquared = 0;

            //For the number of runs passed in
            for ( int run = 0; run < numRuns; run++ ){ 

                //if user wanted elements shuffeled
                if (shuffle){
                    std::random_shuffle( v.begin(),v.end() );
                }


                //Insert into the vector
                vit = v.begin();
                s.clear();
                for(int i = 0; i < N ; i++ ){
                    //cerr << "variable being inserted: " << *vit << endl;
                    s.insert(*vit);
                    vit++;
                }

                //create avgComps variable
                double avgcomps = 0;
                //now start the count variable for find
                countint::clearcount();
                for(vit = v.begin(); vit != ven; ++vit){
                    s.find(*vit);
                }

                //now get avg computations
                avgcomps = countint::getcount() / (double) N;

                //now calculate the standard deviation
                avgTotal = avgTotal + avgcomps;

                totalSquared = totalSquared + pow(avgcomps,TWO);
            }

            //average over the amount of runs
            avgTotal = (avgTotal / numRuns);
            //get the s variable t^2/R
            totalSquared = (totalSquared/numRuns);

            stdev = sqrt(   (totalSquared) - (pow(avgTotal,TWO)) );

            //print statements
            cout << setw(6) << N << setw(10) << avgTotal << setw(15) << stdev << endl;

            //reset avgTotal
            avgTotal = 0;
            stdev = 0;
            totalSquared = 0;

            power++;
            //increase N by power of 2
            N = pow(TWO,power) -1;

        }

    }


    else if (rst){
        RST<countint> s;

        //cout messages to user
        cout << "# Benchmarking average number of comparisons for successful find" << endl;
        cout << "# Data Structure: " << argv[1] << endl;
        cout << "# Data: " << argv[2] << endl;
        cout << "# N is powers of 2, minus 1, from 1 to " << argv[3] << endl;
        cout << "# Averaging over 5 runs for each N" << endl;
        cout << "#" << endl;
        cout << "# N    avgcomps    stdev"<< endl;

        while ( N < maxSize ){


            vector<countint> v;
            v.clear();
            for(int i = N; 0 < i  ; --i) {
                v.push_back(i);
            }


            vector<countint>::iterator vit = v.begin();
            vector<countint>::iterator ven = v.end();


            double totalSquared = 0;

            //For the number of runs passed in
            for ( int run = 0; run < numRuns; run++ ){ 

                //if user wanted elements shuffeled
                if (shuffle){
                    std::random_shuffle( v.begin(),v.end() );
                }

                //Insert into the vector
                vit = v.begin();
                s.clear();
                for(int i = 0; i < N ; i++ ){
                    //cerr << "variable being inserted: " << *vit << endl;
                    s.insert(*vit);
                    vit++;
                }
                //create avgComps variable
                double avgcomps = 0;
                //now start the count variable for find
                countint::clearcount();
                for(vit = v.begin(); vit != ven; ++vit){
                    s.find(*vit);
                }

                //now get avg computations
                avgcomps = countint::getcount() / (double) N;

                //now calculate the standard deviation
                avgTotal = avgTotal + avgcomps;

                totalSquared = totalSquared + pow(avgcomps,TWO);
            }

            //average over the amount of runs
            avgTotal = (avgTotal / numRuns);
            //get the s variable t^2/R
            totalSquared = (totalSquared/numRuns);

            stdev = sqrt(   (totalSquared) - (pow(avgTotal,TWO)) );

            //print statements
            cout << setw(6) << N << setw(10) << avgTotal << setw(15) << stdev << endl;

            //reset avgTotal
            avgTotal = 0;
            stdev = 0;
            totalSquared = 0;

            power++;
            //increase N by power of 2
            N = pow(TWO,power) -1;

        }

    }

    if(set1){
        set<countint> s;

        //cout messages to user
        cout << "# Benchmarking average number of comparisons for successful find" << endl;
        cout << "# Data Structure: " << argv[1] << endl;
        cout << "# Data: " << argv[2] << endl;
        cout << "# N is powers of 2, minus 1, from 1 to " << argv[3] << endl;
        cout << "# Averaging over 5 runs for each N" << endl;
        cout << "#" << endl;
        cout << "# N    avgcomps    stdev"<< endl;

        while ( N < maxSize ){


            vector<countint> v;
            v.clear();
            for(int i = N; 0 < i  ; --i) {
                v.push_back(i);
            }

            vector<countint>::iterator vit = v.begin();
            vector<countint>::iterator ven = v.end();


            double totalSquared = 0;

            //For the number of runs passed in
            for ( int run = 0; run < numRuns; run++ ){ 

                //if user wanted elements shuffeled
                if (shuffle){
                    std::random_shuffle( v.begin(),v.end() );
                }
                //Insert into the vector
                vit = v.begin();
                s.clear();
                for(int i = 0; i < N ; i++ ){
                    //cerr << "variable being inserted: " << *vit << endl;
                    s.insert(*vit);
                    vit++;
                }
                //create avgComps variable
                double avgcomps = 0;
                //now start the count variable for find
                countint::clearcount();
                for(vit = v.begin(); vit != ven; ++vit){
                    s.find(*vit);
                }

                //now get avg computations
                avgcomps = countint::getcount() / (double) N;

                //now calculate the standard deviation
                avgTotal = avgTotal + avgcomps;

                totalSquared = totalSquared + pow(avgcomps,TWO);
            }

            //average over the amount of runs
            avgTotal = (avgTotal / numRuns);
            //get the s variable t^2/R
            totalSquared = (totalSquared/numRuns);

            stdev = sqrt(   (totalSquared) - (pow(avgTotal,TWO)) );

            //print statements
            cout << setw(6) << N << setw(10) << avgTotal << setw(15) << stdev << endl;

            //reset avgTotal
            avgTotal = 0;
            stdev = 0;
            totalSquared = 0;

            power++;
            //increase N by power of 2
            N = pow(TWO,power) -1;

        }

    }


    //endfile
}
