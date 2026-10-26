#include <string>
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class BrowserHistory 
{

private:
    /**
     * Create a struct Node containing a url and pointers to the next
     * and previous Nodes. 
     * 
     * Create instance variables for any Nodes that we need to keep
     * track of
     */
     // YOUR CODE HERE
    struct Node
    {
        string url;
        Node* forward;
        Node* backward;

        Node(string u)
        {
            url = u;
            forward = nullptr;
            backward = nullptr;
        }
    };
    Node* curr;

public:
    
    /**
     * Constructor
     * 
     * Initialize instance variables with homepage
     */
    BrowserHistory(string homepage) 
    {
        // YOUR CODE HERE
        curr = new Node(homepage);
    }

    /**
     * Destructor
     * 
     * Called when deleting object - should free up any remaining
     * dynamically allocated memory referenced by the object
     */
    ~BrowserHistory()
    {
        // YOUR CODE HERE
        while(curr != nullptr && curr->backward != nullptr)
        {
            curr = curr->backward;
        }
        while(curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->forward;
            delete temp;
        }
    }
    
    /**
     * Goes to url from the current page and clears all forward history
     */
    void visit(string url) 
    {
        // YOUR CODE HERE
        Node* temp = curr->forward;
        while(temp != nullptr)
        {
            Node* nextPage = temp->forward;
            delete temp;
            temp = nextPage;
        }
        Node* newPage = new Node(url);
        curr->forward = newPage;
        newPage->backward = curr;
        curr = newPage;
    }
    
    
    /** 
     * Move steps back in history. If you can only move back x steps 
     * in the history and steps > x, you will move back only x steps. 
     * Return the current url after moving back in history at most 
     * steps times.
     */ 
    string back(int steps) 
    {
        // YOUR CODE HERE
        for(int i = 0; i<steps; i++)
        {
            if(curr->backward == nullptr)
            {
                break;
            }
            curr = curr->backward;
        }
        return curr->url;
    }

    /** 
    * Move steps forward in history. If you can only forward x steps in
    * the history and steps > x, you will forward only x steps. Return
    * the current url after forwarding in history at most steps.
    */ 
    string forward(int steps) 
    {
        // YOUR CODE HERE
        for(int i = 0; i<steps; i++)
        {
            if(curr->forward == nullptr)
            {
                break;
            }
            curr = curr->forward;
        }
        return curr->url;
    }
};

int main()
{
    // Example test - write at least 5 unique cases of your own!
    BrowserHistory* bh = new BrowserHistory("google.com"); // start at google
    bh->visit("amazon.com"); // go to amazon (google 1 back in history)
    bh->visit("wikipedia.com"); // go to wikipedia (google 2 back in history)
    bh->visit("cppreference.com"); // go to cppreference (google 3 back in history)
    assert(bh->back(2) == "amazon.com"); // go back 2, should be at amazon
    assert(bh->forward(1) == "wikipedia.com"); // go forward 1, should be at wikipedia
    
    assert(bh->back(100) == "google.com");
    assert(bh->forward(100) == "cppreference.com");
    assert(bh->back(0) == "cppreference.com");
    assert(bh->forward(0) == "cppreference.com");
    BrowserHistory* bh2 = new BrowserHistory("school.com");
    assert(bh2->back(1) == "school.com");
    assert(bh2->forward(1) == "school.com");
    assert(bh->back(2) == "amazon.com");
    bh->visit("youtube.com");
    assert(bh->forward(1) == "youtube.com");
    assert(bh->back(1) == "amazon.com");
    delete bh2;
    delete bh;
    cout<<"All test successfully comnpleted";
}
