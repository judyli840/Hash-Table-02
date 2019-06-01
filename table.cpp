#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "table.h"
#include "entry.h"

using namespace std;

//void put(Entry e);
//void put(unsigned int key, std::string data);

Table::Table(unsigned int max_entries){
	size = max_entries;
	num_entries = 0;
	table = new vector<Entry>[size];
}

Table::Table(unsigned int entries, istream& input) {
    unsigned int i = 0;
    size = entries;
    table = new vector<Entry>[entries+1];

    while ((i < entries) && (!input.eof())) {
	Entry e;
	input >> e;
        this->put(e.get_key(),e.get_data());
        i++;
	}
    num_entries = i;
}

Table::Table(const Table& t) {
	size = t.get_size();

	num_entries = 0;
	int count = t.num_entries;
	
	table = new vector<Entry>[size];

	int i = 0;
	int n = 0;
//	vector<Entry>::iterator temp = t.table[n].begin();

	for (i = 0; i < size; i++) {
		for (int j =0; j < t.table[i].size(); j++) {
			this->put(t.table[i][j]);
		}
	}
/*		if (temp == t.table[n].end()) {
			temp = t.table[++n].begin();
		} else {
			this->put(*temp);
			i++;
			temp++;
		}
	}*/
}

Table::~Table() {
/*	cout << "destructor" << endl;
	int i = 0;
	int n = 0;
	vector<Entry>::iterator temp = table[n].begin();
	while (i < num_entries) {
		if (temp == table[n].end()) {
			temp = table[++n].begin();
		} else {
		
			i++;
			temp++;
		}
}*/
	delete [] table;
}

Table & Table::operator=(const Table& t) {
	//Check for self-assignment
	if (&t == this) {
		return (*this);
	}

	//replace 
	size = t.get_size();
	num_entries = 0; 
	
	delete [] table;

	table = new vector<Entry>[size];

	for (int i = 0; i < size; i++) {
		for (int j =0; j < t.table[i].size(); j++) {
			this->put(t.table[i][j]);
		}
	}


/*	int i = 0;
	int n = 0;
	vector<Entry>::iterator temp = t.table[n].begin();
	while (i < size) {
		if (temp == t.table[n].end()) {
			temp = t.table[++n].begin();
		} else {
			this->put(*temp);
			i++;
			temp++;
		}
	}*/
	return (*this);
}


void Table::put(unsigned int key, std::string data) {
	unsigned int index = hashkey(key);
	bool found = false;
	
	vector<Entry>::iterator i;
	for (i = table[index].begin(); i != table[index].end(); ++i) {
		if (i->get_key() == key){
			i->set_key(key);
			i->set_data(data);
			found = true;
		}
	}

	if (!found) {
		Entry *temp = new Entry(key, data);
	//	Entry temp(key, data);
		table[index].push_back(*temp);
		num_entries++;
		delete temp;
	}	
}


void Table::put(Entry e) {
	this->put(e.get_key(), e.get_data());
}


string Table::get(unsigned int key) const {
    unsigned int index = hashkey(key);
    for (vector<Entry>::iterator i = table[index].begin(); i != table[index].end(); i++) {
        if (i->get_key() == key) {
            return i->get_data();
        }
    }
    return "";
}


bool Table::remove(unsigned int key) {
    unsigned int index = hashkey(key);
	
    vector<Entry>::iterator i;		
    for (i = table[index].begin(); i != table[index].end(); i++){
	if (i->get_key() == key) {
           table[index].erase(i);
	   num_entries--;
	    return true;
        }
    }
    return false;
}

int Table::get_num_entries() const {
    return num_entries;
}

int Table::get_size() const {
    return size;
}

void merge(Entry a[], size_t leftArraySize, size_t rightArraySize) {
    Entry* temp;
    size_t copied = 0;
    size_t leftCopied = 0;
    size_t rightCopied = 0;

    temp = new Entry[leftArraySize + rightArraySize];
    while ((leftCopied < leftArraySize) && (rightCopied < rightArraySize)) {
        if (a[leftCopied] < (a + leftArraySize)[rightCopied]) {
            temp[copied++] = a[leftCopied++];
        }else {
            temp[copied++] = (a + leftArraySize)[rightCopied++];
        }
    }
    while (leftCopied < leftArraySize) {
        temp[copied++] = a[leftCopied++];
    }
    while (rightCopied < rightArraySize) {
        temp[copied++] = (a + leftArraySize)[rightCopied++];
    }
    for (int i = 0; i < leftArraySize + rightArraySize; i++) {
        a[i] = temp[i];
    }

    delete []temp;

}

void mergeSort(Entry a[], size_t size) {
    size_t leftArraySize;
    size_t rightArraySize;

    if (size > 1) {

        leftArraySize = size/2;
        rightArraySize = size - leftArraySize;
	
        mergeSort(a, leftArraySize);
        mergeSort((a + leftArraySize), rightArraySize);
        merge(a, leftArraySize, rightArraySize);
    }
}

std::ostream& operator<< (std::ostream& out, const Table& t) {
    int count = t.get_num_entries();
    int size = t.get_size();
    Entry a[size];

    int i = 0;
    int n = 0;
    vector<Entry>::iterator temp = t.table[n].begin();
    while (i < count) {
	if (temp == t.table[n].end()) {
		temp = t.table[++n].begin();
	} else {
		a[i] = *temp;
		i++;
		temp++;
	}
    }

    mergeSort(a, count);
    for(int j = 0; j < count; j++) {
	if (a[j].get_key() != 0) {
        	out << a[j] << endl;
	}
    }
    
    return out;
}
