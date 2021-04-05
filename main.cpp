#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Dot.h"
#include "QuadNode.h"
#include "Utilities.h"

/*****************************************************************************
Author: Sushil Kharal
Last Modified: 16 Dec 2020
Description: Detection of circular objects in 2D surface using Quadtree
*****************************************************************************/
// Detect if two circles are colliding.
bool collision_detection(const Dot *dot1, const Dot *dot2)
{
    return (pow(dot1->x() - dot2->x(), 2) +
                pow(dot1->y() - dot2->y(), 2) <=
            pow(dot1->r() + dot2->r(), 2));
}

int main()
{
    int max_depth;
    bool use_quadtree;
    bool move_dots = false;
    std::cout << "Please enter max depth: ";
    std::cin >> max_depth;
    std::cout << "Use Quadtree? (0 No 1 Yes): ";
    std::cin >> use_quadtree;
    print_menu();

    Surface surface(W, H);
    Event event;
    KeyPressed keypressed;
    int slow_down = 10;
    int time1 = getTicks();
    int time2 = getTicks();

    std::vector<Dot *> dots;
    std::vector<QuadNode *> leaves;

    while (1)
    {
        QuadNode *root = new QuadNode(std::pair<int, int>(0, 0),
                                      std::pair<int, int>(W, H),
                                      NULL, 0, max_depth);
        if (event.poll() && event.type() == QUIT)
            break;

        // right click mouse to slow down/ speed up.
        if (mouse_right() && (time2 + 150 < getTicks()))
        {
            slow_down = (slow_down == 10 ? 50 : 10);
            time2 = getTicks();
        }

        // If keypressed is space, change value of use_quadtree.
        if (time1 + 100 < getTicks())
        {
            keypressed = get_keypressed();
            if (keypressed[SPACE])
            {
                use_quadtree = (use_quadtree ? false : true);
            }
            else if (keypressed[UPARROW])
            {
                move_dots = (move_dots ? false : true);
            }
            time1 = getTicks();
        }

        surface.lock();
        surface.fill({230, 230, 230});

        // left click mouse to add dots.
        if (mouse_left() && (time1 + 50 < getTicks()) && dots.size() < 2000)
        {
            dots.push_back(new Dot(&surface, mouse_x(), mouse_y()));
            time1 = getTicks();
        }

        // move dots, insert them in tree and draw them on surface.
        for (int i = 0; i < dots.size(); ++i)
        {
            if (move_dots)
            {
                dots[i]->check_direction();
            }
            root->insert(dots[i]);
            dots[i]->draw();
        }

        // root->get_leaves(leaves);

        // if use_quadtree, use quadtree for collision detection within leaves.
        if (use_quadtree)
        {
            draw_tree(root, leaves, surface);

            for (auto &it1 : leaves)
            {
                for (auto &it2 : it1->dots())
                {
                    for (auto &it3 : it1->dots())
                    {
                        if (it2 == it3)
                        {
                            continue;
                        }
                        if (collision_detection(it2, it3))
                        {
                            it2->change_color();
                            it2->collided() = true;
                            it3->change_color();
                            it3->collided() = true;
                        }
                    }
                }
            }
        }

        // if use_quadtree is false, detect collision using vector of dots.
        if (!use_quadtree)
        {
            for (int i = 0; i < dots.size(); ++i)
            {
                for (int j = 0; j < dots.size(); ++j)
                {
                    // if same dot or both dots have already collided
                    // skip them
                    if (dots[i] == dots[j] ||
                        (dots[i]->collided() && dots[j]->collided()))
                    {
                        continue;
                    }
                    if (collision_detection(dots[i], dots[j]))
                    {
                        dots[i]->change_color();
                        dots[i]->collided() = true;
                        dots[j]->change_color();
                        dots[j]->collided() = true;
                    }
                }
            }
        }

        // clear leaves
        leaves.clear();
        surface.unlock();
        surface.flip();
        delay(slow_down);
    }
}
