//graph.cpp
#include "graph.h"

using namespace std;

vertex::vertex():location(NULL), head(NULL)
{
}

vertex::vertex(const vertex & copy_from):location(NULL), head(NULL)
{
    location = new char [strlen(copy_from.location) + 1]; 
    strcpy(location, copy_from.location);
    //copy edge list
    if(copy_from.head)
        copy_list(head, copy_from.head);
}

vertex::vertex(char * copy_location):location(NULL), head(NULL)
{
    if(location)
        delete [] location;
    location = new char [strlen(copy_location) + 1]; 
    strcpy(location, copy_location);
}

vertex::~vertex()
{
    if(location)
    {
        delete [] location;
        location = NULL;
    }
    remove_list();
}

int vertex::remove_list()
{
    remove_list(head);
    head = NULL;
    return 1;
}

int vertex::remove_list(edge *& current)
{
    if(!current)
        return 1;
    remove_list(current->get_next());
    delete current;
    current = NULL;
    return 1;
}

/*
int vertex::copy_list( edge * copy_from)
{
    return copy_from(head, copy_from);
}
*/

bool vertex::compare(char * compare) 
{
    if(location && compare)
    {
        if(strcmp(location, compare) == 0)
            return true;
        else
            return false;
    }
    return false;
}
int vertex::copy_list(edge * head,  edge * copy_from)
{
    if(!copy_from)
    {
        head = NULL;
        return 1;
    }
    head = new edge(*copy_from);
    head->set_next(NULL);
    return copy_list(head->get_next(), copy_from->get_next());
}

void vertex::display()
{
    if(location)
        cout << location;
}

void vertex::display_all()
{
    //cout << "\nIN VERTEX::DISPLAY_ALL()\n";
    cout << "Location: ";
    display();
    cout << endl;
    if(!head)
        cout << "No connecting roads\n";
    cout << "Has roads to: ";
    display_list(head);
    cout << endl;
}

void vertex::display_list(edge * current)
{
    if(!current)
        return;
    current->display();
    cout << ", ";
    display_list(current->get_next());
}

int vertex::insert_edge(edge * to_insert)
{
    if(!head)
    {
        head = new edge(*to_insert);
        edge * temp = NULL;
        head->set_next(temp);
    }
    else
    {
        edge * temp = new edge(*to_insert);
        temp->set_next(head);
        head = temp;
    }
    return 1;
}

int vertex::set_location(char * location)
{
    //cout << "in set_location...";
    if(this->location)
    {
        delete [] this->location;
    }
    //cout << "copying....";
    this->location = new char [strlen(location) + 1];
    strcpy(this->location, location);
    //cout << this->location;
    return 1;
}
////////////////EDGE CLASS///////////////////////////////////

edge::edge():distance(1), speed_limit(25), adjacent(NULL), next(NULL)
{
}

edge::edge(const edge & copy_from):next(NULL)
{
    adjacent = new vertex(*copy_from.adjacent);
    next = copy_from.next;
    distance = copy_from.distance;
    speed_limit = copy_from.speed_limit;
}

edge::edge(vertex & adjacent, int distance, int speed_limit):distance(distance),
    speed_limit(speed_limit), next(NULL)
{
    this->adjacent = &adjacent; 
}

edge::~edge()
{
    if(adjacent)
    {
        delete adjacent;
        adjacent = NULL;
    }
    next = NULL;
}

void edge::set_next( edge * set_from)
{
    next = set_from;
}

edge *& edge::get_next()
{
    return next;
}

void edge::display()
{
    adjacent->display();
}

void edge::read()
{

}


////////////////GRAPH CLASS/////////////////////////////////
graph::graph():adj_list(NULL), size(20)
{
    adj_list = new vertex * [size];
    for(int i = 0; i < size; ++i)
    {
        adj_list[i] = NULL;
    }
}

graph::~graph()
{
    for(int i = 0; i < size; ++i)
    {
        if(adj_list[i])
        {
            delete adj_list[i];
            adj_list[i] = NULL;
        }
        else
            break;
    }
    /*
    if(adj_list)
        delete adj_list;
        */
}

int graph::add_vertex(vertex * to_add)
{
    //cout << "\nIN GRAPH::ADD_VERTEX(VERTEX * TO_ADD)\n";
    //cout << "SIZE: " << size << endl;
    int i = 0;
    while(adj_list[i])
        ++i;
    //cout << "\ni = " << i << endl;
    if(i < size)
    {
        //cout << "\nCreating new vertex at adj_list[" << i << "].\n";
        adj_list[i] = new vertex(*to_add);
        return 1;
    }
    else
        return 0;
}

int graph::find_location(char * to_find)
{
    for(int i = 0; i < size; ++i)
    {
        if(adj_list[i]->compare(to_find))
        {
            return i;
        }
    }
    return 999;
}

int graph::connect(char * connect_from, char * connect_to, int distance,
        int speed_limit)
{
    //add connect_to to connect_from's edge list
    //vertex v_from;
    //vertex v_to;
    int key_from = find_location(connect_from); 
    int key_to = find_location(connect_to); 
    if(key_from == 999 || key_to == 999)
        return 0;
    edge * edge_to_insert = new edge(*adj_list[key_to], distance, speed_limit);
    adj_list[key_from]->insert_edge(edge_to_insert);
    return 1;
}

int graph::connect(int connect_from, int connect_to,
                        int distance, int speed_limit)
{
    edge * edge_to_insert = new edge(*adj_list[connect_to], distance, speed_limit);
    adj_list[connect_from]->insert_edge(edge_to_insert);
    return 1;
}

void graph::display_all()
{
    int i = 0;
    if(!adj_list[i])
    {
        cout << "\nThe map is empty...\n";
        return;
    }
    while(adj_list[i])
    {
        adj_list[i]->display_all();
        ++i;
    }
}

int graph::load2()
{
    char * location = NULL;
    char num[2];
    vertex * a_vertex = NULL;
    srand (time(NULL));
    int from = 0;
    int to = 0;

    //creat locations 1-20 and add to vertex array
    for(int i = 1; i <= size; ++i)
    {
        if(i < 10)
        {
            num[0] = '0' + i;
            num[1] = '\0';
        }
        else if(i >= 10 && i < 100)
        {
            num[0] = '0' + (i/10);
            num[1] = '0' + (i%10);
            num[2] = '\0';
        }
        char * location = new char [strlen("Location ") + strlen(num) + 1];
        strcpy(location, "Location "); 
        strcat(location, num);
        a_vertex = new vertex(location); 
        add_vertex(a_vertex);
    }

    connect(0,1, rand() % 70 + 15, rand() % 20 + 1);
    connect(0,(rand() % 19), rand() % 70 + 15, rand() % 20 + 1);
    connect(19,18, rand() % 70 + 15, rand() % 20 + 1);
    connect(19,(rand() % 19), rand() % 70 + 15, rand() % 20 + 1);

    for(int i = 1; i < size - 1; ++i)
    {
        connect(i,i + 1, rand() % 70 + 15, rand() % 20 + 1);
        connect(i,i - 1, rand() % 70 + 15, rand() % 20 + 1);
        connect(i,(rand() % 19), rand() % 70 + 15, rand() % 20 + 1);
    }
}

int graph::load()
{
    char * location = NULL;
    char * location2 = NULL;
    char num[2];
    char num2[2];
    int digit = 0;
    vertex * a_vertex = NULL;
    srand (time(NULL));

    for(int i = 0; i < size; ++i)
    {
        //Generate locations and insert into graph...
        digit = i + 1;
        if(digit < 10)
        {
            num[0] = '0' + digit;
            num[1] = '\0';
        }
        else if(digit >= 10 && digit < 20)
        {
            num[0] = '1';
            num[1] = '0' + (digit-10);
            num[2] = '\0';
        }
        else
        {
            num[0] = '2';
            num[1] = '0' + (digit - 20);
            num[2] = '\0';
        }

        char * location = new char [strlen("Location 00") + 1];
        strcpy(location, "Location "); 
        strcat(location, num);
        //cout << location;

        a_vertex = new vertex(location); 
        add_vertex(a_vertex);
    }
    //add connections
    for(int i = 0; i < size; ++i)
    {
        digit = i + 1;
        if(digit < 10)
        {
            num[0] = '0' + digit;
            num[1] = '\0';
            num2[0] = '0' + (digit + 1);
            num2[1] = '\0';
        }
        else if(digit >= 10 && digit < 20)
        {
            num[0] = '1';
            num[1] = '0' + (digit-10);
            num[2] = '\0';
            num2[0] = '1';
            num2[1] = '0' + (digit-10) + 1;
            num2[2] = '\0';
        }
        else
        {
            num[0] = '2';
            num[1] = '0' + (digit - 20);
            num[2] = '\0';
            num2[0] = '1';
            num2[1] = '\0';
        }

        char * location = new char [strlen("Location 1") + 2];
        strcpy(location, "Location "); 
        strcat(location, num);

        char * location2 = new char [strlen("Location 1") + 2];
        strcpy(location2, "Location "); 
        strcat(location2, num2);

        //cout << endl << location << "->" << location2;
        connect(location, location2, 5, 35);
        //cout << endl << location2 << "->" << location;
        connect(location2, location, 5, 35);
    }



    return 1;

/*
        cout << "\nConnecting Location 1 to Location 2...\n";
        connect("Location 1", "Location 2", 5, 35);

        cout << "\nConnecting Location 2 to Location 1...\n";
        connect("Location 2", "Location 1", 5, 35);
        */
}

