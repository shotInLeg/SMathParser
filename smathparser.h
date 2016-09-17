#ifndef SMATHPARSER_H
#define SMATHPARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>

class Tree
{
public:
    struct Node
    {
    public:
        std::string value;

        Node * left;
        Node * right;

        Node():value(""),left(NULL),right(NULL){}
        Node( const std::string& str ):value(str),left(NULL),right(NULL){}
    };

    Tree()
    {
        root = new Node();
    }

public:
    Node * root;
};

class SMathParser
{
public:
    SMathParser();

    Tree parse( Tree::Node *curr );

    void print( Tree::Node * node, int n = 0 )
    {

        if( node->left != NULL )
            std::cout << " { " << node->left->value << " } ";

        if( node != NULL )
            std::cout << " [ " << node->value << " ] ";

        if( node->right != NULL )
            std::cout << " { " << node->right->value << " } ";

        std::cout << std::endl;

        if( node->left != NULL )
        {
            for( int i = 0; i < n+5; i++ )
                std::cout << " ";

            std::cout << "left:";

            print( node->left, n+5 );
        }

        if( node->right != NULL )
        {
            for( int i = 0; i < n+5; i++ )
                std::cout << " ";

            std::cout << "right:";

            print( node->right, n+5  );
        }
    }

    double run( const std::string& str )
    {
        tree.root->value = str;
        parse( tree.root );

        print( tree.root );

        double result = build( tree.root );

        std::cout << std::endl;

        return result;
    }

    double build( Tree::Node * node );

private:
    std::vector<std::string> split(const std::string& str, const std::string& pattern , bool all = true);

    std::vector<unsigned> indexOf( const std::string& str, const std::string& pattern );

    bool isVar( const std::string& str );
    bool isNumber( const std::string& str );
    bool isOperation( const std::string& str );

private:
    Tree tree;
};

#endif // SMATHPARSER_H
