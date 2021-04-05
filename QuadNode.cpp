//File: QuadNode.cpp
//Author: Sushil Kharal
//Description: Implementation of function prototypes in QuadNode.h

#include "QuadNode.h"
#include <iostream>

QuadNode::QuadNode(std::pair< int, int > xy0,
         std::pair< int, int > xy1,
         QuadNode * parent, int depth, int max_depth)
    :xy0_(xy0), xy1_(xy1),
     parent_(parent), depth_(depth), max_depth_(max_depth)
{
    capacity_ = 4;
    is_leaf_ = true;
}

QuadNode::~QuadNode()
{
    if (is_leaf_ && this != NULL)
    {
        dots_.clear(); // since dot * are being used by vector in main.

        // if dot * are not used in other places, use this.
        // for (int i = 0; i < dots_.size(); ++i)
        // {
        //     delete dots_[i];
        // }
        delete this;
    }
    else
    {
        top_left_->delete_node();
        top_right_->delete_node();
        bottom_left_->delete_node();
        bottom_right_->delete_node();
    }
}


std::pair< int, int > QuadNode::xy0() const
{
    return xy0_;
}


std::pair< int, int > QuadNode::xy1() const
{
    return xy1_;
}


int QuadNode::depth() const
{
    return depth_;
}


bool QuadNode::is_leaf() const
{
    return is_leaf_;
}


QuadNode * QuadNode::parent() const
{
    return parent_;
}


QuadNode * QuadNode::top_left() const
{
    return top_left_;
}


QuadNode * QuadNode::top_right() const
{
    return top_right_;
}


QuadNode * QuadNode::bottom_left() const
{
    return bottom_left_;
}


QuadNode * QuadNode::bottom_right() const
{
    return bottom_right_;
}


std::vector< Dot * > QuadNode::dots() const
{
    return dots_;
}



//Check if the dot being inserted falls within the bound
// of the window
bool QuadNode::in_bounds(const Dot * dot)
{
    return ((dot->x() - dot->r() >= xy0_.first &&
             dot->x() + dot->r() <= xy1_.first) &&
            (dot->y() - dot->r() >= xy0_.second &&
             dot->y() + dot->r() <= xy1_.second));
}


// Traverse down to the leaf node and insert dot objects at appropriate
// leaf node
void QuadNode::insert(Dot * dot)
{
    if (!in_bounds(dot))
    {
        // std::cout << "not in bounds\n";
        return;
    }

    //If the current node is not leaf node, find appropriate
    // root to terverse down to
    if (!is_leaf_)
    {
        if (top_left_->in_bounds(dot))
        {
            return top_left_->insert(dot);
        }
        else if (top_right_->in_bounds(dot))
        {
            return top_right_->insert(dot);
        }
        else if (bottom_left_->in_bounds(dot))
        {
            return bottom_left_->insert(dot);
        }
        else if (bottom_right_->in_bounds(dot))
        {
            return bottom_right_->insert(dot);
        }
        return;
    }
        
    // If it is leaf node push the dot objects into dots_ vector
    if (is_leaf_ && in_bounds(dot))
    {
        // std::cout << '(' << xy0_.first << "," << xy0_.second << ") ";
        // std::cout << '(' << xy1_.first << "," << xy1_.second << ")\n";

        // std::cout << "is leaf and in bounds inserting\n";
        // std::cout << dot->x() << ' ' << dot->y() << std::endl;
        dots_.push_back(dot);   
    }

    // if dots_ vector becomes greater than the capacity, create children,
    // assign dots objects to appropriate child node, and mark node not as leaf.
    if (is_leaf_ && in_bounds(dot) && dots_.size() > capacity_ && depth_ < max_depth_ &&
        (xy1_.first - xy0_.first >= dot->r() * 5 && xy1_.second - xy0_.second >= dot->r() * 5))
    {
        // std::cout << "is leaf and in bounds but over capacity further dividing\n";
        // std::cout << '(' << xy0_.first << "," << xy0_.second << ") ";
        // std::cout << '(' << xy1_.first << "," << xy1_.second << ")\n";

        top_left_ = new QuadNode(xy0_,
                                 std::pair< int, int >
                                 ((xy0_.first + xy1_.first) / 2,
                                  (xy0_.second + xy1_.second) / 2),
                                 this, depth_ + 1, max_depth_);
        top_right_ = new QuadNode(std::pair< int, int >
                                  ((xy0_.first + xy1_.first) / 2,
                                   xy0_.second),
                                  std::pair< int, int >
                                  (xy1_.first, (xy0_.second + xy1_.second) / 2),
                                  this, depth_ + 1, max_depth_);
        bottom_left_ = new QuadNode(std::pair< int, int >
                                    (xy0_.first, (xy0_.second + xy1_.second) / 2),
                                    std::pair< int, int >
                                    ((xy0_.first + xy1_.first)/ 2, xy1_.second),
                                    this, depth_ + 1, max_depth_);
        bottom_right_ = new QuadNode(std::pair< int, int >
                                     ((xy0_.first + xy1_.first) / 2,
                                      (xy0_.second + xy1_.second) / 2),
                                     xy1_, this, depth_ + 1, max_depth_);
            
        for (auto& it : dots_)
        {

            if (top_left_->in_bounds(it))
            {
                // std::cout << "trying Tleft\n";
                // std::cout << '(' << top_left_->xy0_.first << ","
                //           << top_left_->xy0_.second << ") ";
                // std::cout << '(' << top_left_->xy1_.first << ","
                //           << top_left_->xy1_.second << ")\n";
                // std::cout << it->x() << "," << it->y() << std::endl;

                top_left_->insert(it);
            }
  
            else if (top_right_->in_bounds(it))
            {
                // std::cout << "trying Tright\n";
                // std::cout << '(' << top_right_->xy0_.first << ","
                //           << top_right_->xy0_.second << ") ";
                // std::cout << '(' << top_right_->xy1_.first << ","
                //           << top_right_->xy1_.second << ")\n";
                // std::cout << it->x() << "," << it->y() << std::endl;
          
                top_right_->insert(it);
            }
                
            else if (bottom_left_->in_bounds(it))
            {
                // std::cout << "trying Bleft\n";
                // std::cout << '(' << bottom_left_->xy0_.first << ","
                //           << bottom_left_->xy0_.second << ") ";
                // std::cout << '(' << bottom_left_->xy1_.first << ","
                //           << bottom_left_->xy1_.second << ")\n";
                // std::cout << it->x() << "," << it->y() << std::endl;

                bottom_left_->insert(it);
            }
                
            else if (bottom_right_->in_bounds(it))
            {
                // std::cout << "trying Bright\n";
                // std::cout << '(' << bottom_right_->xy0_.first
                //       << "," << bottom_right_->xy0_.second << ") ";
                // std::cout << '(' << bottom_right_->xy1_.first << ","
                //           << bottom_right_->xy1_.second << ")\n";
                // std::cout << it->x() << "," << it->y() << std::endl;

                bottom_right_->insert(it);
            }
        }
        // std::cout << "clearing children\n";
        is_leaf_ = false;
        dots_.clear();
    }
}


// Delete node recursively
void QuadNode::delete_node()
{
    if (is_leaf_ && this != NULL)
    {
        dots_.clear(); // since dot * are being used by vector in main.

        // if dot * are not used in other places, use this.
        // for (int i = 0; i < dots_.size(); ++i)
        // {
        //     delete dots_[i];
        // }
        delete this;
    }
    else
    {
        if (top_left_ != NULL)
        {
            top_left_->delete_node();
        }
        if (top_right_ != NULL)
        {
            top_right_->delete_node();
        }
        if (bottom_left_ != NULL)
        {
            bottom_left_->delete_node();
        }
        if (bottom_right_ != NULL)
        {
            bottom_right_->delete_node();
        }
        delete this;
    }
}


//get all the leaf nodes
void QuadNode::get_leaves(std::vector< QuadNode * > & leaves)
{
    if (is_leaf_)
    {
        leaves.push_back(this);
    }
    else
    {
        top_left_->get_leaves(leaves);
        top_right_->get_leaves(leaves);
        bottom_left_->get_leaves(leaves);
        bottom_right_->get_leaves(leaves);
    }
}



std::ostream & operator<<(std::ostream & cout,
                          const QuadNode p)
{
    cout << "<QuadNode: " << &p
         << "depth: " << p.depth() << "\n"
         << "is leaf: " << p.is_leaf() << "\n"
         << "top left: " << p.top_left() << "\n"
         << "top right: " << p.top_right() << "\n"
         << "bottom left: " << p.bottom_left() << "\n"
         << "bottom right: " << p.bottom_right() << "\n"
         << "start: " << p.xy0().first << "," << p.xy0().second
         << "\nend: " << p.xy1().first << ", " << p.xy1().second
         << "\nnum of children: " << p.dots().size() << "\n"
         << std::endl;
    return cout;
}
