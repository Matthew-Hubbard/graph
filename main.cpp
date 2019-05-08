#include "graph.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int get_location(char *& location);

int main()
{
    graph map;
    map.load2();
    map.display_all();
    /*
    char num[2];
    for(int i = 1; i <= 20; ++i)
    {
        if(i < 10)
        {
            num[0] = '0' + i;
            num[1] = '\0';
        }
        else if(i >= 10 && i < 20)
        {
            num[0] = '1';
            num[1] = '0' + (i-10);
            num[2] = '\0';
        }
        else
        {
            num[0] = '2';
            num[1] = '0' + (i - 20);
            num[2] = '\0';
        }

        char * location = new char [strlen("Location 1") + 1];
        strcpy(location, "Location "); 
        strcat(location, num);

        cout << endl << location << endl;

    }
    */




    /*
    graph map;

    char * location = NULL;
    vertex * a_vertex;
    //char response = '\0';

    location = new char [strlen("Location 1") + 1];
    strcpy(location, "Location 1");
    cout << endl << "Creating " << location << "." << endl;
    a_vertex = new vertex(location); 
    cout << endl;
    a_vertex->display_all();

    cout << endl << "Adding " << location << " to map..." << endl;
    map.add_vertex(a_vertex);

    strcpy(location, "Location 2");
    cout << endl << "Creating " << location << "." << endl;
    a_vertex = new vertex(location); 
    cout << endl;
    a_vertex->display_all();

    cout << endl << "Adding " << location << " to map..." << endl;
    map.add_vertex(a_vertex);

    cout << "\nConnecting Location 1 to Location 2...\n";
    map.connect("Location 1", "Location 2", 5, 35);

    cout << "\nConnecting Location 2 to Location 1...\n";
    map.connect("Location 2", "Location 1", 5, 35);


    cout << "\ndisplaying map...\n";
    map.display_all();
    */

    /*
    vertex found;
    int index = map.find_location("Location 2");
    cout << "\nFound at " << index << endl;
    */
    
    
  /* 
    do
    {
        if(!get_location(location))
            cout << "\nCouldn't get location.\n";
        cout << endl << "Adding " << location << " to map..." << endl;
        a_vertex->set_location(location);
        a_vertex->display_all();
        cout << "\nEnter another location? (Y/N): ";
        cin >> response;
    }while(toupper(response) == 'Y');
    if(location)
    {
        delete [] location;
        location = NULL;
    }
    if(a_vertex)
    {
        delete a_vertex;
        a_vertex = NULL;
    }
    */

}

int get_location(char *& location)
{
    char temp[100];
    cout << "\nEnter location: ";
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');

    if(location)
        delete [] location;
    location = new char [strlen(temp) + 1];
    strcpy(location, temp);
    return 1;
}
//test
