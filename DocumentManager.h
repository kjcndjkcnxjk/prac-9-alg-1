
#include <string>
#include <unordered_map>

using namespace std;

class Document
{
    string name;
    int id;
    int license_limit;
    int borrow_count;

public:
    Document() = default;
    Document(string, int, int);

    void borrow();

    void return_back();

    bool avaiable();
};

class Patron
{
    int id;
    unordered_map<int, int> borrow_document;

public:
    Patron() = default;
    Patron(int);
    void borrow(int);
    void return_bact(int);
};

class DocumentManager
{
    unordered_map<int, Document> id_to_document;
    unordered_map<int, Patron> id_to_patron;
    unordered_map<string, int> name_to_id;

public:
    void addDocument(string name, int id, int license_limit);

    void addPatron(int patronID);

    int search(string name);

    bool borrowDocument(int docid, int patronID);
    void returnDocument(int docid, int patronID);
};