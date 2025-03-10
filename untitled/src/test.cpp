#include <display.h>

using namespace std;

const int CELL_SIZE = 20; // Size of each grid cell
const int WIDTH = 400;    // Window width
const int HEIGHT = 400;   // Window height

void draw_matrix(cairo_t* cr, const vector<vector<int>>& matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Set color based on value
            if (matrix[i][j] == 0)
                cairo_set_source_rgb(cr, 1, 1, 1); // White
            else if (matrix[i][j] == 1)
                cairo_set_source_rgb(cr, 0, 0, 0); // Black
            else
                cairo_set_source_rgb(cr, 1, 0, 0); // Red (for other values)

            // Draw filled rectangle
            cairo_rectangle(cr, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            cairo_fill(cr);

            // Draw grid outline
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
            cairo_rectangle(cr, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            cairo_stroke(cr);
        }
    }
}

int main()
{
    // Sample matrix
    vector<vector<int>> matrix = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // Initialize X11 display and create a window
    Display* dpy = XOpenDisplay(nullptr);
    if (!dpy)
    {
        cerr << "Cannot open display\n";
        return 1;
    }

    int screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy, screen);
    Window win = XCreateSimpleWindow(dpy, root, 10, 10, matrix[0].size() * CELL_SIZE, matrix.size() * CELL_SIZE, 1,
                                     BlackPixel(dpy, screen), WhitePixel(dpy, screen));
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    cairo_surface_t* surface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, screen),
                                                         matrix[0].size() * CELL_SIZE, matrix.size() * CELL_SIZE);
    cairo_t* cr = cairo_create(surface);

    bool running = true;
    XEvent e;
    while (running)
    {
        XNextEvent(dpy, &e);

        if (e.type == Expose)
        {
            draw_matrix(cr, matrix);
        }
        else if (e.type == KeyPress)
        {
            running = false;
        }
    }

    // Cleanup
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}
