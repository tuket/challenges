Class Node
{
    Bool locked;
    Int countLock;    // number of locked descendants
    Node* parent;
Public:
    Bool isLocked()const { return locked; }
    Bool canLock()const
    {
        if(locked || countLock != 0)
            Return false;
        for(Node* node = parent; node; node = node->parent)
        {
            if(node->locked)
                Return false;
        }
        Return true;
    }
    Bool lock()
    {
        if(!canLock())
            return false;
        Locked = true;
        for(Node* node = parent; node; node = node->parent)
            node->countLock++;    
        Return true;    
    }
    Bool unlock()
    {
        if(!locked)
            Return false;
        Locked = false;
        for(Node* node = parent; node; node = node->parent)
            node->countLock--;
        Return true;
    }
};
