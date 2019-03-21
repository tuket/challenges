Class Node
{
    Node *left, *right;
};

Node* findSecondLargest(Node* root)
{
    // go all down though the right
    Node* parentLargestNode = nullptr;
    Node* largestNode = root;
    while(largestNode->right) {
parentLargestNode = largestNode;
largestNode = largestNode->right;
}
    Return parentLastNode;
}


