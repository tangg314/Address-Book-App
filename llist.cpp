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
* FILE:                 llist.cpp
*      
* DESCRIPTION:          This file contains function definition of llist.
*
*****************************************************************************/

#include "llist.h"

#include <iostream>
#include<fstream>
#include <string.h>
#include <ctype.h>

using namespace std;

/****************************************************************************
*
* FUNCTION NAME:        llist
*              
* DESCRIPTION:          Creates llist.
*              
* PARAMETERS:           None.
*
* Return values:        None.
*
****************************************************************************/

llist::llist() 
{

    //Debug mode
    #ifdef debug
    cout << "\nfunction called: llist() \n\n";
    #endif

    (this -> start) = NULL;
    strcpy(this -> filename, "default.txt");
    this -> readfile();
}

/****************************************************************************
*
* FUNCTION NAME:        llist
*              
* DESCRIPTION:          Creates llist. Stores database in file named fname.
*              
* PARAMETERS:           fname(char[]): Name of database file.
*
* Return values:        None.
*
****************************************************************************/

llist::llist(char fname[])
{

    //Debug mode
    #ifdef debug
    cout << "\nfunction called: llist(char fname[]) \n"
         << "fname = " << fname << "\n\n";
    #endif

    (this -> start) = NULL;
    strcpy(this -> filename, fname);
    this -> readfile();
}

/****************************************************************************
*
* FUNCTION NAME:        llist
*              
* DESCRIPTION:          Copy constructor or copies llist. 
*              
* PARAMETERS:           ulist(llist&): llist to copy.
*
* Return values:        None.
*
****************************************************************************/

llist::llist(llist& ulist)
{ 
    (this -> start) = NULL;
    strcpy(this -> filename, "default.txt");
    record* temp = (ulist.start);
        
    //Debug mode
    #ifdef debug
    cout << "\nfunction called: llist(llist& ulist) \n" 
         << "ulist = ulist \n\n";
    #endif
      
    //Empty list
    if((ulist.start) == NULL)
    {
        cout << "\nI am sorry, the phonebook is empty. \n\n";
    }
    
    //Copy list    
    while(temp != NULL)
    {
        this -> addRecord(temp -> name, temp -> telno,
                         temp -> yearofbirth, 
                         temp -> address);
            
        temp = temp -> next;
    }    
}

/****************************************************************************
*
* FUNCTION NAME:        ~llist
*              
* DESCRIPTION:          Destroys llist.
*              
* PARAMETERS:           None.
*
* Return values:        None.
*
****************************************************************************/

llist::~llist()
{

    //Debug mode
    #ifdef debug
    cout << "\nfunction called: ~llist() \n";
    #endif
        
    this -> writefile();
    this -> cleanup();
}

/****************************************************************************
*
* FUNCTION NAME:        addRecord
*              
* DESCRIPTION:          Add record to end of linked list.
*              
* PARAMETERS:           uname(char[]): Name of person. 
*                       utelno(char[]): Telephone number of person.
*                       uyob(int): Year of birth of person.
*                       uaddr(char[]): Address of person.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::addRecord(char uname[], char utelno[], int uyob, char uaddr[])
{             
       record* temp;
       record* previous;
       temp = NULL;
       previous = NULL;

       //Debug mode
       #ifdef debug      
       cout << "\nfunction called: addRecord(char uname[], char utelno[]," 
            << " int uyob, char uaddr[]) \n"
            << "uname = " << uname << "\n"
            << "utelno = " << utelno << "\n"
            << "uyob = " << uyob << "\n"
            << "uaddr = " << "\n" << uaddr << "\n\n";
       #endif  
    
       if((this -> start) == NULL)
       {           
           (this -> start) = new record();	
           strcpy((this -> start) -> name, uname);
           strcpy((this -> start) -> address, uaddr);
           (this -> start) -> yearofbirth = uyob;
           strcpy((this -> start) -> telno, utelno);
           (this -> start) -> next = NULL;
       }
       
       else
       {
           temp = (this -> start);

           while(temp != NULL)
           {
               previous = temp;
               temp = temp -> next;
           }
       
           if(previous != NULL)
           {
               previous -> next = new record();
               temp = previous -> next;
               strcpy(temp -> name, uname);
               strcpy(temp -> address, uaddr);
               (temp -> yearofbirth) = uyob;
               strcpy(temp -> telno, utelno);
               temp -> next = NULL;
           }
       }  
       
       return 0;
}

/****************************************************************************
*
* FUNCTION NAME:        printRecord
*              
* DESCRIPTION:          Prints an entry from phonebook.
*              
* PARAMETERS:           uname(char[]): Name of person to be printed.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::printRecord(char uname[])
{
       struct record* current;
       int status = 1;
              
       current = NULL;
       current = (this -> start);
       
       //Debug mode
       #ifdef debug
       cout << "\nfunction called: printRecord(char uname[]) \n"
            << "uname = " << uname << "\n\n";
       #endif
       
       //Empty phonebook
       if((this -> start) == NULL)
       {
           cout << "\nI am sorry, the phonebook is empty. \n\n";
           status = -1;
       }
       
       //No name entered, can not have no name record
       else if(strlen(uname) == 0)
       {
           status = 1;
       }
       
       //Name entered
       else
       {              
           while(current != NULL)
           {
               if(strcmp(current -> name, uname) == 0)
               {
                   cout << "\nName: " << current -> name << "\n"
                        << "Telephone#: " << current -> telno << "\n"
                        << "Year of Birth: " << current -> yearofbirth << "\n"
                        << "Address:\n" << current -> address << "\n";
                   status = 0;
               }
           
               current = current -> next;
           } 
       }  
       
       return status;
}

/****************************************************************************
*
* FUNCTION NAME:        modifyRecord
*              
* DESCRIPTION:          Modifies existing entry in phonebook.
*              
* PARAMETERS:           uname(char[]): Name of person's entry to be edited.
*                       utelno(char[]): New telephone number.
*                       uaddr(char[]): New address.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::modifyRecord(char uname[], char utelno[], char uaddr[])
{ 
       record* current;
       int status = 1;
              
       current = NULL;
       current = (this -> start);
       
       //Debug mode
       #ifdef debug
       cout << "\nfunction called: modifyRecord(char uname[], char utelno[]," 
            << " char uaddr[]) \n"
            << "uname = " << uname << "\n"
            << "utelno = " << utelno << "\n"
            << "uaddr = " << "\n" << uaddr << "\n\n";
       #endif       
       
       //Empty phonebook
       if((this -> start) == NULL)
       {
           cout << "\nI am sorry, the phonebook is empty. \n\n";
           status = -1;
       }
       
       //No name entered, can not have no name record
       else if(strlen(uname) == 0)
       {
           status = 1;
       }
       
       //Entered name       
       else
       {       
           while(current != NULL)
           {
               if(strcmp(current -> name, uname) == 0)
               {
                   strcpy(current -> telno, utelno);
                   strcpy(current -> address, uaddr);
                   status = 0;
               }
           
               current = current -> next;
           } 
       }       
       return status;
}     

/****************************************************************************
*
* FUNCTION NAME:        printAll
*              
* DESCRIPTION:          Prints all entries in phonebook.
*              
* PARAMETERS:           None.
*
* Return values:        None.
*
****************************************************************************/

void    llist::printAll()
{
        record* temp = (this -> start);
        
        //Debug mode
        #ifdef debug
        cout << "\nfunction called: printAll() \n\n";
        #endif
        
        if((this -> start) == NULL)
        {
            cout << "\nI am sorry, the phonebook is empty. \n\n";
        }
        
        while(temp != NULL)
        {
            cout << "\nName: " << temp -> name << "\n"
                 << "Telephone#: " << temp -> telno << "\n"
                 << "Year of Birth: " << temp -> yearofbirth << "\n"
                 << "Address:\n" << temp -> address << "\n";
            
            temp = temp -> next;
        }        
}

/****************************************************************************
*
* FUNCTION NAME:        deleteRecord
*              
* DESCRIPTION:          Deletes an entry from phonebook.
*              
* PARAMETERS:           uname(char[]): Name of person to be deleted.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::deleteRecord(char uname[])
{
       record* current;
       record* previous;
       
       //1: item was deleted. 
       int change;
       
       //Return value
       int status;
       
       current = NULL;
       previous = NULL;
       change = 0;
       status = 1;
       current = (this -> start);
       
       //Debug mode
       #ifdef debug      
       cout << "\nfunction called: deleteRecord(char uname[]) \n"
            << "uname = " << uname << "\n\n";
       #endif
       
       //Empty phonebook
       if((this -> start) == NULL)
       {
           cout << "\nI am sorry, the phonebook is empty. \n\n";
           status = -1;
       }
       
       //No name entered, can not have no name record
       else if(strlen(uname) == 0)
       {
           status = 1;
       }
 
       //Name entered, find entry 
       else
       {       
           while(current != NULL)
           {
               if(strcmp(current -> name, uname) == 0)
               {
                   if(current == (this -> start))
                   {
                       (this -> start) = (this -> start) -> next;
                       delete(current);
                       current = (this -> start);
                       change = 1;
                       status = 0;
                   }
               
                   if(current != (this -> start))
                   {
                       previous -> next = current -> next;
                       delete(current);
                       current = previous -> next;
                       change = 1;
                       status = 0;                       
                   }
               }
           
               if(change == 0)
               {
                   previous = current;
                   current = current -> next;
               }
           
               change = 0;
           }      
       }
      
       return status;
}

/****************************************************************************
*
* FUNCTION NAME:        reverse
*              
* DESCRIPTION:          Calls reverse() to reverses linked list of records.
*              
* PARAMETERS:           None.
*
* Return values:        None.
*
****************************************************************************/

void    llist::reverse()
{

        //Debug mode
        #ifdef debug
        cout << "\nfunction called: reverse() \n\n";
        #endif
       
        //Empty phonebook
        if((this -> start) == NULL)
        {
            cout << "\nI am sorry, the phonebook is empty. \n\n";
        }
        
        //Reverse records
        else
        {
            (this -> start) = reverse((this -> start));
        }
}

/****************************************************************************
*
* FUNCTION NAME:        reverse
*              
* DESCRIPTION:          Reverses linked list of records.
*              
* PARAMETERS:           urecord(record*): Points to record to be reversed.
*
* Return values:        rrecord(record*): Points to record reversed.
*
****************************************************************************/

record*    llist::reverse(record* urecord)
{
           record* temp = NULL;
           
           //Debug mode
           #ifdef debug
           cout << "\nfunction called: reverse(record* urecord) \n"
                << "urecord = " << urecord << "\n\n";
           #endif
           
           //Last record, done reversing
           if((urecord -> next) == NULL)
           {
               temp = urecord;
               (urecord -> next) = (this -> start);
           }
    
           //Reverse record
           else
           {
               temp = (urecord -> next);
                
               //First record
               if(urecord == (this -> start))
               {                                      
                   (urecord -> next) = NULL;
               }
               
               //Other records
               else
               {
                   
                   //Point to previous record
                   (urecord -> next) = (this -> start);
                    
                   //Moves start to next record
                   (this -> start) = urecord;
               }
                              
               temp = reverse(temp);
           }
    
           return temp;
}

/****************************************************************************
*
* FUNCTION NAME:        operator<<
*              
* DESCRIPTION:          Prints all entries in phonebook. Replaces printAll().
*              
* PARAMETERS:           out(ostream&): All entries outputted to this stream.
*                       ulist(llist&): All entries from this list outputted.
*
* Return values:        ustream(ostream&): stream object (*this).
*
****************************************************************************/

ostream&    operator<<(ostream& out, llist& ulist)
{
            record* temp = ulist.start;
  
            //Debug mode
            #ifdef debug      
            out << "\nfunction called: operator<<(ostream& out, llist& ulist)"
                << "\n"
                << "out = cout \n"
                << "ulist = ulist \n\n";
            #endif
        
            if(ulist.start == NULL)
            {
                out << "\nI am sorry, the phonebook is empty. \n\n";
            }
        
            while(temp != NULL)
            {
                out << "\nName: " << temp -> name << "\n"
                    << "Telephone#: " << temp -> telno << "\n"
                    << "Year of Birth: " << temp -> yearofbirth << "\n"
                    << "Address:\n" << temp -> address << "\n";
            
                temp = temp -> next;
            }

            return out;
}

/****************************************************************************
*
* FUNCTION NAME:        operator=
*              
* DESCRIPTION:          Copies llist.
*              
* PARAMETERS:           ulist(llist&): llist to copy.
*
* Return values:        None.
*
****************************************************************************/

void    llist::operator=(llist& ulist)
{
        (this -> start) = NULL;
        strcpy(this -> filename, "default.txt");
        record* temp = (ulist.start);
        
        //Debug mode
        #ifdef debug
        cout << "\nfunction called: operator=(llist& ulist) \n" 
             << "ulist = ulist \n\n";
        #endif
      
        //Empty list
        if((ulist.start) == NULL)
        {
            cout << "\nI am sorry, the phonebook is empty. \n\n";
        }
    
        //Copy list    
        while(temp != NULL)
        {
            this -> addRecord(temp -> name, temp -> telno,
                              temp -> yearofbirth, 
                              temp -> address);
            
            temp = temp -> next;
        }    
}

/****************************************************************************
*
* FUNCTION NAME:        writefile
*              
* DESCRIPTION:          Write linked list of records to file.
*              
* PARAMETERS:           None.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::writefile()
{
       int status = 1;
       ofstream  fileBuffer;
       fileBuffer.open((this -> filename), ios::out);
       record* temp = (this -> start);
       
       //Debug mode
       #ifdef debug      
       cout << "\nfunction called: writefile() \n";
       #endif
       
       if(!fileBuffer.fail())
       {      
           while(temp != NULL)
           {
               fileBuffer << temp -> name << "\n";
               fileBuffer << temp -> telno << "\n";
               fileBuffer << temp -> yearofbirth << "\n";
               fileBuffer << temp -> address << "@" << "\n";
            
               temp = temp -> next;
           }  
        
           if (fileBuffer.is_open())
           {
               fileBuffer.close();
           } 
            
           if(!fileBuffer.fail())
           {
               status = 0;
           } 
       }
        
       return status;
}

/****************************************************************************
*
* FUNCTION NAME:        readfile
*              
* DESCRIPTION:          Read linked list of records from file.
*              
* PARAMETERS:           None.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/

int    llist::readfile()
{
       ifstream fileBuffer;
       int numCustInFile = 0;
       char input;
       int k = 0;
       int length;
       char uname[25];
       char address[80];
       char utelno[15];
       char bday[5] = "";
       int uyob = 0;
       int status = 1;
       
       //Debug mode
       #ifdef debug      
       cout << "\nfunction called: readfile() \n\n";
       #endif

       fileBuffer.open((this -> filename), ifstream::in);

       if(!fileBuffer.fail())
       {

           /*Figure out number of records in file.*/       
           input = fileBuffer.get();
           while(!fileBuffer.eof())
           {
               if(input == '@')
               {
                   numCustInFile++;
               }
                
               input = fileBuffer.get();
           }                       
            
           fileBuffer.clear();
            
           if (fileBuffer.is_open())
           {
               fileBuffer.close();
           }
            
           fileBuffer.open((this -> filename), ifstream::in);
            
           int i;
           for(i = 1; i <= numCustInFile; i++)
           {
               fileBuffer.getline(uname, 25);                    
               fileBuffer.getline(utelno, 15);    
               fileBuffer.getline(bday, 5);
           
               uyob = atoi(bday);

               input = fileBuffer.get();
               address[k] = input;

               if(address[k] != '@')
               {
                   while(input != '@')
                   {
                       k++;
                       input = fileBuffer.get();
                       address[k] = input;
                        
                       if(input == '@')
                       {
                           address[k] = '\0';
                   
                           /*Reading \n from input buffer from previous input*/
                           fileBuffer.ignore(1);
                       }
                   }              
               }
                
               else
               {
                   address[k] = '\0';  
                    
                   /*Reading \n from input buffer from previous input*/
                   fileBuffer.ignore(1);
               } 
                
               this -> addRecord(uname, utelno, uyob, address);
                
               /*Clear address*/
               length = strlen(address);
               int j;
               for(j = 0; j < length; j++)
               {
                   address[j] = '\0';
               }
                                
               k = 0;
           }

           if (fileBuffer.is_open())
           {
               fileBuffer.close();
           }                                     
            
           if(!fileBuffer.fail())
           {
               status = 0;
           }            
       }
        
       return status;
}

/****************************************************************************
*
* FUNCTION NAME:        cleanup
*              
* DESCRIPTION:          Deletes linked list of records from heap and sets start
*                       to NULL.
*              
* PARAMETERS:           None.
*
* Return values:        None.
*
****************************************************************************/

void    llist::cleanup()
{
        record* current = NULL;
        record* previous = NULL;      
       
        //Debug mode
        #ifdef debug      
        cout << "\nfunction called: cleanup() \n\n";
        #endif
       
        current = (this -> start);
       
        while(current != NULL)
        {
            previous = current;
            current = current -> next;
            previous -> next = NULL;
            delete(previous);          
        }
       
        (this -> start) = NULL;
}
