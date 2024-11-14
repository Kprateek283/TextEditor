#include "EditorWindow.h"
#include <iostream>
using namespace std;

void EditorWindow::draw_line_numbers()
{
    string text = textbuf->text();
    int total_lines = count(text.begin(), text.end(), '\n') + 1;
    int line_height = fl_height();
    int x = 2;
    int y = editor->y() + line_height;

    fl_color(FL_BLACK);
    for (int i = 0; i < total_lines; ++i)
    {
        fl_draw(to_string(i + 1).c_str(), x, y);
        y += line_height;
    }
}

void EditorWindow::draw()
{
    Fl_Window::draw();
    draw_line_numbers();
}

void EditorWindow::dark_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    editor->color(FL_BLACK);
    editor->textcolor(FL_WHITE);
    editor->redraw();
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to change to dark mode: " << elapsed_time << " seconds" << endl;
}

void EditorWindow::normal_cb(Fl_Widget *, void *)
{
    clock_t start_time = clock();
    editor->color(FL_WHITE);
    editor->textcolor(FL_BLACK);
    editor->redraw();
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken to change to normal mode: " << elapsed_time << " seconds" << endl;
}
