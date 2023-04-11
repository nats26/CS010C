#include "Playlist.h"
#include <string>
#include <iostream>
using namespace std;

void PrintMenu(string title);

int main() {
    // info from user
    string userTitle;
    cout << "Enter playlist's title:\n";
    getline(cin, userTitle);
    cout << endl;

    Playlist userPlaylist;

    char userOption;
    do {
        PrintMenu(userTitle);
        cout << "Choose an option:\n";
        cin >> userOption;

        // add song to userPlaylist
        if (userOption == 'a') {
            string userSong;
            string userID;
            string userArtist;
            int userLength;

            cout << "ADD SONG\n";
            cout << "Enter song's unique ID:\n";
            cin >> userID;
            cout << "Enter song's name:\n";
            cin.ignore();
            getline(cin, userSong);
            cout << "Enter artist's name:\n";
            getline(cin, userArtist);
            cout << "Enter song's length (in seconds):\n";
            cin >> userLength;
            cout << endl;

            userPlaylist.AddSong(userID, userSong, userArtist, userLength);
        }

        // delete song from userPlaylist
        else if (userOption == 'd') {
            string userID;

            cout << "REMOVE SONG\n";
            cout << "Enter song's unique ID:\n";
            cin >> userID;

            userPlaylist.DeleteSong(userID);
        }

        // change a specific song's position
        else if (userOption == 'c') {
            int currPosition;
            int newPosition;

            cout << "CHANGE POSITION OF SONG\n";
            cout << "Enter song's current position:\n";
            cin >> currPosition;
            cout << "Enter new position for song:\n";
            cin >> newPosition;

            userPlaylist.ChangePosition(currPosition, newPosition);
            cout << "\n";
        }

        // output all songs by user given artist
        else if (userOption == 's') {
            string userArtist;

            cout << "OUTPUT SONGS BY SPECIFIC ARTIST\n";
            cout << "Enter artist's name:\n\n";
            cin.ignore();
            getline(cin, userArtist);

            userPlaylist.PrintArtistSongs(userArtist);
        }

        // output total time of all songs in playlist
        else if (userOption == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n";
            cout << "Total time: ";
            cout << userPlaylist.TotalTime();
            cout << " seconds" << endl << endl;
        }

        // output full userPlaylist
        else if (userOption == 'o') {
            cout << userTitle << " - OUTPUT FULL PLAYLIST\n";
            userPlaylist.PrintPlaylist();
        }

        // Ensure menu doesn't take invalid choices
        while (userOption != 'a' && userOption != 'd' && userOption != 'c' && userOption != 's'
    && userOption != 't' && userOption != 's' && userOption != 'o' && userOption != 'q') {
            cout << "Choose an option:\n";
            cin >> userOption;
            if (userOption != 'q') {
                cout << endl;
            }
        }
    }
    while (userOption != 'q');

    return 0;
}

void PrintMenu(string title) {
    cout << title << " PLAYLIST MENU\n";
    cout << "a - Add song\n";
    cout << "d - Remove song\n";
    cout << "c - Change position of song\n";
    cout << "s - Output songs by specific artist\n";
    cout << "t - Output total time of playlist (in seconds)\n";
    cout << "o - Output full playlist\n";
    cout << "q - Quit\n\n";
}