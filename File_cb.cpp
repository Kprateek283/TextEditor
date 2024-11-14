#include "EditorWindow.h"

void EditorWindow::new_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    if (!check_save())
        return;

    filename[0] = '\0';
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();
    file_changed = 0;
    textbuf->call_modify_callbacks();
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to start new file: " << elapsed_time << " seconds" << endl;
}

void EditorWindow::open_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    if (!check_save())
        return;

    const char *newfile = fl_file_chooser("Open File?", "*", filename);
    if (newfile != nullptr)
    {
        load_file(newfile, -1);
    }
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to open file: " << elapsed_time << " seconds" << endl;
}

void EditorWindow::save_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    if (filename[0] == '\0')
    {
        saveas_cb(nullptr, nullptr);
        return;
    }
    else
    {
        save_file(filename);
    }
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to save file: " << elapsed_time << " seconds" << endl;
}

void EditorWindow::saveas_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    const char *newfile = fl_file_chooser("Save File As?", "*", filename);
    if (newfile != nullptr)
    {
        save_file(newfile);
    }clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to save file: " << elapsed_time << " seconds" << endl;
}

void EditorWindow::quit_cb(Fl_Widget *, void *)
{
    if (!check_save())
        return;
    exit(0);
}

void EditorWindow::changed_cb(int, int nInserted, int nDeleted, int, const char *, void *cbArg)
{
    EditorWindow *w = (EditorWindow *)cbArg;
    if ((nInserted || nDeleted) && !loading)
        file_changed = 1;
    w->set_title();
    if (loading)
        editor->show_insert_position();
}