#include <iostream>
#include<string>
#include <vector>
#include <stack>
using namespace std;

struct AVL
{
    AVL* left;
    AVL* right;
    string NAME;
    int ID;

    AVL()
    {
        left = nullptr;
        right = nullptr;
        NAME = " ";
        ID = 0;
    }

    AVL(string name, int id)
    {
        left = nullptr;
        right = nullptr;
        NAME = std::move(name);
        ID = id;
    }
};

class Student
{
    public:

    Student();

    int height(AVL* root);

    int balanceFactor(AVL* root);

    static AVL *rotateRight(AVL* root);

    static AVL *rotateLeft(AVL* root);

    AVL* insert(AVL* root, AVL* newNode);

    static AVL* smallestNode(AVL* root);

    AVL* remove(AVL* root, int target);

    void removeInorder(AVL* root, int n);

    AVL* search(AVL* root, int target);

    AVL* search(AVL* root, const string &target);

    void printInorder(AVL* root);

    void printPreorder(AVL* root);

    void printPostorder(AVL* root);

    void printLevelCount(AVL* root);

    AVL* root;

    bool isValid = false;
};

bool isNameValid(const string &data);

bool isIdValid(const string &data);

Student::Student()
{
    root = nullptr;
}

int Student::height(AVL* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight)           // The height of the AVL tree is found from the tallest subtree
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

int Student::balanceFactor(AVL *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return leftHeight - rightHeight;         // Left Subtree Height - Right Subtree Height = Balance Factor
}

AVL* Student::rotateRight(AVL* root)         // Right Rotation
{
    if (root == nullptr || root->left == nullptr)
    {
        return root;
    }
    AVL* child = root->left;
    root->left = child->right;
    child->right = root;
    return child;
}

AVL* Student::rotateLeft(AVL* root)         // Left Rotation
{
    if (root == nullptr || root->right == nullptr)
    {
        return root;
    }
    AVL* child = root->right;
    root->right =  child->left;
    child->left = root;
    return child;
}

AVL* Student::insert(AVL* root, AVL* newNode)
{
    if (root == nullptr) 
    {
        root = newNode;
        cout << "successful" << endl;
        return root;
    } 
    else 
    {
        if (newNode->ID < root->ID)
        {
            root->left = insert(root->left, newNode);
        } 
        else if (newNode->ID > root->ID) 
        {
            root->right = insert(root->right, newNode);
        } 
        else 
        {
            cout << "unsuccessful" << endl;
            return root;
        }
    }

    int factor = balanceFactor(root);
    if (factor > 1 && newNode->ID < root->left->ID)
    {
        return rotateRight(root);
    }
    if (factor < -1 && newNode->ID > root->right->ID)
    {
        return rotateLeft(root);
    }
    if (factor > 1 && newNode->ID > root->left->ID)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (factor < -1 && newNode->ID < root->right->ID)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

AVL* Student::smallestNode(AVL* root)    // As the name might give away, finds the smallest Node in the AVL tree
{
    if (root == nullptr)
    {
        return nullptr;
    }
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

AVL *Student::remove(AVL *root, int target)  // Removes a targeted node from the AVL tree
{
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    else if (target < root->ID)
    {
        root->left = remove(root->left, target);
    }
    else if (target > root->ID)
    {
        root->right = remove(root->right, target);
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        root = nullptr;
        cout << "successful" << endl;
        return root;
    }
    else if (root->left == nullptr)
    {
        AVL *temp = root;
        root = root->right;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    else if (root->right == nullptr)
    {
        AVL *temp = root;
        root = root->left;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    else
    {
        AVL *temp = smallestNode(root->right);
        root->ID = temp->ID;
        root->NAME = temp->NAME;
        root->right = temp->right;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    return root;
}

void Student::removeInorder(AVL *root, int n) // Removes the node with the nth smallest value
{
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return;
    }

    int count = 0;
    AVL* current = root;
    stack<AVL *> s;
    while (current != nullptr || !s.empty())
    {
        while (current != nullptr)
        {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();

        if (++count == n + 1)
        {
            remove(root, current->ID);
            return;
        }

        current = current->right;
    }

    cout << "unsuccessful" << endl;
}

AVL* Student::search(AVL* root, int target)    // search ID
{
    if (root == nullptr) 
    {
        return root;
    } 
    else if (root->ID == target)
    {
        cout << root->NAME << endl;
        isValid = true;
        return root;
    }
    else if (target < root->ID)
        return search(root->left, target);
    else
        return search(root->right, target);
}

AVL* Student::search(AVL* root, const string &target)   //search NAME
{
    if (root == nullptr) 
    {
        return root;
    } 
    else if (root->NAME == target) 
    {
        cout << root->ID << endl;
        isValid = true;
    }
    search(root->left, target);
    search(root->right, target);
    return root;
}

void Student::printInorder(AVL* root)
{
    if (root == nullptr)
    {
        return;
    }
    printInorder(root->left);
    if (root->left != nullptr)
    {
        cout << ", ";
    }
    cout << root->NAME;
    if (root->right != nullptr)
    {
        cout << ", ";
    }
    printInorder(root->right);
}

void Student::printPreorder(AVL* root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->NAME;
    if (root->left != nullptr)
    {
        cout << ", ";
        printPreorder(root->left);
    }
    if (root->right != nullptr)
    {
        cout << ", ";
        printPreorder(root->right);
    }
}

void Student::printPostorder(AVL* root)
{
    if (root != nullptr)
    {
        printPostorder(root->left);
        if (root->right)
        {
            cout << ", ";
        }
        printPostorder(root->right);
        if (root->left)
        {
            cout << ", ";
        }
        cout << root->NAME;
    }
}

void Student::printLevelCount(AVL* root)
{
    cout << height(root) << endl;
}


bool isNameValid(const string &data)
{
    for (char i : data)
    {
        if (!isalpha(i))
        {
            if (i == ' ')
            {
                continue;
            }
            return false;
        }
    }
    return true;
}


bool isIdValid(const string &data)
{
    int count = 0;
    for (char i : data)
    {
        if (!isdigit(i))
        {
            if (i == ' ')
            {
                continue;
            }
            return false;
        }
        count++;
    }
    return (count == 8);
}

int main()
{
    Student student;
    string studentName;
    string studentInfo;
    string idNumber;
    string command;
    int commandTotal;
    cin >> commandTotal;

    for (int i = 0; i < commandTotal; i++)
    {
        cin >> command;

        auto *newNode = new AVL();

        if (command == "insert")
        {

            getline(cin, studentInfo);
			cout << studentInfo << endl;
            int firstQuote = studentInfo.find_first_of('"');
            int lastQuote = studentInfo.find_last_of('"');
            studentName = studentInfo.substr(firstQuote + 1, lastQuote - 2);
            idNumber = studentInfo.substr(lastQuote + 1, studentInfo.length() - 1);

            if (!isIdValid(idNumber)|| studentName.empty())
            {
                cout << "unsuccessful" << endl;
                continue;
            }

            if (!isNameValid(studentName))
            {
                cout << "unsuccessful" << endl;
                continue;
            }

            newNode->NAME = studentName;
            newNode->ID = stoi(idNumber);
            student.root = student.insert(student.root, newNode);

        }
        else if (command == "remove")
        {
            string target;
            getline(cin, target);

              if (!isIdValid(target))
              {
                cout << "unsuccessful" << endl;
                continue;
            }
            student.root = student.remove(student.root, stoi(target));

        }
        else if (command == "search")
        {
            string target;
            getline(cin, target);
            int firstQuote = target.find_first_of('"');
            int lastQuote = target.find_last_of('"');
            if (firstQuote > -1)
            {
                student.search(student.root, target.substr(firstQuote + 1, lastQuote - 2));
            }
            else
            {
                 if (!isIdValid(target))
                 {
                cout << "unsuccessful" << endl;
                continue;
            }
                student.search(student.root, stoi(target));
            }
            if (!student.isValid)
                cout << "unsuccessful" << endl;
            student.isValid = false;

        }
        else if (command == "printPreorder")
        {
            student.printPreorder(student.root);
            cout << endl;

        }
        else if (command == "printInorder")
        {
            student.printInorder(student.root);
            cout << endl;

        }
        else if (command == "printPostorder")
        {
            student.printPostorder(student.root);
            cout << endl;

        }
        else if (command == "printLevelCount")
        {
            student.printLevelCount(student.root);
        }
        else if (command == "removeInorder")
        {
            int input;
            cin >> input;
            student.removeInorder(student.root, input);
        }
    }
    return 0;
}


