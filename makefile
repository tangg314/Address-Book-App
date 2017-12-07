ui.o: ui.cpp 
	g++ -c -ansi -Wall ui.cpp 
    
llist.o: llist.cpp 
	g++ -c -ansi -Wall llist.cpp 

pro2: ui.o llist.o record.h
	g++ -o pro2 ui.o llist.o record.h

rm: ui.o
	rm ui.o llist.o  






    
    
    
    
    
    
    






