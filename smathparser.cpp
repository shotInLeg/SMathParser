#include "smathparser.h"

SMathParser::SMathParser()
{

}


std::vector<unsigned> SMathParser::indexOf(const std::string &str, const std::string &pattern)
{

    std::vector<unsigned> indexes;

    for( unsigned i = 0; i < str.size(); i++ )
    {
        bool ok = false;

        for( unsigned j = 0; j < pattern.size() && i+j < str.size(); j++ )
        {
            if( str[i+j] == pattern[j] )
                ok = true;
            else
            {
                ok = false;
                break;
            }
        }

        if( ok )
            indexes.push_back( i );
    }

    return indexes;
}

std::vector<std::string> SMathParser::split(const std::string &str, const std::string &pattern, bool all )
{
    std::vector<std::string> listTokens;

    int leftI = -1;
    for( int i = 0; i < str.size(); i++ )
    {
        if( str.at(i) != ' ' && str.at(i) != '(' )
            break;

        if( str.at(i) == '(' )
        {
            leftI = i;
            break;
        }
    }

    int rightI = -1;
    for( int i = str.size()-1; i >= 0; i-- )
    {
        if( str.at(i) != ' ' && str.at(i) != ')' )
            break;

        if( str.at(i) == ')' )
        {
            rightI = i;
            break;
        }
    }


    std::string copyStr = str;
    if( leftI != -1 && rightI != -1 )
    {
       copyStr[leftI] = ' ';
       copyStr[rightI] = ' ';
    }


    unsigned strI = 0;
    unsigned patternI = 0;
    std::vector<unsigned> indexes = indexOf( copyStr, pattern );

    while( !copyStr.empty() && patternI < indexes.size() )
    {
        int balance = 0;
        for( unsigned i = strI; i < indexes[patternI]; i++ )
        {
            if( copyStr.at(i) == '(' )
                balance++;
            if( copyStr.at(i) == ')' )
                balance--;

            if( balance < 0 )
                return std::vector<std::string>();
        }

        if( balance == 0 )
        {
            std::string splitTerm = "";
            for( unsigned i = strI; i < copyStr.size() && i < indexes[patternI]; i++ )
            {
                splitTerm += copyStr.at(i);
            }

            if( !splitTerm.empty() )
                listTokens.push_back( splitTerm );


            strI = indexes[patternI]+1;
            patternI++;
        }
        else
        {
            patternI++;
        }
    }

    return listTokens;
}


bool SMathParser::isNumber(const std::string &str)
{
    bool point = false;

    char alph[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for( int i = 0; i < str.size(); i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            if( str.at(i) != alph[i] || ( str.at(i) != '.' || ( str.at(i) == '.' && !point) ) )
                return false;
        }

        if( i != 0 && i != str.size()-1 && str.at(i) == '.' )
            point = true;
    }

    return true;
}



Tree SMathParser::parse( Tree::Node * curr )
{
    std::vector<std::string> tokens = split( curr->value, " " );

    bool finded = false;

    for( int i = tokens.size()-1; i >= 0 && !finded; i-- )
    {
        if( tokens.at(i) == "+" || tokens.at(i) == "-" )
        {
            std::string left = "";
            for( int j = 0; j < i; j++ )
                left += tokens.at(j) + " ";

            std::string root = tokens.at(i);

            std::string right = "";
            for( int j = i+1; j < tokens.size(); j++ )
                right += tokens.at(j) + " ";


            curr->value = root;
            curr->left = new Tree::Node( left );
            curr->right = new Tree::Node( right );

            parse( curr->left );
            parse( curr->right );


            finded = true;
        }
    }

    for( int i = tokens.size()-1; i >= 0 && !finded; i-- )
    {
        if( tokens.at(i) == "*" || tokens.at(i) == "/" )
        {
            std::string left = "";
            for( int j = 0; j < i; j++ )
                left += tokens.at(j) + " ";

            std::string root = tokens.at(i);

            std::string right = "";
            for( int j = i+1; j < tokens.size(); j++ )
                right += tokens.at(j) + " ";


            curr->value = root;
            curr->left = new Tree::Node( left );
            curr->right = new Tree::Node( right );

            parse( curr->left );
            parse( curr->right );


            finded = true;
        }
    }

    for( int i = tokens.size()-1; i >= 0 && !finded; i-- )
    {
        if( tokens.at(i) == "^" )
        {
            std::string left = "";
            for( int j = 0; j < i; j++ )
                left += tokens.at(j) + " ";

            std::string root = tokens.at(i);

            std::string right = "";
            for( int j = i+1; j < tokens.size(); j++ )
                right += tokens.at(j) + " ";


            curr->value = root;
            curr->left = new Tree::Node( left );
            curr->right = new Tree::Node( right );

            parse( curr->left );
            parse( curr->right );


            finded = true;
        }
    }
}

double SMathParser::build( Tree::Node *node )
{
    double left = 0;
    double right = 0;

    if( node->left == NULL )
        return strtod(node->value.c_str(), NULL);
    else
        left = build( node->left );

    if( node->right == NULL )
        return strtod(node->value.c_str(), NULL);
    else
        right = build( node->right );

    if( node->value == "*" )
        return left * right;
    else if( node->value == "/" )
        return left / right;
    else if( node->value == "+" )
        return left + right;
    else if( node->value == "-" )
        return left - right;
}
