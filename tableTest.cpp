//Table tests for constructor, destructor and operator=
#include <iostream>
#include "table.h"
#include "entry.h"

using namespace std;

int main() {
	
    Table t(5);
    t.put(7, "seven");
    t.put(9, "nine");
    t.put(17, "Seventeen");
    t.put(4, "four");
    t.put(36, "Thirty-six");

    cout << "-----CONSTRUCTOR-----" << endl;

    Table f(t);
    cout << "Table F :" << endl;
    cout << f << endl;

    cout << "-----ASSIGNMENT OPERATOR-------" << endl;
    Table h(6);
 
    h.put(11, "eleven");
    h.put(10, "ten");
    h.put(17, "Seventeen");
    h.put(15, "fifteen");
    h.put(36, "Thirty-six");
    h.put(80, "eighty");
    
    cout << "Table h: " << endl;
    cout << h << endl;
    cout << "Table h after assignment: " << endl;;
    h = t;

    cout << h << endl;

}
