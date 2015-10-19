/* File:        Producer_consumer_functions.cpp
 * Author:      Vengalthur Srikanth Kashyap
 * Description: This file contains the functions to be executed in this multi-threaded application
 *              Version 1.0
 * Created on October 18, 2015
 */
/*Header declaration*/
#include "Pc_header.h"
using namespace std;
/* Class functions declarations  */
//function declaration for producer


void stop_program( GtkWidget *widget, gpointer *window);
int main(int argc, char** argv){

/* getting value form the file*/
std::string line;
std::string value;
while( std::getline(input_file, line) )
{
  std::istringstream is_line(line);
  std::string key;
  while( std::getline(is_line, key, '=') )
  {
      value = key;
  }
}
/* GtkWidget is the storage type for widgets */
  gtk_init (&argc, &argv);

    Gwidgets = gwidgets;
    gwidgets->window=gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER (gwidgets->window), 10);
    gtk_widget_set_size_request(gwidgets->window, 370, 270);
    GtkAdjustment *ghorizontal = gtk_adjustment_new (0,0,0,0,0, 0);
    /* Rest in gtk_main and wait for the fun to begin! */
    /* Complete window*/
    gwidgets->completebox = gtk_box_new(GTK_ORIENTATION_VERTICAL,FALSE);
    /*input box*/
    gwidgets->inputbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE);
    gwidgets->textbox = gtk_entry_new ();
   
    gtk_entry_set_text(GTK_ENTRY(gwidgets->textbox),  value.c_str() );
    gwidgets->start_button = gtk_button_new_with_label("Start");
    gwidgets->time_box = gtk_label_new("Timer : Yet to start");
    gtk_box_pack_start(GTK_BOX(gwidgets->inputbox),gwidgets->textbox,FALSE,FALSE,2);
    gtk_box_pack_start(GTK_BOX(gwidgets->inputbox),gwidgets->start_button,FALSE,FALSE,20);
    gtk_box_pack_start(GTK_BOX(gwidgets->inputbox),gwidgets->time_box,FALSE,FALSE,2);
    gtk_box_pack_start(GTK_BOX(gwidgets->completebox),gwidgets->inputbox,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(gwidgets->start_button), "clicked", G_CALLBACK(start_program),(gpointer)gwidgets->window);
    
        
    /*items box*/
    gwidgets->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    /* Producer box view*/
    gwidgets->sw = gtk_scrolled_window_new(NULL, ghorizontal);
    gwidgets->box_producer = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gwidgets->prod_listView = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(gwidgets->sw), gwidgets->prod_listView);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gwidgets->sw),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(gwidgets->sw),GTK_SHADOW_ETCHED_IN);
    init_list(gwidgets->prod_listView);
    gwidgets->label = gtk_label_new("Items produced");
    gtk_box_pack_start(GTK_BOX(gwidgets->box_producer),gwidgets->label,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(gwidgets->box_producer),gwidgets->sw,50,50,10);
    gtk_box_pack_start(GTK_BOX(gwidgets->box),gwidgets->box_producer,1,1,2);
    /*consumer box view*/
    gwidgets->sw = gtk_scrolled_window_new(NULL, ghorizontal);
    gwidgets->box_consumer = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    gwidgets->cons_listView = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(gwidgets->sw), gwidgets->cons_listView);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gwidgets->sw),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(gwidgets->sw),GTK_SHADOW_ETCHED_IN);
    init_list(gwidgets->cons_listView);
    gwidgets->label = gtk_label_new("Items Consumed");
    gtk_box_pack_start(GTK_BOX(gwidgets->box_consumer),gwidgets->label,FALSE,FALSE,5);
     gtk_box_pack_start(GTK_BOX(gwidgets->box_consumer),gwidgets->sw,50,50,10);
     gtk_box_pack_start(GTK_BOX(gwidgets->box),gwidgets->box_consumer,20,20,2);
    gtk_box_pack_start(GTK_BOX(gwidgets->completebox),gwidgets->box,50,50,2);
    /* Footer box*/
    gwidgets->footerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE);
    gwidgets->label = gtk_label_new("Status  : ");
    gtk_box_pack_start(GTK_BOX(gwidgets->footerbox),gwidgets->label,FALSE,FALSE,2);
    gtk_box_pack_start(GTK_BOX(gwidgets->completebox),gwidgets->footerbox,FALSE,FALSE,2);
    /* Adding the widgets to the window*/
    gtk_container_add(GTK_CONTAINER(gwidgets->window),gwidgets->completebox);
    gtk_window_set_title(GTK_WINDOW(gwidgets->window), "Producer-Consumer");
    gtk_window_set_default_size(GTK_WINDOW(gwidgets->window), 500,500);
    gtk_widget_show_all(gwidgets->window);
       /* Kill the gui*/
       g_signal_connect(G_OBJECT (gwidgets->window), "destroy", G_CALLBACK (gtk_main_quit),NULL);
    gtk_main ();

    return 0;
}

Producer::Producer(Products* product){
    _prod = product;
}
Consumer::Consumer(Products* product){
    _prod = product;
}

void Producer::produce(){
   while(curr_iter <= (max_val-min_val)){
    cons_mut.lock();
    _prod->produce();
    sleep(2);
    curr_iter++;
    cons_mut.unlock();
    }
  
   
}
//function declaration for Consumer
void Consumer:: consume(){
    sleep(1);
    while(curr_iter <= (max_val-min_val) || !product_list.empty()){
    cons_mut.lock();
    _prod->consume();
    sleep(2);
    cons_mut.unlock();
      }
    check_view = true;
}
//function declaration for Products base class
void Products::produce(){
    std::unique_lock<std::mutex> locker(mut);
    int item_produced = random_number_generator();
    product_list.push(item_produced);
    string s = std::to_string(item_produced);
    add_to_list( s.c_str(), gwidgets->prod_listView,(gpointer *)gwidgets->window ,"prod");
    cond.notify_all();
    locker.unlock();
    return;

}
//function declaration for consume
void Products::consume(){
    std::unique_lock<std::mutex> locker(mut);
    int item_consumed = product_list.front();
    product_list.pop();
    string s = std::to_string(item_consumed);
    add_to_list( s.c_str(),gwidgets->cons_listView, (gpointer *)gwidgets->window,"cons" );
    cond.notify_all();
    locker.unlock();
    return;
    
}


static gboolean _label_update(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    char time[256];
    if(has_started)
    {  snprintf(time, 255, "Time elapsed: %d secs", ++sec_expired);
        gtk_label_set_label(label, time);
    }else{
        snprintf(time, 255, "Time elapsed: %d secs", sec_expired);
        gtk_label_set_label(label, time);
    }
    return true;

}
/* INPUT NUMBER GENERATIONS*/
int random_number_generator(){
    return ((min_val + curr_iter/2)*(curr_iter%2 -1)*(-1) + (max_val - curr_iter/2)*(curr_iter%2)) ;
}
//Validating the input provided by the user
bool input_validation(string input){
    stringstream inputstream(input);
    string tokens;
    while(std::getline(inputstream,tokens,','))
    {
        loop(i,tokens.size())
             if(!isdigit(tokens[i]))
                  return false;
       input_values.push_back(atoi(tokens.c_str()));     
    }
    if(input_values.size() != 2 || input_values[0] == input_values[1])
        return false;
    if(input_values[0] < 0 && input_values[1] < 0)
        return false;

    max_val = input_values[0] ; min_val = input_values[1];
    if(input_values[1]>input_values[0] )
        {min_val = input_values[0];max_val = input_values[1];
                
        }
    return true;
}

//START THE PROGRAM
void start_program( GtkWidget *widget, gpointer *window)
{ GtkListStore *store;
 GtkWidget *textbox = gwidgets->textbox;
    char buf[256];
    std::ofstream outfile(inputfile);
    string input_text = gtk_entry_get_text((GtkEntry *) textbox );
    if(!has_started){
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(gwidgets->cons_listView)));
         gtk_list_store_clear(store);
         store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(gwidgets->prod_listView)));
         gtk_list_store_clear(store);
         while( gtk_events_pending() )
                 gtk_main_iteration();
         cout<<input_text<<endl;
         curr_iter =0;
    }
  
   if(!input_text.empty())
            outfile<<"input="+input_text;
   
   if(! input_validation(input_text)  ){ 
        snprintf(buf,255,"The Invalid input");
         gtk_label_set_label(GTK_LABEL(gwidgets->label),buf );
         input_values.clear();
    }else{
        has_started = true; 
        sec_expired =0;
        g_timeout_add_seconds(1, _label_update, GTK_LABEL(gwidgets->time_box));
        Products prods;
        Producer Prod(&prods);
        Consumer Cons(&prods);
        snprintf(buf,255,"Status : the program is running");
        gtk_label_set_label(GTK_LABEL(gwidgets->label),buf );
          while( gtk_events_pending() )
                    gtk_main_iteration();
       producer_thread = std::thread(&Producer::produce,&Prod);
       consumer_thread = std::thread(&Consumer::consume,&Cons);
       while( check_view != true)
       {gtk_widget_show_now(GTK_WIDGET(gwidgets->cons_listView));
          while( gtk_events_pending() )
                 gtk_main_iteration();
       }
       producer_thread.join();
       consumer_thread.join();
       has_started = false;
        input_values.clear();
       snprintf(buf,255,"Status : the program is completed");
       gtk_label_set_label(GTK_LABEL(gwidgets->label),buf );
          while( gtk_events_pending() )
                 gtk_main_iteration();
       
       return;
}
}
/*initializing the list*/
void init_list(GtkWidget *list) {

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("Items List",
          renderer, "text", 0, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
  store = gtk_list_store_new(1, G_TYPE_STRING);
  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
  g_object_unref(store);
}
/*Adding values to the list*/
void add_to_list( const gchar *str, GtkWidget *widget, gpointer *window, string id) {
  GtkTextIter *iter;
  GtkListStore *store;
  GtkTreeIter list_iter;
  GError    *error = NULL;
  char buf[256];

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(widget)));
  gtk_list_store_append(store, &list_iter);
  gtk_list_store_set(store, &list_iter, 0, str, -1);
 gtk_tree_view_set_model(GTK_TREE_VIEW(widget), GTK_TREE_MODEL(store));
}
