#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
template <typename T>
class node
{
public:
	node<T>* parent;
	node<T>* left_ch;
	node<T>* right_ch;
	T data;
	bool visit;
};
template <typename T>
class bin_tree_main
{
	friend class bin_tree_exec;
public:
	bin_tree_main()
	{
		root = NULL;
	}
	~bin_tree_main()
	{

	}
	void input_data();
	void create_tree(T);
	void preorder_traverse(node<T>*);
	void inorder_traverse(node<T>*);
	void postorder_traverse(node<T>*);
	void breath_first_search(node<T>*);
	void depth_first_search(node<T>*);
	void delete_node_at(node<T>*, T);
	void cleantag();
	void delete_tree();

	bool find_value(node<T>*);

	node<T>* find_value_DFS_iterative();
	node<T>* binary_search(node<T>*, T);
	node<T>* find_max(node<T>*);
	node<T>* find_min(node<T>*);
	node<T>* find_succeesor(node<T>*, T);
	node<T>* find_predecceesor(node<T>*, T);
private:
	node<T>* root;
	T search_value, add_value, add_after, del_value;
	int nodes_cnt, leaves_cnt;
};

template <typename T>
void bin_tree_main<T>::input_data()
{
	int total;
	cout << "How many nodes?  ";
	cin >> total;
	cout << total << " Nodes' data: ";
	for (int i = 0; i < total; i++)
	{
		T tmp;
		cin >> tmp;
		create_tree(tmp);
	}
}
template <typename T>    //Top-down from root node construction and Time complexity is
void bin_tree_main<T>::create_tree(T in) //Not bin_tree_main:: since it is a template class
{
	node<T>* newnode = new node < T > ;
	newnode->data = in;
	newnode->left_ch = NULL;
	newnode->right_ch = NULL;
	newnode->visit = false;
	if (root == NULL)
	{
		root = newnode;
	}
	else
	{

		node<T>* current = root; //current is used for traverse
		node<T>* prev = NULL; //save prev data before current reach NULL for insertion   current reach NULL and prev before 1 level of current

		//start the top-down from root to build the binary tree ,and traverse to the node before newnode to implement insertion
		while (current != NULL)
		{
			//cout << "Build node " << newnode->data << "After " << current->data << endl;
			prev = current;
			if (in < current->data)
			{
				current = current->left_ch;
			}
			else
			{
				current = current->right_ch;
			}
		}
		//now at the right node's place before the newnode's insertion
		if (in < prev->data)
		{
			prev->left_ch = newnode;
		}
		else
		{
			prev->right_ch = newnode;
		}
		newnode->parent = prev;
	}
}
template <typename T>
void bin_tree_main<T>::preorder_traverse(node<T>* current)
{
	if (current == NULL)
	{
		return ;
	}
	cout << current->data << " ";
	preorder_traverse(current->left_ch);
	preorder_traverse(current->right_ch);
}
template<typename T>
void bin_tree_main<T>::inorder_traverse(node<T>* current)
{
	if (current == NULL)
	{
		return ;
	}
	inorder_traverse(current->left_ch);
	cout << current->data << " ";
	inorder_traverse(current->right_ch);
}
template <typename T>
void bin_tree_main<T>::postorder_traverse(node<T>* current)
{
	if (current == NULL)
	{
		return ;
	}
	postorder_traverse(current->left_ch);
	postorder_traverse(current->right_ch);
	cout << current->data << " ";
}
template <typename T>
void bin_tree_main<T>::breath_first_search(node<T>* current)
{
	queue<node<T>*> bfs_stack;
	bfs_stack.push(current);
	while (bfs_stack.size())
	{
		current = bfs_stack.front();
		bfs_stack.pop();
		cout << current->data << " ";
		if (current->left_ch)
			bfs_stack.push(current->left_ch);
		if (current->right_ch)
			bfs_stack.push(current->right_ch);
	}
}
template <typename T>
bool bin_tree_main<T>::find_value(node<T>* current) //by DFS recursive
{

	if (current != NULL)
	{
		if (current->data == search_value)
			return true;
		else
		{
			if (search_value < current->data)
			{
				find_value(current->left_ch);
			}
			else
			{
				find_value(current->right_ch);
			}

		}
	}
	else
		return false;
}
template <typename T>
node<T>* bin_tree_main<T>::find_value_DFS_iterative()
{
	node<T>* current = root;
	vector<node<T>*> dfs_itr;
	dfs_itr.push_back(root);
	bool find = false;
	while (dfs_itr.size() > 0)
	{
		cout << current->data << " ";
		if (current->data == search_value)
		{
			find = true;
			break;
		}
		if (current->left_ch&&!current->left_ch->visit)
		{
			current = current->left_ch;
			dfs_itr.push_back(current);
		}
		else if (current->right_ch&&!current->right_ch->visit)
		{
			current = current->right_ch;
			dfs_itr.push_back(current);
		}
		else
		{
			current->visit = true;
			current = current->parent;
			dfs_itr.pop_back();
		}
	}
	if (find)
	{
		return current;
	}
	else
	{
		return NULL;
	}

}
template <typename T>
node<T>* bin_tree_main<T>::binary_search(node<T>* current, T value)
{
	while (current != NULL)
	{
		if (value < current->data)
		{
			current = current->left_ch;
		}
		else if (value > current->data)
		{
			current = current->right_ch;
		}
		else
		{
			return current;
		}
	}
	return NULL;

}
template <typename T>
node<T>* bin_tree_main<T>::find_min(node<T>* current)
{
	node<T>* temp_root = current;
	if (current == NULL)
	{
		cout << "Min value in BST: NULL" << endl;
		return NULL;
	}
	else
	{
		while (current->left_ch != NULL) //head to the leftmost node, which is the smallest
		{
			current = current->left_ch;
		}
		cout << "Min value in root "<<temp_root->data <<" BST is " << current->data<<endl;
		return current;
	}
}
template <typename T>
node<T>* bin_tree_main<T>::find_max(node<T>* current)
{
	node<T>* temp_root = current;
	if (current == NULL)
	{
		cout << "Max value in BST: NULL" << endl;
		return NULL;
	}
	else
	{
		while (current->right_ch != NULL) //head to the leftmost node, which is the smallest
		{
			current = current->right_ch;
		} 
		cout << "Max value in root " << temp_root->data << " BST is " << current->data<<endl;
		return current;
	}
}
/*template <typename T>
void bin_tree_main<T>::add_node_after(node<T>* current, T after, T addvalue)
{
	node <T>* newnode = new node < T > ;
	newnode->data = addvalue;
	newnode->left_ch = NULL;
	newnode->right_ch = NULL;
	node <T>* before_add;
	if (after == root->data)
	{
		if (addvalue < root->data)
		{
			root->left_ch = newnode;
			newnode->left_ch = root->left_ch->left_ch;
			newnode->right_ch = root->left_ch->right_ch;
			newnode->parent = root;
			newnode->left_ch->parent = newnode;
			newnode->right_ch->parent = newnode;
		}
		else
		{
			root->right_ch = newnode;
			newnode->left_ch = root->right_ch->left_ch;
			newnode->right_ch = root->right_ch->right_ch;
			newnode->parent = root;
			newnode->left_ch->parent = newnode;
			newnode->right_ch->parent = newnode;
		}
	}
	else
	{
		before_add = binary_search(root, addvalue);
		if (addvalue < before_add->data)
		{
			before_add->left_ch = newnode;
			newnode->left_ch = before_add->left_ch->left_ch;
			newnode->right_ch = before_add->left_ch->right_ch;
			newnode->parent = before_add;
			newnode->left_ch->parent = newnode;
			newnode->right_ch->parent = newnode;
		}
		else
		{
			before_add->right_ch = newnode;
			newnode->left_ch = before_add->right_ch->left_ch;
			newnode->right_ch = before_add->right_ch->right_ch;
			newnode->parent = before_add;
			newnode->left_ch->parent = newnode;
			newnode->right_ch->parent = newnode;
		}
	}
}*/
template <typename T>  //3cases 0chils 1 child and hardest 2 choldren!!!
void bin_tree_main<T>::delete_node_at(node<T>* current, T value) //value of node to be deleted
{
	node<T>* before_delete = NULL; 
	node<T>* deltmp = NULL;
	node<T>* to_be_deleted = NULL;
	if (current == NULL)
	{
		cout << "Root is NULL! Nothing to be deleted !" << endl;
		return;
	}
	before_delete = binary_search(root, value)->parent; //should search the node before deleted or will cause dangling pointer
	to_be_deleted = binary_search(root, value);

	//case 1:  leaf
	if (to_be_deleted->left_ch == NULL&&to_be_deleted->right_ch == NULL)
	{
		if (to_be_deleted == root)
		{
			root = NULL;
		}
		else if (before_delete->left_ch == to_be_deleted)
		{		
			deltmp = before_delete->left_ch;
			before_delete->left_ch = NULL;
			delete deltmp ;

		}
		else if (before_delete->right_ch == to_be_deleted)
		{		
			deltmp = before_delete->right_ch;
			before_delete->right_ch = NULL;
			delete deltmp;
		}
		 //dont forget this, or pointer will crash while traversaling
	}
	//case 2: 1 child node
	else if ((to_be_deleted->left_ch&&to_be_deleted->right_ch == NULL) || (to_be_deleted->left_ch == NULL&&to_be_deleted->right_ch))
	{
		
		cout << "Delete a 1 child node " << to_be_deleted->data << endl;
		if (to_be_deleted == root)
		{
			if (to_be_deleted->right_ch == NULL)
			{
				deltmp = root;
				root = root->left_ch;
				delete deltmp;
			}
			else if (before_delete->left_ch == NULL)
			{
				deltmp = root;
				root = root->right_ch;
				delete deltmp;
			}
		}

		else if (to_be_deleted->right_ch == NULL)
		{
			if (before_delete->left_ch == to_be_deleted)
			{
				deltmp = before_delete->left_ch;
				before_delete->left_ch = to_be_deleted->left_ch;
				delete deltmp;
			}
			else if (before_delete->right_ch == to_be_deleted)
			{
				deltmp = before_delete->right_ch;
				before_delete->right_ch = to_be_deleted->left_ch;
				delete deltmp;
			}
		}

		else if (to_be_deleted->left_ch == NULL)			
		{
			if (before_delete->left_ch == to_be_deleted)
			{
				deltmp = before_delete->left_ch;
				before_delete->left_ch = to_be_deleted->right_ch;
				delete deltmp;
			}
			else if (before_delete->right_ch == to_be_deleted)
			{
				deltmp = before_delete->right_ch;
				before_delete->right_ch = to_be_deleted->right_ch;
				delete deltmp;
			}
		}
		
	}
	//case 3: 2 child node (full node)
	else if (to_be_deleted->left_ch&&to_be_deleted->right_ch) //replace the deleted node with the largest in left subtree or the smallest in right subtree , still obey BST
	{
		node<T>* left_subtree_max=NULL;
		node<T>* before_lsub_max=NULL;
		left_subtree_max = find_max(to_be_deleted->left_ch);
		before_lsub_max = binary_search(root,left_subtree_max->data)->parent;
		cout << "Delete 2 children node :" << to_be_deleted->data << " Replace with lsubtree max node: " << left_subtree_max->data << endl;
		if (to_be_deleted == root)
		{
			root->data = left_subtree_max->data;
			deltmp = before_lsub_max->right_ch;
			before_lsub_max->right_ch = NULL;
			delete deltmp;
		}
		else
		{
			to_be_deleted->data = left_subtree_max->data;
			deltmp=before_lsub_max->right_ch;
			before_lsub_max->right_ch = NULL;
			delete deltmp;
		}
		
	}
}
class bin_tree_exec
{
public:
	bin_tree_exec()
	{
		main_exec();
	}
	void main_exec();
	template <typename T>
	void command_control(bin_tree_main<T>);
private:
	int command, type_selection;
};
template <typename T>
void bin_tree_exec::command_control(bin_tree_main<T> bin_tree)
{
	do
	{
		cout << "\nCommand: 1 build tree ,2 preorder traverse ,3 inorder traverse ,4 postorder traverse\n" <<
			"5 BFS ,6 DFS ,7 find value ,8 find value iterative ,9 binary search ,10 find max ,11 find min\n" <<
			",13 delete node ,14 find predecessor ,15 find succeesor,0  end" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			bin_tree.input_data();
			break;
		case 2:
			bin_tree.preorder_traverse(bin_tree.root);
			break;
		case 3:
			bin_tree.inorder_traverse(bin_tree.root);
			break;
		case 4:
			bin_tree.postorder_traverse(bin_tree.root);
			break;
		case 5:
			bin_tree.breath_first_search(bin_tree.root);
			break;
		case 6:
			bin_tree.inorder_traverse(bin_tree.root);
			break;
		case 7:
			cout << "Search value: ";
			cin >> bin_tree.search_value;
			if (!bin_tree.find_value(bin_tree.root))
			{
				cout << "Vaule doesn't exist in BST! " << endl;
			}
			else
			{
				cout << "Value exists !";
			}
			break;
		case 8:
			cout << "Search value: ";
			cin >> bin_tree.search_value;
			if (bin_tree.find_value_DFS_iterative() == NULL)
			{
				cout << "Vaule doesn't exist in BST! " << endl;
			}
			else if (bin_tree.find_value_DFS_iterative() == bin_tree.root)
			{
				cout << "Value is root " << bin_tree.find_value_DFS_iterative()->data;
			}
			else
			{
				cout << "Value exists after " << bin_tree.find_value_DFS_iterative()->parent->data;
			}
			break;
		case 9:
			cout << "Search value: ";
			cin >> bin_tree.search_value;
			if (bin_tree.binary_search(bin_tree.root, bin_tree.search_value) == NULL)
			{
				cout << "Vaule doesn't exist in BST! " << endl;
			}
			else if (bin_tree.binary_search(bin_tree.root, bin_tree.search_value) == bin_tree.root)
			{
				cout << "Value is root " << bin_tree.binary_search(bin_tree.root, bin_tree.search_value)->data;
			}
			else
			{
				cout << "Value exists after " << bin_tree.binary_search(bin_tree.root, bin_tree.search_value)->parent->data;
			}
			break;
		case 10:
			cout << "Max value in BST " << bin_tree.find_max(bin_tree.root) << endl;
			break;
		case 11:
			cout << "Min value in BST " << bin_tree.find_min(bin_tree.root) << endl;
			break;
		/*case 12:
				cout << "Add value1 after value2 (v1,v2)(obey BST's rule): ";
				cin >> bin_tree.add_value >> bin_tree.add_after;
				bin_tree.add_node_after(bin_tree.root, bin_tree.add_after, bin_tree.add_value);
				break;*/
		case 13:
			cout << "Delete ";
			cin >> bin_tree.del_value;
			bin_tree.delete_node_at(bin_tree.root, bin_tree.del_value);
			break;
		default:
			cout << "Wrong input , try again: " << endl;
		}
	} while (command);
}

void bin_tree_exec::main_exec()
{
	cout << "What type of binary tree ? 0:int ,1:double ,2:string ";
	cin >> type_selection;
	switch (type_selection)
	{
	case 0:
	{
		bin_tree_main<int> bin_tree_int;
		command_control(bin_tree_int);
		break;
	}
	case 1:
	{
		bin_tree_main<double> bin_tree_dou;
		command_control(bin_tree_dou);
		break;
	}
	case 2:
	{
		bin_tree_main<string> bin_tree_str;
		command_control(bin_tree_str);
		break;
	}
	default:
	{
		cout << "Wrong input, please try again.";
		break;
	}
	}

}