//
// Constructor and Function Definitions for Classes: Song and SongLength
//
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Song.h"

using namespace std;

// Class SongLength:
SongLength::SongLength()
{
	minutes = 0;
	seconds = 0;
}
void SongLength::setSongLength(const int mm, const int ss)
{
	minutes = mm;
	seconds = ss;
}
int SongLength::getMinutes() const
{
	return minutes;
}
int SongLength::getSeconds() const
{
	return seconds;
}
void SongLength::printSongLength() const
{
	cout << setw(2) << minutes << ":" << setfill('0') << setw(2) << seconds;
}
//
// Constructors for Class Song:
Song::Song()
{
    title = nullptr;
	artist = nullptr;
	duration.setSongLength(0, 0);
	album = nullptr;
}
Song::Song(const char a[], const char b[], int mm, int ss, const char c[])
{
	title = new char[strlen(a) + 1];
	strcpy(title, a);
	artist = new char[strlen(b) + 1];
	strcpy(artist, b);
	duration.setSongLength(mm, ss);
	album = new char[strlen(c) + 1];
	strcpy(album, c);
}

// copy constructor for Class Song
Song::Song(const Song &asong)
{
	this->title = new char[strlen(asong.title) + 1];
	strcpy(this->title, asong.title);
	this->artist = new char[strlen(asong.artist) + 1];
	strcpy(this->artist, asong.artist);
	this->duration.setSongLength(asong.duration.getMinutes(), asong.duration.getSeconds());
	this->album = new char[strlen(asong.album) + 1];
	strcpy(this->album, asong.album);
}
void Song::copySong(const Song &songToCopy)
{
	if (this->title) delete[] this->title;
	this->title = new char[strlen(songToCopy.title) + 1];
	strcpy(this->title, songToCopy.title);
	if (this->artist) delete[] this->artist;
	this->artist = new char[strlen(songToCopy.artist) + 1];
	strcpy(this->artist, songToCopy.artist);
	this->duration.setSongLength(songToCopy.duration.getMinutes(), songToCopy.duration.getSeconds());
	if (this->album) delete[] this->album;
	this->album = new char[strlen(songToCopy.album) + 1];
	strcpy(this->album, songToCopy.album);
}
// Destructor for Class Song:
Song::~Song()
{
    if(title != nullptr) 
	    delete[] title;
    if(artist != nullptr) 
	   delete[] artist;
    if(album != nullptr) 
	   delete[] album;
}
// Member Function Definitions for Class Song:

void Song::printSong() const 
{
	cout << left << setw(32) << title << setw(20) << artist << "  ";
	cout << right << setw(2) << duration.getMinutes() << ":";
	cout << setfill('0') << setw(2) << duration.getSeconds() << "    ";
	cout << left << setfill(' ') << setw(25) << album << endl;
} 
void Song::getSongInfo(char a[], char b[], int& mm, int& ss, char c[]) const
{
	strcpy(a, title);
	strcpy(b, artist);
	mm = duration.getMinutes();
	ss = duration.getSeconds();
	strcpy(c, album);
}
void Song::getTitle(char str[]) const 
{
	strcpy(str, title);
}
void Song::getArtist(char str[]) const
{
	strcpy(str, artist);
}
void Song::getAlbum(char str[]) const 
{
	strcpy(str, album);
}
void Song::setSong(const char a[], const char b[], const int mm, const int ss, const char c[])
{
	if (title != nullptr) {
		delete[] title;
	}
	title = new char[strlen(a) + 1];
	strcpy(title, a);
	if (artist != nullptr) {
		delete[] artist;
	}
	artist = new char[strlen(b) + 1];
	strcpy(artist, b);
	duration.setSongLength(mm, ss);
	if (album != nullptr) {
		delete[] album;
	}
	album = new char[strlen(c) + 1];
	strcpy(album, c);
}
