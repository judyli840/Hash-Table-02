#ifndef table_h
#define table_h

#include <string>
#include <iosfwd>
#include <vector>
#include "entry.h"


// Note: Your hash table must be implemented using an array of
// std::vector<Entry> as stated in the instructions.



class Table {
private:
	unsigned int size;
	int num_entries;
	unsigned int hashkey(unsigned int key) const{
		unsigned int index;
		if (size == 0)
			index = key%1;
		else 
			index = key%size;
		return index;
	}

public:
	Table(unsigned int max_entries = 100);
	Table(unsigned int entries, std::istream& input);
	~Table();
	Table(const Table& t);

	Table& operator=(const Table& t);

	void put(unsigned int key, std::string data);
	void put(Entry e);

	//returns the string associated with the parameter
	std::string get(unsigned int key) const;
	int get_num_entries() const;
	int get_size() const;


	//removes the Entry containing given key and returns true if it
	//removes entry or false if the Table has no such Entry
	bool remove(unsigned int key);

	std::vector<Entry> *table;


};

// print each Entry in the table to a separate line in the given
// output stream O(nlogn)

std::ostream& operator<< (std::ostream& out, const Table& t);



#endif
