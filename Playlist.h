#pragma once
#include <string>
using namespace std;

class PlaylistNode {
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;

public:
    // Default
    PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr){};
    // Parametized
    PlaylistNode(string uniqueIDCopy, string songNameCopy, string artistNameCopy, int songLengthCopy) : 
    uniqueID(uniqueIDCopy), songName(songNameCopy), artistName(artistNameCopy), songLength(songLengthCopy), nextNodePtr(nullptr) {};
    // member functions
    const string& GetID() const;
    const string& GetSongName() const;
    const string& GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext();
    const PlaylistNode* GetNext() const;
    void PrintPlaylistNode() const;
    void SetNext(PlaylistNode* next);
    void InsertAfter(PlaylistNode* node);
};

/*
 * Implementation of Playlist class
 * 
 * Member functions are in order of menu for convenience
 * (1 function per menu option except for q)
 * 
 * Head/tail pointer used to add/delete node in the beginning/end
 * as well as keep track of nodes
 */

class Playlist {
private:
    PlaylistNode* head;
    PlaylistNode* tail;

public:
    // Constructor
    Playlist() : head(nullptr), tail(nullptr) {};
    // Member functions
    void AddSong(const string& userID, const string& songName, 
    const string& artistName, int songLength);
    void DeleteSong(string& userID);
    void ChangePosition(int currPos, int newPos);
    void PrintArtistSongs(const string& userArtist);
    int TotalTime();
    void PrintPlaylist() const;
};