#include "EditorWindow.h"

void EditorWindow::cut_cb(Fl_Widget *, void *)
{
    Fl_Text_Editor::kf_cut(0, editor);
}

void EditorWindow::copy_cb(Fl_Widget *, void *)
{
    Fl_Text_Editor::kf_copy(0, editor);
}

void EditorWindow::paste_cb(Fl_Widget *, void *)
{
    Fl_Text_Editor::kf_paste(0, editor);
}

void EditorWindow::delete_cb(Fl_Widget *, void *)
{
    textbuf->remove_selection();
}
