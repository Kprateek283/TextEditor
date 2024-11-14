#include "EditorWindow.h"
#include <iostream>
using namespace std;

EditorWindow::EditorWindow(int w, int h, const char *t) : Fl_Double_Window(w, h, t), dark_mode_enabled(false)
{
    loading = 0;
    file_changed = 0;
    filename[0] = '\0';
    search[0] = '\0';

    textbuf = new Fl_Text_Buffer();

    // menu bar
    Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, w, 30);
    m->add("&File/&New File", 0, static_new_cb, this);
    m->add("&File/&Open File...", FL_COMMAND + 'o', static_open_cb, this);
    m->add("&File/&Save File", FL_COMMAND + 's', static_save_cb, this);
    m->add("&File/Save File &As...", FL_COMMAND + FL_SHIFT + 's', static_saveas_cb, this);
    m->add("&File/E&xit", FL_COMMAND + 'q', static_quit_cb, this);

    m->add("&Edit/&Cut", FL_COMMAND + 'x', static_cut_cb, this);
    m->add("&Edit/&Copy", FL_COMMAND + 'c', static_copy_cb, this);
    m->add("&Edit/&Paste", FL_COMMAND + 'v', static_paste_cb, this);
    m->add("&Edit/&Delete", 0, static_delete_cb, this);

    m->add("&Find or Replace...", FL_COMMAND + 'f', static_replace_cb, this);

    m->add("&Security/&Encrypt File", FL_COMMAND + 'e', static_encrypt_cb, this);
    m->add("&Security/Decrypt File", FL_COMMAND + 'd', static_decrypt_cb, this);

    m->add("&Dark Mode/&On", FL_COMMAND + 'D',static_dark_cb,this);
    m->add("&Dark Mode/&Off", FL_COMMAND + 'N',static_normal_cb,this);

    editor = new Fl_Text_Editor(10, 30, w, h - 30);
    editor->buffer(textbuf);
    editor->textfont(FL_COURIER);

    textbuf->add_modify_callback(static_changed_cb, this);
    textbuf->call_modify_callbacks();
    
    replace_dlg = new Fl_Window(400, 150, "Find/Replace");  
    replace_find = new Fl_Input(70, 10, 200, 25, "Find:");   
    replace_with = new Fl_Input(70, 40, 200, 25, "Replace:"); 

    find = new Fl_Button(10, 70, 60, 25, "Find");
    replace_all = new Fl_Button(80, 70, 100, 25, "Replace All");
    replace_next = new Fl_Return_Button(190, 70, 100, 25, "Replace Next"); 
    replace_cancel = new Fl_Button(300, 70, 60, 25, "Cancel"); 

    // Callbacks
    find->callback(static_find2_cb, this);             
    replace_all->callback(static_replall_cb, this);   
    replace_next->callback(static_replace2_cb, this);  
    replace_cancel->callback(static_replcan_cb, this); 

    replace_dlg->end();

    resizable(this);



    end();
}

// Destructor
EditorWindow::~EditorWindow()
{
    delete textbuf;
    delete replace_dlg;
}
