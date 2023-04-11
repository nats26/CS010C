#include "Playlist.h"
#include <iostream>

using namespace std;

const string& PlaylistNode::GetID() const {
    return uniqueID;
}

const string& PlaylistNode::GetSongName() const {
    return songName;
}

const string& PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

const PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << GetID() << endl;
    cout << "Song Name: " << GetSongName() << endl;
    cout << "Artist Name: " << GetArtistName() << endl;
    cout << "Song Length (in seconds): " << GetSongLength() << endl;
}

void PlaylistNode::SetNext(PlaylistNode* next) {
    nextNodePtr = next;
}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    PlaylistNode* temp = nullptr;
    temp = nextNodePtr;
    nextNodePtr = node;
    node->SetNext(temp);
}

// used in option 'a'
void Playlist::AddSong(const string& userID, const string& songName, const string& artistName, int songLength) {
    PlaylistNode* tempData = new PlaylistNode(userID, songName, artistName, songLength);
    if (head == nullptr && tail == nullptr) {
        head = tempData;
        tail = tempData;
    }
    // if playlist is not empty, add song LAST, set new tail
    else {
        tail->InsertAfter(tempData);
        tail = tempData;
    }
}

// used in option 'd'
void Playlist::DeleteSong(string& userID) {
    // Empty playlist
    if (head == nullptr && tail == nullptr) {
        cout << "EMPTY, CANNOT DELETE SONG\n\n";
    }
    else {
        PlaylistNode* prev = nullptr;
        PlaylistNode* loopUse = head;
        string holdName = loopUse->GetSongName();
        // while loop finds prev & name of the song with loopUse
        while (loopUse->GetID() != userID && loopUse->GetNext() != nullptr) {
            prev = loopUse;
            loopUse = loopUse->GetNext();
            holdName = loopUse->GetSongName();
        }
        if (loopUse->GetID() == userID) {
            // delete head
            if (loopUse == head) {
                if (loopUse == tail) {
                    tail = nullptr; // if head & tail are same
                } 
                PlaylistNode* temp = head;
                head = temp->GetNext();
                delete temp;
            }
            // delete tail
            else if (loopUse == tail) {
                tail = prev;
                tail->SetNext(nullptr);
                delete loopUse;
            }
            // delete middle nodes
            else {
                prev->SetNext(loopUse->GetNext());
                delete loopUse;
            }
            cout << "\"" << holdName << "\" removed.\n\n";
        }
    }
}

// used in option 'c'
void Playlist::ChangePosition(int currPos, int newPos) {
    int numOfNodes = 0;
    PlaylistNode* secToLast = nullptr;
    // Count num of nodes and find the pointer before tail (to be used in changes concerning tails)
    for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
        ++numOfNodes;
        if (p != tail) {
            secToLast = p;
        }
    }
    
    PlaylistNode* prevNode = nullptr;
    PlaylistNode* currNode = head;
    PlaylistNode* nameNode = head;
    string nameOfSong = head->GetSongName();
    int i = 1, j = 1;

    // find song name & nodes before/after node at currPos (nameNode - provides song name)
    PlaylistNode* beforeNode = nullptr;
    while (j < currPos) {
        beforeNode = nameNode;
        nameNode = nameNode->GetNext();
        nameOfSong = nameNode->GetSongName();
        ++j;
    }
    PlaylistNode* afterNode = nameNode->GetNext();

    // find node corresponding to new position + node before new position
    while (i < newPos) {
        prevNode = currNode;
        currNode = currNode->GetNext();
        ++i;
    }

    // move head node
    if (currPos == 1) {
        PlaylistNode* temp = head;
        head = head->GetNext();
        // move to tail
        if (newPos >= numOfNodes) {
            temp->SetNext(nullptr);
            tail->SetNext(temp);
            tail = temp;
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        // other place in list
        else if (newPos > 1 && newPos < numOfNodes) {
            temp->SetNext(currNode->GetNext());
            currNode->SetNext(temp);
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        else {
            cout << "Can't move " << nameOfSong << "!\n";
        }
    }
    // move tail node
    else if (currPos == numOfNodes) {
        PlaylistNode* temp = tail;
        secToLast->SetNext(nullptr);
        tail = secToLast;
        // move tail to head
        if (newPos <= 1) {
            temp->SetNext(head);
            head = temp;
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        // other place in list
        else if (newPos > 1 && newPos < numOfNodes) {
            temp->SetNext(currNode);
            prevNode->SetNext(temp);
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        else {
            cout << "Can't move " << nameOfSong << "!\n";
        }
    }
    // move in between nodes
    else if (currPos > 1 && currPos < numOfNodes) {
        // move to head
        if (newPos <= 1) {
            nameNode->SetNext(head);
            beforeNode->SetNext(afterNode);
            head = nameNode;
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        // move to tail
        else if (newPos >= numOfNodes) {
            nameNode->SetNext(nullptr);
            beforeNode->SetNext(afterNode);
            tail->SetNext(nameNode);
            tail = nameNode;
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        // move up list
        else if (newPos < currPos) {
            beforeNode->SetNext(afterNode);
            nameNode->SetNext(currNode);
            prevNode->SetNext(nameNode);
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
        // move down list
        else if (newPos > currPos) {
            nameNode->SetNext(currNode->GetNext());
            beforeNode->SetNext(afterNode);
            currNode->SetNext(nameNode);
            cout << "\"" << nameOfSong << "\"" << " moved to position " << newPos << endl;
        }
    }
}

// used in option 's'
void Playlist::PrintArtistSongs(const string& userArtist) {
    if (head == nullptr) {
        cout << "Playlist is empty\n\n";
    }
    else {
        int i = 1;
        // loop through all songs & output only if the artist name matches user input
        for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
            if (p->GetArtistName() == userArtist) {
                cout << i << ".\n";
                p->PrintPlaylistNode();
                cout << endl;
            }
            ++i;
        }
    }
}

// used in option 't'
int Playlist::TotalTime() {
    int totalTime = 0;
    // loop through all songs and add all song lengths & return total time
    for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
        totalTime += p->GetSongLength();
    }
    return totalTime;
}

// used in option 'o'
void Playlist::PrintPlaylist() const {
    if (head == nullptr) {
        cout << "Playlist is empty\n\n";
    }
    else {
        // loop through songs and output all songs until null is reached
        int i = 1;
        for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
            cout << i << ".\n";
            p->PrintPlaylistNode();
            cout << endl;
            ++i;
        }
    }
}