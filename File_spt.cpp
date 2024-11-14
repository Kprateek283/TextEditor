#include "EditorWindow.h"

void EditorWindow::load_file(const char *newfile, int ipos)
{
    loading = 1;
    int insert = (ipos != -1);
    file_changed = insert;

    int r;
    if (!insert)
    {
        r = textbuf->loadfile(newfile);
    }
    else
    {
        r = textbuf->insertfile(newfile, ipos);
    }

    if (r != 0)
    {
        fl_alert("Error reading from file '%s':\n%s.", newfile, strerror(errno));
    }
    else
    {
        if (!insert)
        {
            strncpy(filename, newfile, sizeof(filename) - 1);
            filename[sizeof(filename) - 1] = '\0';
        }
    }

    loading = 0;
    textbuf->call_modify_callbacks();
}

void EditorWindow::save_file(const char *newfile)
{
    if (textbuf->savefile(newfile) != 0)
    {
        fl_alert("Error writing to file '%s':\n%s.", newfile, strerror(errno));
    }
    else
    {
        strncpy(filename, newfile, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        file_changed = 0;
    }

    textbuf->call_modify_callbacks();
}

int EditorWindow::check_save()
{
    if (!file_changed)
        return 1;

    int r = fl_choice("The current file has not been saved.\n"
                      "Would you like to save it now?",
                      "Cancel", "Save", "Don't Save");

    if (r == 1)
    {
        save_cb(nullptr, nullptr);
        return !file_changed;
    }

    return (r == 2) ? 1 : 0;
}

void EditorWindow::set_title()
{
    if (filename[0] == '\0')
    {
        strcpy(title, "Untitled");
    }
    else
    {
        const char *slash = strrchr(filename, '/');
#ifdef _WIN32
        if (!slash)
            slash = strrchr(filename, '\\');
#endif
        if (slash)
        {
            strcpy(title, slash + 1);
        }
        else
        {
            strcpy(title, filename);
        }
    }

    if (file_changed)
        strcat(title, " (modified)");
    label(title);
}

