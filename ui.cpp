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
* FILE:                 ui.cpp
*      
* DESCRIPTION:          This file contains user interface of project 2.
*
*****************************************************************************/
                             
/****************************************************************************
*
* FUNCTION NAME:        main
*              
* DESCRIPTION:          User interface.
*              
* PARAMETERS:           argc(int): Number of command line arguments.
*                       argv(char[]): Array of command line arguments.
*
* Return values:        (int): if method successful, 0.
*                       (int): if method failed, other.
*
****************************************************************************/
#include "llist.h"

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <limits>

using namespace std;

int    exCommand(llist&, string);

int    main(int argc, char* argv[])
{
       //Stores user input
       string input = "";
       
       //Execute command status
       int commandResults = 0;
       
       //Stores records
       llist mylist("proj2.txt");
       
       //Pointer to mylist
       llist& plist = mylist;
       
       //Welcome message
       cout << "\nHi, welcome to your address book! \n\n"
            << "What would  you like to do? For help, please enter Help. \n"
            << ">";
            
       //Get command 
       getline(cin, input);
       commandResults = exCommand(plist, input);
       
       //Keep getting command until quit command
       while(commandResults != 0)
       {
           cout << "What would  you like to do? For help, please enter Help. \n"
                << ">";
           
           //Get command 
           getline(cin, input);
           commandResults = exCommand(plist, input);   
       }
       
       return 0;
}

/****************************************************************************
*
* FUNCTION NAME:        exCommand
*              
* DESCRIPTION:          Executes requested command.
*              
* PARAMETERS:           ulist(llist&): Gives access to linked list functions.
*                       command(string): Command to execute.
*
* Return values:        0: Exit program called.
*                       other: command processed.
*
****************************************************************************/

int    exCommand(llist& ulist, string command)
{
       char name[25] = "";
       char address[80] = "";
       char telno[15] = "";
       char bday[5] = "";
       int yearofbirth = 0;
       int results = 1;
       int exStatus = 1;
       
       //Add command
       if(command.compare("add") == 0 || command.compare("Add") == 0)
       {
           cout << "\nPlease enter the person's: \n\n";
            
           //Get name and removes long entries
           cout << "Name: ";                
           cin.getline(name, 25);
           
           if(!cin.good())
           {
               cin.clear();                      
               cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
           }
           
           //Repeatedly asks for name
           while(strlen(name) == 0)
           {
               cout << "Please enter a Name: ";                
               cin.getline(name, 25);
               
               if(!cin.good())
               {
                   cin.clear();                      
                   cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
               }
           }           

           //Get telephone# and removes long entries
           cout << "Telephone#: ";
           cin.getline(telno, 15);

           if(!cin.good())
           {
               cin.clear();                      
               cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
           }           
           
           //Get year of birth and removes long entries
           cout << "Year of Birth: ";
           cin.getline(bday, 5);

           if(!cin.good())
           {
               cin.clear();                      
               cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
           }
           
           yearofbirth = atoi(bday);
           
           //Get address
           cout << "Address(@ to save): \n";
           cin.getline(address, 80, '@'); 

           if(!cin.good())
           {
           
               //If user entered too long of address, clears buffer error 
               cin.clear();
           
               //If address was too long, reads the rest of address entry
               cin.ignore(numeric_limits<std::streamsize>::max(), '@');                    
           }     

           //Reads \n
           cin.ignore(1);           
                      
           //Saving info
           ulist.addRecord(name, telno, yearofbirth, address);
           cout << "\nInformation saved. \n\n";   
       }
       
       //Search command
       else if(command.compare("search") == 0 || command.compare("Search") == 0)
       {
           //Check if phonebook empty
           exStatus = ulist.printRecord("");
       
           if(exStatus >= 0)
           {
               cout << "\nWho's entry would you like to look up? \n\n";  

               /*Get info and removes long entries*/
               cout << "Name: ";
               cin.getline(name, 25);

               if(!cin.good())
               {
                   cin.clear();                      
                   cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
               }
			
               exStatus = ulist.printRecord(name); 
           
               if(exStatus == 0)
               {
                   printf("\n");
               }
           
               else if(exStatus == 1)
               {
                   printf("\nI am sorry, that name was not found. \n\n");
               }                         
           }                  
       }
       
       //Edit command
       else if(command.compare("edit") == 0 || command.compare("Edit") == 0)
       {
       
           //Check if phonebook empty
           exStatus = ulist.modifyRecord("", "", "");
       
           if(exStatus >= 0)
           {
               cout << "\nWho's entry would you like to change: \n\n";  

               /*Get info and removes long entries*/
               cout << "Name: ";
               cin.getline(name, 25);

               if(!cin.good())
               {
                    cin.clear();                      
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
               } 

               //Verify name exists.
               exStatus = ulist.printRecord(name);
               
               if(exStatus == 1)
               {
                   cout << "\nI am sorry, that name was not found. \n\n";
               }

               else
               {           
                   cout << "Please enter the person's new information: \n\n";
            
                   //Get telephone# and removes long entries
                   cout << "Telephone#: ";
                   cin.getline(telno, 15);

                   if(!cin.good())
                   {
                       cin.clear();                      
                       cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                   } 
            
                   //Get address
                   cout << "Address(@ to save): \n";
                   cin.getline(address, 80, '@'); 

                   if(!cin.good())
                   {
           
                       //If user entered too long of address, clears buffer error 
                       cin.clear();
           
                       //If address was too long, reads the rest of address entry
                       cin.ignore(numeric_limits<std::streamsize>::max(), '@');                    
                   }     

                   //Reads \n
                   cin.ignore(1);
			
                   exStatus = ulist.modifyRecord(name, telno, address);
           
                   if(exStatus == 0)
                   {          
                       cout << "\nNew information saved. \n\n";
                   }
               }
           }                      
       }
       
       //All command
       else if(command.compare("all") == 0 || command.compare("All") == 0)
       {
           cout << ulist;
           cout << "\n";
       }
       
       //Delete command
       else if(command.compare("delete") == 0 || command.compare("Delete") == 0)
       {	
       
           //Check if phonebook empty
           exStatus = ulist.deleteRecord("");
       
           if(exStatus >= 0)
           {
               cout << "\nWhose entry would you like to delete? \n\n";
			
               /*Get info and removes long entries*/
               cout << "Name: ";
               cin.getline(name, 25);

               if(!cin.good())
               {
                   cin.clear();                      
                   cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
               }               
			
               exStatus = ulist.deleteRecord(name);
           
               if(exStatus == 0)
               {
                   cout << "\nEntry deleted. \n\n";
               }

               else if(exStatus == 1)
               {
                   cout << "\nI am sorry, that name was not found. \n\n";
               }           
           }           
       }
       
       //Reverse command
       else if(command.compare("reverse") == 0 || command.compare("Reverse") == 0)
       {
           ulist.reverse();
           cout << "\n";
       }
       
       //Quit command
       else if(command.compare("quit") == 0 || command.compare("Quit") == 0)
       {
           results = 0;
           cout << "\nGood bye... \n";
       }
		
       //Help menu
       else
       {
           cout << "\nPlease enter one of the following options: \n\n"
                << "Add: To add a new entry to your address book.\n"
                << "Edit: To edit an existing entry.\n"
                << "Search: To look up an existing entry.\n"
                << "All: To list all entries in your address book.\n"
                << "Delete: To delete an existing entry.\n"
                << "Reverse: To reverse the ordering of the phonebook entries.\n"
                << "Quit: To exit your address book.\n\n";
       }
       
       return results;
}


  
