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
* FILE:                 record.h
*      
* DESCRIPTION:          This file contains definition of record.
*
*****************************************************************************/

#ifndef _record_H_INCLUDED_
#define _record_H_INCLUDED_

struct    record
{
          char name[25];
          char address[80];
          int yearofbirth;
          char telno[15];
          struct record* next;
};

#endif

