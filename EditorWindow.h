#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

#include <algorithm>

#include <sstream> 
#include <string>  
#include <ctime>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <FL/Fl_Hold_Browser.H>
using namespace std;

class EditorWindow : public Fl_Double_Window
{
public:
    EditorWindow(int w, int h, const char *t);
    ~EditorWindow();

    // Callback member functions
    void encrypt_cb(Fl_Widget *w, void *data);
    void decrypt_cb(Fl_Widget *w, void *data);
    void new_cb(Fl_Widget *, void *);
    void open_cb(Fl_Widget *, void *);
    void save_cb(Fl_Widget *, void *);
    void saveas_cb(Fl_Widget *, void *);
    void quit_cb(Fl_Widget *, void *);
    void cut_cb(Fl_Widget *, void *);
    void copy_cb(Fl_Widget *, void *);
    void paste_cb(Fl_Widget *, void *);
    void find2_cb(Fl_Widget *, void *);
    void replace_cb(Fl_Widget *, void *);
    void replace2_cb(Fl_Widget *, void *);
    void replall_cb(Fl_Widget *, void *);
    void replcan_cb(Fl_Widget *, void *);
    void delete_cb(Fl_Widget *, void *);
    void changed_cb(int pos, int nInserted, int nDeleted, int nRestyled, const char *deletedText, void *cbArg);
    void dark_cb(Fl_Widget *, void *);
    void normal_cb(Fl_Widget *, void *);

    // Supporting functions
    void load_file(const char *newfile, int ipos);
    void save_file(const char *newfile);
    int check_save();
    void set_title();
    const char *get_password();
    void draw_line_numbers();
    void draw();

    // Static callback functions
    static void static_new_cb(Fl_Widget *w, void *data);
    static void static_open_cb(Fl_Widget *w, void *data);
    static void static_save_cb(Fl_Widget *w, void *data);
    static void static_saveas_cb(Fl_Widget *w, void *data);
    static void static_quit_cb(Fl_Widget *w, void *data);
    static void static_cut_cb(Fl_Widget *w, void *data);
    static void static_copy_cb(Fl_Widget *w, void *data);
    static void static_paste_cb(Fl_Widget *w, void *data);
    static void static_find2_cb(Fl_Widget *w, void *data);
    static void static_replace_cb(Fl_Widget *w, void *data);
    static void static_replace2_cb(Fl_Widget *w, void *data);
    static void static_replall_cb(Fl_Widget *w, void *data);
    static void static_replcan_cb(Fl_Widget *w, void *data);
    static void static_delete_cb(Fl_Widget *w, void *data);
    static void static_changed_cb(int pos, int nInserted, int nDeleted, int nRestyled, const char *deletedText, void *cbArg);
    static void static_encrypt_cb(Fl_Widget *w, void *data);
    static void static_decrypt_cb(Fl_Widget *w, void *data);
    static void static_dark_cb(Fl_Widget *w, void *data);
    static void static_normal_cb(Fl_Widget *w, void *data);

    // Member variables
    Fl_Text_Editor *editor;
    Fl_Text_Buffer *textbuf;
    Fl_Window *replace_dlg;
    Fl_Input *replace_find;
    Fl_Input *replace_with;
    Fl_Button *replace_all;
    Fl_Return_Button *replace_next;
    Fl_Button *replace_cancel;
    Fl_Button *find;
    Fl_Button* dark_mode_button; // Button for dark mode
    bool dark_mode_enabled;

    char search[256];
    char filename[256];
    char title[256];
    int loading;
    int file_changed;
};

#endif // EDITOR_WINDOW_H
