#ifndef UTILITIES_H
#define UTILITIES_H


// Draw dividing lines on the screen
void draw_tree(QuadNode *p, std::vector<QuadNode *> &leaves,
               Surface &surface)
{
    if (p->is_leaf())
    {
        leaves.push_back(p);
    }
    else
    {
        // Vertical
        surface.put_line(p->top_right()->xy0().first,
                         p->top_right()->xy0().second,
                         p->bottom_left()->xy1().first,
                         p->bottom_left()->xy1().second,
                         180, 180, 180);

        // Horizontal
        surface.put_line(p->bottom_left()->xy0().first,
                         p->bottom_left()->xy0().second,
                         p->top_right()->xy1().first,
                         p->top_right()->xy1().second,
                         180, 180, 180);

        draw_tree(p->top_left(), leaves, surface);
        draw_tree(p->top_right(), leaves, surface);
        draw_tree(p->bottom_left(), leaves, surface);
        draw_tree(p->bottom_right(), leaves, surface);
    }
}


void print_menu()
{
    std::cout << "\n****************MENU*************************\n\n";
    std::cout << "Insert Dots                - Left Click.\n";
    std::cout << "Slow Down Animation        - Right Click.\n";
    std::cout << "To use or not use Quadtree - Space Bar.\n";
    std::cout << "To move or not move dots   - Up arrow.\n";
    std::cout << "\n**********************************************\n";
}
#endif
