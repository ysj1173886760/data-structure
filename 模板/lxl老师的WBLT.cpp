#include <iostream>
#include <stdio.h>
#define ratio 4
#define new_Node( s , v , a , b ) ( & ( * st[ cnt++ ] = Node( s , v , a , b ) ) )
#define update( cur ) if( cur -> left -> size ) cur -> size = cur -> left -> size + cur -> right -> size , cur -> value = cur -> right -> value
#define merge( a , b ) new_Node( a -> size + b -> size , b -> value , a , b )

using namespace std;

int n , cnt , s , a;

inline int read()
{
    register int x = 0 , v = 1 , ch = getchar();
    while( !isdigit( ch ) )
    {
        if( ch == '-' ) v = -1;
        ch = getchar();
    }
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
    return x * v;
}

struct Node
{
	int size , value;
	Node * left , * right;
	Node( int s , int v , Node * a , Node * b ) : size( s ) , value( v ) , left( a ) , right( b ) {}
	Node() {}
} * root , * null , * st[300000] , t[300000] , * father;

inline void maintain( Node * cur )
{
	if( cur -> left -> size > cur -> right -> size * ratio ) cur -> right = merge( cur -> left -> right , cur -> right ) , st[ --cnt ] = cur -> left , cur -> left = cur -> left -> left;
	if( cur -> right -> size > cur -> left -> size * ratio ) cur -> left = merge( cur -> left , cur -> right -> left ) , st[ --cnt ] = cur -> right , cur -> right = cur -> right -> right;
}

int find( int x , Node * cur )
{
	if( cur -> size == 1 ) return cur -> value;
	return x > cur -> left -> size ? find( x - cur -> left -> size , cur -> right ) : find( x , cur -> left );
}

int rank( int x , Node * cur )
{
	if( cur -> size == 1 ) return 1;
	return x > cur -> left -> value ? rank( x , cur -> right ) + cur -> left -> size : rank( x , cur -> left );
}

void insert( int x , Node * cur )
{
	if( cur -> size == 1 ) cur -> left = new_Node( 1 , min( cur -> value , x ) , null , null ) , cur -> right = new_Node( 1 , max( cur -> value , x ) , null , null );
	else insert( x , x > cur -> left -> value ? cur -> right : cur -> left );
	update( cur ) , maintain( cur );
}

void erase( int x , Node * cur )
{
	if( cur -> size == 1 ) * father = cur == father -> left ? * father -> right : * father -> left;
	else father = cur , erase( x , x > cur -> left -> value ? cur -> right : cur -> left );
	update( cur ) , maintain( cur );
}

int main()
{
    n = read();
    for( register int i = 0 ; i < 300000 ; i++ ) st[i] = & t[i];
    null = new Node( 0 , 0 , 0 , 0 );
    root = new Node( 1 , 2147483647 , null , null );
    while( n-- )
    {
        s = read() , a = read();
        if( s == 1 ) insert( a , root );
        else if( s == 2 ) erase( a , root );
        else if( s == 3 ) printf( "%d\n" , rank( a , root ) );
        else if( s == 4 ) printf( "%d\n" , find( a , root ) );
        else if( s == 5 ) printf( "%d\n" , find( rank( a , root ) - 1 , root ) );
        else printf( "%d\n" , find( rank( a + 1 , root ) , root ) );
    }
    return 0;
}
