#ifndef QUADNODE_H
#define QUADNODE_H
#include "Dot.h"
#include <vector>

class QuadNode
{
  public:
    QuadNode(std::pair< int, int > xy0,
             std::pair< int, int > xy1,
             QuadNode * parent, int depth, int max_depth);
    ~QuadNode();

    std::pair< int, int > xy0() const;
    std::pair< int, int > xy1() const;
    int depth() const;
    bool is_leaf() const;
    QuadNode * parent() const;
    QuadNode * top_left() const;
    QuadNode * top_right() const;
    QuadNode * bottom_left() const;
    QuadNode * bottom_right() const;
    std::vector< Dot * > dots() const;

    bool in_bounds(const Dot * dot);
    void insert(Dot * dot);
    void delete_node();
    void get_leaves(std::vector< QuadNode * > & leaves);
    
  private:
    std::pair< int, int > xy0_;
    std::pair< int, int > xy1_;
    bool is_leaf_;
    int depth_;
    int max_depth_;
    int capacity_;
    std::vector< Dot* > dots_;
    QuadNode * parent_;
    QuadNode * top_left_;
    QuadNode * top_right_;
    QuadNode * bottom_left_;
    QuadNode * bottom_right_;
};

std::ostream & operator<<(std::ostream & cout,
                          const QuadNode p);

#endif
