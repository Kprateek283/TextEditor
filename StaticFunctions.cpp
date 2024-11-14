#include "EditorWindow.h"

void EditorWindow::static_new_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->new_cb(w, data);
}

void EditorWindow::static_open_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->open_cb(w, data);
}

void EditorWindow::static_save_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->save_cb(w, data);
}

void EditorWindow::static_saveas_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->saveas_cb(w, data);
}

void EditorWindow::static_quit_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->quit_cb(w, data);
}

void EditorWindow::static_cut_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->cut_cb(w, data);
}

void EditorWindow::static_copy_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->copy_cb(w, data);
}

void EditorWindow::static_paste_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->paste_cb(w, data);
}

void EditorWindow::static_find2_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->find2_cb(w, data);
}

void EditorWindow::static_replace_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->replace_cb(w, data);
}

void EditorWindow::static_replace2_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->replace2_cb(w, data);
}

void EditorWindow::static_replall_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->replall_cb(w, data);
}

void EditorWindow::static_replcan_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->replcan_cb(w, data);
}

void EditorWindow::static_delete_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->delete_cb(w, data);
}

void EditorWindow::static_changed_cb(int pos, int nInserted, int nDeleted, int nRestyled, const char *deletedText, void *cbArg)
{
    EditorWindow *editorWindow = (EditorWindow *)cbArg;
    ((EditorWindow *)cbArg)->changed_cb(pos, nInserted, nDeleted, nRestyled, deletedText, cbArg);
    editorWindow->redraw(); 
}

void EditorWindow::static_encrypt_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->encrypt_cb(w, data);
}

void EditorWindow::static_decrypt_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->decrypt_cb(w, data);
}

void EditorWindow::static_dark_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->dark_cb(w, data);
}

void EditorWindow::static_normal_cb(Fl_Widget *w, void *data)
{
    ((EditorWindow *)data)->normal_cb(w, data);
}