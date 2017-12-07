/****************************************************************************
* 
* NAME:                 Gary Tang
* 
* HOMEWORK:             Project 2
*
* CLASS:                ICS 212
*
* INSTRUCTOR:           Ravi Narayan
*
* DATE:                 November 22, 2014
*              
* FILE:                 llist.h
*      
* DESCRIPTION:          This file contains definition of llist.
*
*****************************************************************************/
#ifndef _llist_H_INCLUDED_
#define _llist_H_INCLUDED_

#include<iostream>
#include "record.h"

class    llist
{
         private:
             record* start;
             char filename[16];
             int readfile();
             int writefile();
             record* reverse(record *);
             void cleanup();
 
         public:
             llist();
             llist(char[]);
             ~llist();
             llist(llist&);
             int addRecord(char[], char[], int, char[]);
             int printRecord(char[]);
             int modifyRecord(char[], char[], char[]);
             void printAll();
             int deleteRecord(char[]);
             void reverse();
             friend std::ostream& operator<<(std::ostream&, llist&);
             void operator=(llist&);
};

#endif

