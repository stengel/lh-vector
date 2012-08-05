#include "equilibrium.h"
#include "list.h"

/* Creates a new node */
node* newnode(int n)
{
	node* nd;
	nd = malloc(sizeof(node));
	nd->link = malloc(n * sizeof(int));
	int i;
	for(i = 0; i < n; ++i)
	{
		nd->link[i] = -1;
	}
	nd->next = NULL;
	
	return nd;
}

/* Adds a new node with the given equilibrium to the list
 * and returns its index position */
int addNode(node* list, Equilibrium eq)
{
	int i = 0;
	node* cur = list;
	
	while(cur->next != NULL)
	{
		cur = cur->next;
		++i;
	}
	
	node* n = newnode(eq.lcpdim-2);
	n->eq = eq;
	cur->next = n;
	++i;
	
	return i;
}

/*Finds and returns the location of an equilibrium in the list 
 Returns -1 if the equilibrium is not in the list*/
int contains(node* list, Equilibrium eq)
{
	int result = -1;
	int i = 0;
	node* cur = list;
	
	while(cur != NULL)
	{
		if(equilibriumisEqual(cur->eq, eq))
		{
			result = i;
			break;
		}
		cur = cur->next;
		++i;
	}
	
	return result;
}

/* Adds the equilibrium to the list, and returns its index position
 * in the list. If the equilibrium already exists, it returns the 
 * index where it is stoeed, and doesn't add it. */
int addEquilibrium(node* list, Equilibrium eq)
{
	int result = contains(list, eq);
	if(result == -1)
	{
		result = addNode(list, eq);
	}
	return result;
}

/* Get node at index */
int listlength(node* list)
{
	if(list == NULL)
		return 0;
		
	int i = 1;
	
	node* next = list;
	while(next->next != NULL)
	{
		++i;
		next = next->next;
	}
	
	return i;
}

/* Computes the number of elements in the list */
node* getNodeat(node* list, int n)
{
	if(n >= listlength(list))
		return NULL;
	
	int i = 0;
	
	node* cur = list;
	for(i = 0; i < n; ++i)
	{
		cur = cur->next;
	}
	
	return cur;
}

/* Prints all the elements in the list */
void printlist(node* list)
{
	node* cur = list;
	int i = 0;
	while(cur != NULL)
	{
		printf("\nEq[%d]: ", i++);
		printEquilibrium(cur->eq);
		int k;
		printf("Leads to: ");
		for(k = 0; k < cur->eq.lcpdim - 2; ++k)
			printf("%d->%d ", k+1, cur->link[k]);
		printf("\n");
		cur = cur->next;
	}
}