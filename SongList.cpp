#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Song.h"
#include "SongList.h"
#include "myUtil.h"

using namespace std;

// Constructor and Function Definitions for Class SongList:
SongList::SongList()
{
	//default constructor
	head = nullptr;
	tail = nullptr;
	size = 0;
}
SongList::SongList(const char filename[])
{
	head = nullptr;
	tail = nullptr;
	size = 0;
	loadDB(filename);
	cout << endl << this->getSize() << " records were loaded from file \"" << filename << "\".";
}

SongList::SongList(const SongList& alist)
{
	//  copy constructor...  
	head = nullptr;
	size = 0;
	copyList(alist);

}
void SongList::copyList(const SongList &otherList)
{
	//  allocate memory and copy a SongList linked list to a new SongList object  

	Node * newNode, *curr;

	if (head != nullptr)
	{
		destroyList();
	}
	if (otherList.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else
	{
		curr = otherList.head;				// point to beginning node of the list to be copied
		head = new Node;					// allocate memory for a new list
		head->song.copySong(curr->song);	// copy data from the first node
		head->next = nullptr;				// set "next" pointer of new list to nullptr
		head->prev = nullptr;				// set "prev" pointer of new list to nullptr
		tail = head;						// store head node location in "tail" pointer
		size = 1;
		curr = curr->next;					// point to next node to be copied
		// copy remaining of list
		while (curr)						// while not at the end of the list...
		{
			newNode = new Node;				// allocate memory for new node
			newNode->song.copySong(curr->song);		// copy the current node data to copy list node
			newNode->next = nullptr;			// set "next" pointer of new node to nullptr
			newNode->prev = tail;			// set "prev" pointer of new node to tail->prev
			tail->next = newNode;
			tail = newNode;					// set tail to last node location
			size++;
			curr = curr->next;
		}  //end while
	}   // end else
}  // end copyList

SongList::~SongList()
{
	//  destructor...  
	destroyList();
}
void SongList::destroyList()
{
	Node * temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
	return;
}
void SongList::addToDB(const Song& asong)
{
	Node * newNode, *curr;
	Song tempSong;
	char title[MAX_CHAR], newTitle[MAX_CHAR];
	if (head == nullptr)
	{
		head = new Node;			// create new SongList object if empty list
		head->song.copySong(asong);
		head->prev = nullptr;
		head->next = nullptr;
		tail = head;
		size = 1;					// size=1
		return;						// node was inserted...   return
	}

	newNode = new Node;				// allocate new node
	newNode->song.copySong(asong);
	newNode->song.getTitle(newTitle);

	//traverse to find the position to insert
	curr = this->head;
	while (curr)
	{

		curr->song.getTitle(title);
		if (strcmpIgnoreCase(title, newTitle) > 0)
		{
			newNode->prev = curr->prev;		// insert newNode
			newNode->next = curr;
			if (curr == head)
			{
				head = newNode;
			}
			else
			{
				curr->prev->next = newNode;
			}
			curr->prev = newNode;
			size++;
			return;							// node was inserted... return
		}
		curr = curr->next;
	}

	//  add to end of linked list
	newNode->prev = tail;
	newNode->next = nullptr;
	tail->next = newNode;
	tail = newNode;
	size++;
	return;							// node was inserted... return
}
bool SongList::searchDBForArtist(const char searchKey[], SongList& matchings) const
{
	Node * curr;
	char artist[MAX_CHAR];
	int numFound = 0;

	//traverse to search for artist
	curr = head;
	while (curr)
	{
		curr->song.getArtist(artist);
		if (strcmpIgnoreCase(artist, searchKey) == 0)
		{
			matchings.addToDB(curr->song);
			numFound++;
		}
		curr = curr->next;
	}
	matchings.size = numFound;
	if (numFound > 0)
	{
		return true;
	}
	return false;
}
bool SongList::searchDBForAlbum(const char searchKey[], SongList& matchings) const
{
	Node * curr;
	char album[MAX_CHAR];
	int numFound = 0;

	//traverse to search for album
	curr = head;
	while (curr)
	{
		curr->song.getAlbum(album);
		if (strcmpIgnoreCase(album, searchKey) == 0)
		{
			matchings.addToDB(curr->song);
			numFound++;
		}
		curr = curr->next;
	}
	matchings.size = numFound;
	if (numFound > 0)
	{
		return true;
	}
	return false;
}
void SongList::removeFromDB(int index)
{
	Node * curr;

	if (size == 1)
	{
		destroyList();
		return;
	}

	curr = head;
	for (int i = 0; i < index; i++)		// traverse list until curr = requested node index
	{
		curr = curr->next;
	}
	
	if (curr == head)					// remove node at front of linked list
	{
		head = curr->next;
		head->prev = nullptr;
	}
	else if (curr == tail)				// remove node at end of linked list
	{
		tail = curr->prev;
		curr->prev->next = tail;
		tail->next = nullptr;
	}
	else								// remove node middle of linked list
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}
	delete curr;
	size--;
}
int SongList::getSize() const
{
	return size;
}
void SongList::getSong(int idx, Song& asong) const
{
	Node * curr;

	curr = head;
	for (int i = 0; i < idx; i++)		// traverse list until curr = requested node index
	{
		curr = curr->next;
	}
	asong.copySong(curr->song);
}
void SongList::printSongHeadings() const
{
	cout << endl << left << "#   " << setw(32) << "Title";
	cout << setw(19) << "Artist" << "Duration    Album" << endl;
}
void SongList::printAll() const
// formatted print of the complete SongList object
{
	Node * curr;
	int count = 0;

	printSongHeadings();
	curr = head;
	while (curr)
	{
		cout << left << setw(3) << count+1 << " ";
		curr->song.printSong();
		curr = curr->next;
		count++;
	}
}
int SongList::loadDB(const char filename[])
{
	ifstream infile;
	Song asong;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	int num;

	infile.open(filename);
	if (!infile) {
		cerr << endl << "File " << filename << " failed to open." << endl << endl;
		exit(1);
	}

	num = 0;
	infile.get(title, MAX_CHAR, ';');
	while (infile) {
		infile.get();					// skip data separator ';'
		infile.get(artist, MAX_CHAR, ';');
		infile.get();					// skip data separator ';'
		infile >> mm;
		infile.get();					// skip data separator ';'
		infile >> ss;
		infile.get();					// skip data separator ';'
		infile.get(album, MAX_CHAR, '\n');
		infile.ignore(100, '\n');		// skip end of record

		asong.setSong(title, artist, mm, ss, album);
		addToDB(asong);
		num = num + 1;
		infile.get(title, MAX_CHAR, ';');
	}
	infile.close();
	return num;						// return number of songs in data file
}

void SongList::saveDB(const char filename[]) const
{
	ofstream outfile;
	Node * curr;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	outfile.open(filename);
	if (!outfile) {
		cerr << endl << "Error in writing file " << filename << endl << endl;
		exit(1);
	}

	curr = head;
	while (curr)
	{
		curr->song.getSongInfo(title, artist, mm, ss, album);
		outfile << title << ';'
			<< artist << ';'
			<< mm << ';'
			<< ss << ';'
			<< album << endl;
		curr = curr->next;
	}
	outfile.close();
	return;
}
