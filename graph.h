#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class vertex
{
    public:
        vertex();
        vertex(const vertex & copy_from); //copy 
        vertex(char * copy_location);
        ~vertex();

        void display();
        void display_all();
        int insert_edge(class edge * to_insert);
        int remove_list();
        bool compare(char * compare);
        int set_location(char * location);

    private:
        //int copy_list( edge * copy_from);
        int copy_list(edge * head,  edge * copy_from);
        int remove_list(edge *& current);
        void display_list(edge * current);

        char * location; 
        class edge * head;           //edge list
};

class edge
{
    public:
        edge();
        edge(const edge & copy_from); //copy 
        edge(vertex & adjacent, int distance, int speed_limit);
        ~edge();

        void set_next(edge * set_from);
        edge *& get_next();
        void display();
        void read();

    private: 
        int distance;
        int speed_limit;

        vertex * adjacent;
        edge * next;
};

class graph{
    public:
        //graph();
        graph();
        ~graph();

        int load();
        int load2();
        int add_vertex(vertex * to_add);
        int find_location(char * to_find);

        int connect(char * connect_from, char * connect_to,
                        int distance, int speed_limit);
        int connect(int connect_from, int connect_to,
                        int distance, int speed_limit);
        void display_all();
    private:
        vertex ** adj_list;
        int size;
};
