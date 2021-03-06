#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include "phone_list.h"

using namespace std;

void Phone_List::create()
{
    head = NULL;
    nodecount = 0;
}

int Phone_List::search(char *target)
{
    Phone_Node* traverse;
    int counter = 0;
    int found = 0;
    traverse = head;
    bool all = false;
    if (strcmp(target, "*") == 0)
        all = true;
    while (traverse)
    {
        counter++;
        if (all)
        {
            cout << counter << "." << traverse->phone_record->name << " " << traverse->phone_record->phonenum << endl;
            found++;
        }
        else if (strncasecmp(traverse->phone_record->name, target, strlen(target)) == 0)
        {
            found++;
            cout << counter << "." << traverse->phone_record->name << " " << traverse->phone_record->phonenum
                 << endl;
        }
        traverse = traverse->next;
    }
    return found;
}

void Phone_List::remove(int ordernum)
{
    Phone_Node* traverse;
    Phone_Node* tail;
    int counter = 1;
    traverse = head;
    if (ordernum <= 0)
    {
        cout << "Invalid record order number.\n";
        return;
    }
    if (ordernum == 1)
    {
        head = head->next;
        delete traverse->phone_record;
        delete traverse;
        nodecount--;
        return;
    }
    while ((traverse != NULL) && (counter < ordernum))
    {
        tail = traverse;
        traverse = traverse->next;
        counter++;
    }
    if (counter < ordernum)
    {
        // given order num too large
        cout << "Could not find record to delete.\n ";
    }
    else
    { // record found
        tail->next = traverse->next;
        delete traverse->phone_record;
        delete traverse;
        nodecount--;
    }
}

void Phone_List::insert(Phone_Record* rectoadd)
{
    Phone_Node* traverse;
    Phone_Node* tail;
    Phone_Node* newnode;

    traverse = head;
    newnode = new Phone_Node;
    newnode->phone_record = new Phone_Record;
    strcpy(newnode->phone_record->name, rectoadd->name);
    strcpy(newnode->phone_record->phonenum, rectoadd->phonenum);
    newnode->next = NULL;
    if (head == NULL)
    {
        //first node being added
        head = newnode;
        nodecount++;
        return;
    }
    if (strcmp(newnode->phone_record->name, head->phone_record->name) < 0)
    {
        //Insert to head of list
        newnode->next = head;
        head = newnode;
        nodecount++;
        return;
    }
    while (traverse &&
           (strcmp(newnode->phone_record->name, traverse->phone_record->name) > 0))
    {
        tail = traverse;
        traverse = traverse->next;
    }
    if (traverse)
    { // Insert into a position
        newnode->next = traverse;
        tail->next = newnode;
    }
    else // Insert to end
        tail->next = newnode;
    nodecount++;
}

void Phone_List::update(int recordnum, Phone_Record* newrecord)
{
    Phone_Node* traverse;
    Phone_Node *newnode = new Phone_Node;

    newnode->phone_record = new Phone_Record;
    strcpy(newnode->phone_record->name, newrecord->name);
    strcpy(newnode->phone_record->phonenum, newrecord->phonenum);
    
    int counter = 1;
    traverse = head;
    while (traverse && (counter < recordnum))
    {
        counter++;
        traverse = traverse->next;
    }
    if (traverse)
    {
        newnode->next = traverse->next;
        delete traverse->phone_record;
        *traverse = *newnode;
    }
    else
        cout << "Invalid number for record to be updated.\n";
}

void Phone_List::clear()
{
    Phone_Node *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete p->phone_record;
        delete p;
    }
    nodecount = 0;
}