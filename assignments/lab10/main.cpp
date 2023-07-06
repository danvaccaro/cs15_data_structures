/*
 * Comp 15 Hash Table Lab
 *
 * main.cpp --- tests the two approaches to collisions and two
 * different hash functions using sample song data.
 *
 * Songs chosen by Rebecca Newman
 * Song tempi from songbpm.com and www.bpmdatabase.com
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2017
 *     based on prior labs by Ben Hescott, Bruce Molay, Chris Gregg, 
 *     and work by Rebecca Newman.
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

#include "FunkeyTable.h"
using namespace std;

/*
 * For storing the song we will insert into the hash table
 */
struct SongData {
        string   title;
        SongInfo info;
};

/*
 * Statistics we want to collect for each hash function
 */
struct Stats {
        int maxProbeCollisions, totProbeCollisions, maxChainCollisions;
        Stats()
                : maxProbeCollisions(0),
                  totProbeCollisions(0),
                  maxChainCollisions(0)

        {
                // member initialization list did everything
        }
};

void  run_tests(string testName, SongData songs[], int numSongs,
                FunkeyTable::HashFunction hashFunction);
Stats collect_stats(SongData songs[], int numSongs, FunkeyTable &songDB,
                    FunkeyTable::HashFunction hashFunction);
void  print_stats(Stats test_results);


int main()
{
        SongData songs[] = {
                            {"Stayin' Alive",     {3, 104}},
                            {"Funky Town",        {5, 128}},
                            {"Disco Inferno",     {6, 129}},
                            {"Night Fever",       {20, 109 }},
                            {"Last Dance",        {21, 126}},
                            {"I Will Survive",    {1, 116}},
                            {"Car Wash",          {27, 115}},
                            {"Billie Jean",       {30, 117}},
                            {"Get Up and Boogie", {13, 105}},
                            {"YMCA",              {7, 127}}
                           };
        int numSongs = sizeof(songs) / sizeof(SongData);
        run_tests("Bad Hash Function", songs, numSongs,
                  FunkeyTable::BAD_HASH_FUNCTION);

        run_tests("Good Hash Function", songs, numSongs,
                  FunkeyTable::GOOD_HASH_FUNCTION);

        return 0;
}

/*
 *  Test the two approaches to collision handling with an array of
 *  SongData and a specified hash function.
 *  
 *  Approach:
 *       Insert the data, keeping stats
 *       Report test results
 *       Print the hash tables
 */
void run_tests(string testName, SongData songs[], int numSongs,
               FunkeyTable::HashFunction hashFunction)
{
        FunkeyTable songDB;
        Stats       test_stats;

        cout << testName << endl;
        
        test_stats = collect_stats(songs, numSongs, songDB, hashFunction);
        print_stats(test_stats);

        cout << endl;
        cout << "Your Tables:" << endl;

        songDB.print();
        cout << endl;
}

/*
 * Collect collision statistics for a particular hash function
 */
Stats collect_stats(SongData songs[], int numSongs, FunkeyTable &songDB,
                    FunkeyTable::HashFunction hashFunction)
{
        int collisions, i;
        Stats results;
        
        cout << "inserting keys:";
        for (i = 0; i < numSongs; ++i) {
                cout << " \"" << songs[i].title << "\"";
                collisions = songDB.insertProbing(songs[i].title,
                                                  songs[i].info,
                                                  hashFunction);
                results.totProbeCollisions += collisions;
                results.maxProbeCollisions = max(results.maxProbeCollisions,
                                                 collisions);

                collisions = songDB.insertChaining(songs[i].title,
                                                   songs[i].info,
                                                   hashFunction);
                results.maxChainCollisions = max(results.maxChainCollisions,
                                                 collisions);
        }
        return results;
}

/*
 * Print the collision statistics for a particular test
 */
void  print_stats(Stats test_results)
{
        cout << endl << "Results for your code:" << endl;

        printf("     Linear Probing: reprobes = %d  max lookup = %d\n",
               test_results.totProbeCollisions,
               test_results.maxProbeCollisions);

        // For chaining, the maximum bucket size is 1 more than the
        // number of collisions reported, because the collisions is
        // the size of the bucket list before insertion
        printf("           Chaining: reprobes = 0  max bucket size= %d\n",
               test_results.maxChainCollisions + 1);
}
