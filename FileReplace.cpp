#include "EditorWindow.h"

void EditorWindow::find2_cb(Fl_Widget *, void *)
{
    const char *find = replace_find->value();

    if (find[0] == '\0')
    {
        replace_dlg->show();
        return;
    }

    textbuf->unselect();
    static int pos = 0;
    int found;

    found = textbuf->search_forward(pos, find, &pos);

    if (found)
    {
        textbuf->select(pos, pos + strlen(find));
        fl_message("Found occurrence of '%s'.", find);
    }
    else
    {
        fl_alert("No occurrences of '%s' found!", find);
        pos = 0;
    }
}

void EditorWindow::replace_cb(Fl_Widget *, void *)
{
    replace_dlg->show();
}

void EditorWindow::replace2_cb(Fl_Widget *, void *)
{
    const char *find = replace_find->value();
    const char *replace = replace_with->value();

    if (find[0] == '\0')
    {
        replace_dlg->show();
        return;
    }

    if (replace[0] == '\0')
    {
        fl_alert("Replacement string cannot be empty!");
        return;
    }

    static int search_pos = 0;
    int found = textbuf->search_forward(search_pos, find, &search_pos);

    if (found)
    {
        textbuf->select(search_pos, search_pos + strlen(find));
        textbuf->remove_selection();
        textbuf->insert(search_pos, replace);
        search_pos += strlen(replace);
        editor->insert_position(search_pos);
        editor->show_insert_position();
    }
    else
    {
        fl_alert("No more occurrences of '%s' found!", find);
        search_pos = 0;
    }
}

void EditorWindow::replall_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    const char *find = replace_find->value();
    const char *replace = replace_with->value();

    if (find[0] == '\0')
    {
        replace_dlg->show();
        return;
    }

    if (replace[0] == '\0')
    {
        fl_alert("Replacement string cannot be empty!");
        return;
    }

    editor->insert_position(0);
    int times = 0;
    int pos = 0;
    int found;

    while ((found = textbuf->search_forward(pos, find, &pos)))
    {
        textbuf->select(pos, pos + strlen(find));
        textbuf->remove_selection();
        textbuf->insert(pos, replace);
        pos += strlen(replace);
        times++;
    }
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to find and replace all: " << elapsed_time << " seconds" << endl;

    if (times > 0)
    {
        fl_message("Replaced %d occurrences.", times);
    }
    else
    {
        fl_alert("No occurrences of '%s' found!", find);
    }
}

void EditorWindow::replcan_cb(Fl_Widget *, void *)
{
    replace_dlg->hide();
    replace_find->value("");
    replace_with->value("");
}
