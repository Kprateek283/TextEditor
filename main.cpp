#include <FL/Fl.H>
#include "EditorWindow.h"

int main(int argc, char** argv) {
    EditorWindow* window = new EditorWindow(640, 480, "Text Editor");

    window->show(argc, argv);

    if (argc > 1) {
        window->load_file(argv[1], -1);
    }

    // Run the application
    return Fl::run();
}
