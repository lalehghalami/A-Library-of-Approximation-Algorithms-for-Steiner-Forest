#include "TM-Functions.h"
#include "SF-Functions.h"

using namespace std;

Tree::Tree()
{
    root=0;
}

void Tree::insert(TreeNodes *p, int index, vector<int> set,int Lv)
{
    if (p->firstChild==0) {
        p->firstChild=new TreeNodes(index,set,p,Lv);
    }
    else
    {
        TreeNodes * p_Hold=p;
        p=p->firstChild;
        while (p->nextSibling !=0 ) {
            p=p->nextSibling;
        }
        p->nextSibling=new TreeNodes(index,set,p_Hold,Lv);
    }
}

void Tree::insertRoot(int index, vector<int> set, int Lv)
{
    root=new TreeNodes(index,set,0,Lv);
}

void Tree::buildTreeMetric(int nVertex,vector<vector<int> > pathMatrix,vector<int> vertexListPer,vector <float> rVector )
{
    //BFS
    queue <TreeNodes*> level_queue;
    level_queue.push(root);
    int nodeCounts=(root->nodeIndex)+1;
    
    while (!level_queue.empty())
    {
        TreeNodes* node=level_queue.front();
        level_queue.pop();
        
        vector<int> S=node->nodeSet;
        if (S.size()==1)
            continue;
        for (int j=0; j<nVertex; j++)
        {
            vector<int> B;                 // Creating Ball
            for (int r=0; r<nVertex; r++)
            {
                if (pathMatrix[vertexListPer[j]][r]<rVector[(node->level)-1])
                    B.push_back(r);
            }
            
            vector<int> intersecVector; // Intersection B(π(j), ri−1) ∩ S
            intersecVector=intersection(B, S);
            
            if (intersecVector.size()!=0)
            {
                for (int r=0; r<intersecVector.size(); r++)     // Remove B(π(j), ri−1) ∩ S from S
                    S.erase(remove(S.begin(), S.end(), intersecVector[r]), S.end());
    
                insert(node,nodeCounts,intersecVector,node->level-1);
                nodeCounts++;
            }
        }
        
        if(node->firstChild!=0) level_queue.push(node->firstChild);
        
        TreeNodes* tempPtr=node->firstChild->nextSibling;
        while (tempPtr!=0)
        {
            level_queue.push(tempPtr);
            tempPtr=tempPtr->nextSibling;
        }
    }
    
}

void Tree::showTree()
{
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Show Tree Details:\n";
    queue <TreeNodes*> level_queue;
    level_queue.push(root);
    
    while (!level_queue.empty())
    {
        TreeNodes* p=level_queue.front();
        level_queue.pop();
        cout<<"++++++++++++++++++++++++++++++++++++++++++\n";
        cout<<"Node "<<p->nodeIndex<<" : {";
        for (int i=0; i<p->nodeSet.size(); i++) {
            cout<< p->nodeSet[i]<<",";
        }
        cout<<"}\n";
        
        if(p->parent!=0)cout<<"parent: "<<p->parent->nodeIndex;
        if(p->nextSibling!=0)cout<<" nextSibling: "<<p->nextSibling->nodeIndex;
        if(p->firstChild!=0)cout<<" firstChild: "<<p->firstChild->nodeIndex;
        
        cout<<endl;
        
        if(p->firstChild!=0)
        {
            level_queue.push(p->firstChild);
            
            TreeNodes* tempPtr=p->firstChild->nextSibling;
            while (tempPtr!=0)
            {
                level_queue.push(tempPtr);
                tempPtr=tempPtr->nextSibling;
            }
        }
    }
    cout<<"---------------------------------------------------------------"<<endl;
}

void Tree::shrinkTree() // this is working perfectly but doesn`t update parent(which we are not using in the alg at all)
{
    queue <TreeNodes*> parent_queue;
    parent_queue.push(root);
    
    while (!parent_queue.empty())
    {
        TreeNodes* p=parent_queue.front();
        parent_queue.pop();
        if(p->nodeSet.size()>1) // if parent is qualified
        {
            TreeNodes* child=p->firstChild; // for sure parent has at least a child
            if (child->nodeSet.size()==1)   // the first child is qualified to Merge
            {
                if (child->firstChild==0)   // FirstChild doesn`t have any children
                {
                    p->firstChild=child->nextSibling;
                    p->nodeSet=child->nodeSet;
                    child=NULL;
                    delete child;
                    TreeNodes* temp=p->firstChild;
                    while (temp!=0)
                    {
                        parent_queue.push(temp);
                        temp=temp->nextSibling;
                    }
                }else // the firstchild has childern
                {
                    p->firstChild=child->firstChild;
                    TreeNodes* child2=child->firstChild;

                    while (child2!=0) {
                        child2->parent=p;
                        child2=child2->nextSibling;
                    }
                    TreeNodes* temp0;
                    for (temp0=child->firstChild;temp0->nextSibling!=0; temp0=temp0->nextSibling);
                    temp0->nextSibling=child->nextSibling;
                    p->nodeSet=child->nodeSet;
                    child=NULL;

                    delete child;
                    TreeNodes* temp=p->firstChild;
                    while (temp!=0)
                    {
                        parent_queue.push(temp);
                        temp=temp->nextSibling;
                    }
                }
            }else // the first child is not qualified to merge
            {
                if (child->nextSibling!=0)
                {
                    TreeNodes* child2=p->firstChild;
                    child=child->nextSibling;
                    while (child->nextSibling!=0 && child->nodeSet.size()>1) {
                        child=child->nextSibling;
                        child2=child2->nextSibling;
                    }
                    if (child->nodeSet.size()==1)
                    {
                        if (child->firstChild==0)
                        {
                            child2->nextSibling=child->nextSibling;
                            p->nodeSet=child->nodeSet;
                            child=NULL;

                            delete child;
                            TreeNodes* temp=p->firstChild;
                            while (temp!=0)
                            {
                                parent_queue.push(temp);
                                temp=temp->nextSibling;
                            }
                        }else
                        {
                            child2->nextSibling=child->firstChild;
                            TreeNodes* child3=child->firstChild;
                            
                            while (child3!=0) {
                                child3->parent=p;
                                child3=child3->nextSibling;
                            }
                            TreeNodes* temp0;
                            for (temp0=child->firstChild;temp0->nextSibling!=0; temp0=temp0->nextSibling);
                            
                            temp0->nextSibling=child->nextSibling;
                            p->nodeSet=child->nodeSet;
                            child=NULL;

                            delete child;
                            TreeNodes* temp=p->firstChild;
                            while (temp!=0)
                            {
                                parent_queue.push(temp);
                                temp=temp->nextSibling;
                            }
                        }
                    }else
                    {
                        TreeNodes* temp=p->firstChild;
                        while (temp!=0)
                        {
                            parent_queue.push(temp);
                            temp=temp->nextSibling;
                        }
                        parent_queue.push(p);
                    }
                    
                }else
                {
                    parent_queue.push(child);
                    parent_queue.push(p);
                }
            }
        }
    }
}

int Tree::findPathCost(vector<int> s, vector<int> t,vector<vector<int> > pathMatrix, int terminalPairIndex, set<pair<int,int>,CustomComparitor> & pathSet)
{
    int pathCost=0;
    bool foundSource=0;
    queue <TreeNodes*> pathQueue;
    pathQueue.push(root);
    
    // Find source and destination ptrs
    TreeNodes* sourcePtr=0;
    TreeNodes* destinationPtr=0;
    while (!pathQueue.empty())
    {
        TreeNodes* p=pathQueue.front();
        pathQueue.pop();
        if ((p->nodeSet==s || p->nodeSet==t) && !foundSource)
        {
            sourcePtr=p;
            foundSource=true;
        }
        else if ((p->nodeSet==s || p->nodeSet==t) && foundSource)
            destinationPtr=p;
        
        if(p->firstChild!=0)
        {
            pathQueue.push(p->firstChild);
            TreeNodes* tempPtr=p->firstChild->nextSibling;
            while (tempPtr!=0)
            {
                pathQueue.push(tempPtr);
                tempPtr=tempPtr->nextSibling;
            }
        }
    }
    
    vector<vector<int>> path;
    // Mark nodes from destination to LCA
    TreeNodes* temp1=destinationPtr;
    while (temp1!=0) {
        temp1->terminalPair=terminalPairIndex;
        temp1=temp1->parent;
    }
    TreeNodes* LCA=0;
    TreeNodes* temp2=0;
    temp2=sourcePtr;
    //    path.push_back(sourcePtr->nodeSet);
    
    while (temp2!=0)
    {
        path.push_back(temp2->nodeSet);
        if(temp2->terminalPair==terminalPairIndex)
        {
            LCA=temp2;
            break;
        }
        temp2=temp2->parent;
    }
    
    TreeNodes* temp3=destinationPtr;
    stack<int> tempStack;
    while (temp3!=LCA) {
        tempStack.push(temp3->nodeSet[0]);
        temp3=temp3->parent;
    }
    
    while (!tempStack.empty()) {
        vector<int> tempV;
        tempV.push_back(tempStack.top());
        tempStack.pop();
        path.push_back(tempV);
    }
    
    for (int i=0; i<path.size()-1; i++) {
        pair <int,int> edgePair;
        edgePair=pair<int,int>(path[i][0],path[i+1][0]);
        pathSet.insert(edgePair);
        pathCost+=pathMatrix[path[i][0]][path[i+1][0]];
    }
    return pathCost;
}
