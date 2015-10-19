/* 
 * File:   PC_header.h
 * Author: kashyap
 *
 * Created on October 12, 2015, 2:36 AM
 */

#ifndef PC_HEADER_H
#define	PC_HEADER_H
#include<thread>
#include<iostream>
#include<gtk/gtk.h>
#include<string>
#include <queue>
#include<mutex>
#include<vector>
#include<regex>
#include<chrono>
#include <stdio.h>
#include <stdlib.h>
#include<condition_variable>
#include <fstream>   
#define loop(i,n) for(int i=0;i<n;i++)
using namespace std;
/* Widget struct to be accessed from every function*/
typedef struct Guiwwidgets{
    GtkWidget *window;
    GtkWidget *box_producer, *box_consumer ,* box , *footerbox;
    GtkWidget *inputbox, *textbox, *start_button, *time_box , *completebox;
    GtkWidget *prod_listView, *cons_listView;
    GtkWidget *label, *textlabel, *sw;
}guiwidgets;
/*guiwidgets global delaration*/
class Products{
    std::condition_variable cond;

protected:
    mutex mut,cons_mut;
    queue<int> product_list;
public:
      Products(){}
      virtual void produce();
      virtual void consume();
      ~Products(){
          while(!product_list.empty())
              product_list.pop();
      }
};
 /*functions and variable declaration*/
class Producer : public Products{
    Products *_prod;
public: 
    Producer(Products *prod);
    void produce();
};
class Consumer : public Products{
    Products *_prod;
public : 
    Consumer(Products *product);
    void consume();
};

/*Functions Declaration*/
void add_to_list( const gchar *str, GtkWidget *widget, gpointer *window, string id) ;
int random_number_generator();// Generate random numbers for input
bool input_validation(string input); // Validating the input given by the user
void stop_program( GtkWidget *widget, gpointer *window); // STop the program when the program is running 
void start_program( GtkWidget *widget, gpointer *window); // Start the threaded program
void init_list(GtkWidget *list) ; // initialize the list 
void add_to_list( const gchar *str, GtkWidget *widget, gpointer *window, string id); //functions to add members to the list
/* Initializations */
static guiwidgets *Gwidgets;
const char inputfile[] = "inputfile"; // File name  can be altered depending on the file input required
std::ifstream fin(inputfile);
std::ifstream input_file(inputfile);
guiwidgets *gwidgets = g_new0(guiwidgets, 1);
/* Variable declarations*/
std::thread producer_thread;//declaring the threads
std::thread consumer_thread;
static int max_val, min_val;//the range to be specifid
static int curr_iter =0;
static int sec_expired = 0;
static string state ="start";
static vector<int> input_values;//input vector
static bool check_view = false, has_started = false;
//Condition variables
#endif	/* PC_HEADER_H */

