#include "DocumentManager.h"
// #include <iostream>


Document::Document(string name, int id, int license_limit)
{
    this->name = name;
    this->id = id;
    this->license_limit = license_limit;
    this->borrow_count = 0;
}

void Document::borrow()
{
    this->borrow_count++;
}

void Document::return_back()
{
    this->borrow_count--;
}

bool Document::avaiable()
{
    return this->borrow_count < this->license_limit;
}

Patron::Patron(int id)
{
    this->id = id;
}

void Patron::borrow(int doc_id)
{
    this->borrow_document[doc_id]++;
}

void Patron::return_bact(int doc_id)
{
    this->borrow_document[doc_id]++;
}

void DocumentManager::addDocument(string name, int id, int license_limit)
{
    this->name_to_id[name] = id;
    this->id_to_document[id] = Document(name, id, license_limit);
}

void DocumentManager::addPatron(int id)
{
    this->id_to_patron[id] = Patron(id);
}

int DocumentManager::search(string name)
{
    if (this->name_to_id.count(name))
    {
        return this->name_to_id[name];
    }
    return 0;
}

bool DocumentManager::borrowDocument(int doc_id, int patron_id)
{
    if (this->id_to_document.find(doc_id) == this->id_to_document.end())
    {
        return false;
    }
    if (!this->id_to_document[doc_id].avaiable())
    {
        return false;
    }

    // the user must be registered as a patron and will have a patron id
    if (this->id_to_patron.count(patron_id) == 0)
    {
        // register
        this->addPatron(patron_id);
    }

    this->id_to_patron[patron_id].borrow(doc_id);
    this->id_to_document[doc_id].borrow();

    return true;
}

void DocumentManager::returnDocument(int doc_id, int patron_id)
{
    // uncheck
    this->id_to_patron[patron_id].return_bact(doc_id);
    this->id_to_document[doc_id].return_back();
}

// int main()
// {

//     DocumentManager dm = DocumentManager();

//     dm.addDocument("doc1", 1, 10);
//     dm.addDocument("doc2", 2, 3);
//     dm.addDocument("doc3", 3, 2);
//     dm.addDocument("doc4", 4, 1);

//     dm.addPatron(101);

//     int id1 = dm.search("doc1");
//     cout << id1 << endl;

//     cout << dm.borrowDocument(1, 102) << endl;
//     cout << dm.borrowDocument(4, 102) << endl;
//     dm.returnDocument(4, 102);
//     cout << dm.borrowDocument(4, 102) << endl;

    

//     return 0;
// }