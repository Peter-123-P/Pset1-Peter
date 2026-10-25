#include <cassert>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

/**
 * This struct describes a term in a polynomial with a link to
 * the next term. Note that the head of the polynomial shall be
 * the term with the highest exponent and each term will point
 * to a term with a lower exponent. 
 */
struct Node
{
    int coeff;
    int exp;
    Node* next;

    Node(int c, int e)
    {
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

// Evaluate polynomial given by head for the given x
double eval(Node* head, double x)
{
    // YOUR CODE HERE
    double result = 0;
    while(head != nullptr)
    {
        result += head->coeff * pow(x, head->exp);
        head = head->next;
    }
    return result;
}

// Adds the two polynomials given by head1 and head2 and returns
// the head of the resulting polynomial
Node* addPolynomials(Node* head1, Node* head2)
{
    // YOUR CODE HERE
    Node* head3 = new Node(0,0);
    Node* curr = head3;
    while(head1 != nullptr || head2 != nullptr)
    {
        if(head2 == nullptr || (head1 != nullptr && head1->exp > head2->exp))
        {
            curr->next = new Node(head1->coeff, head1->exp);
            head1 = head1->next;
        }
        else if(head1 == nullptr || head2->exp > head1->exp)
        {
            curr->next = new Node(head2->coeff, head2->exp);
            head2 = head2->next;
        }
        else
        {
            curr->next = new Node(head1->coeff + head2->coeff, head1->exp);
            head1 = head1->next;
            head2 = head2->next;
        }
        curr = curr->next;
    }
    Node* result = head3->next;
    delete head3;
    return result; 
}

int main()
{
    // Example test - write at least 5 unique cases of your own!

    // p1 represents 3x^2 - 5x + 7
    Node* p1 = new Node(3, 2);
    p1->next = new Node(-5, 1);
    p1->next->next = new Node(7, 0);

    // p2 represents 6x - 3
    Node* p2 = new Node(6, 1);
    p2->next = new Node(-3, 0);

    // recall that floating point arithmetic can be finicky! 
    double epsilon = .00001;
    assert(abs(eval(p1, 2.0) - 9.0) < epsilon);

    // p3 should be 3x^2 + x + 4
    Node* p3 = addPolynomials(p1, p2);
    assert(p3->coeff == 3 && p3->exp == 2);
    assert(p3->next->coeff == 1 && p3->next->exp == 1);
    assert(p3->next->next->coeff == 4 && p3->next->next->exp == 0);

    // can we do this better?
    delete p1->next->next;
    delete p1->next;
    delete p1;
    delete p2->next;
    delete p2;
    delete p3->next->next;
    delete p3->next;
    delete p3;

    
    assert(abs(eval(nullptr, 3.0) - 0.0) < epsilon);
    Node* test2 = new Node(7, 0);
    assert(abs(eval(test2, 5.0) - 7.0) < epsilon);
    delete test2;
    Node* test3 = new Node(2, 3);
    assert(abs(eval(test3, -2.0) - (-16.0)) < epsilon);
    delete test3;
    Node* test4 = new Node(4, 2);
    test4->next = new Node(6, 0);
    assert(abs(eval(test4, 0.0) - 6.0) < epsilon);
    delete test4->next;
    delete test4;
    Node* test5 = new Node(2, 2);
    test5->next = new Node(-3, 1);
    test5->next->next = new Node(1, 0);
    assert(abs(eval(test5, 0.5) - 0.0) < epsilon);
    delete test5->next->next;
    delete test5->next;
    delete test5;
    cout<<"Test Completed Success"<<endl;
    cout<<" "<<endl;


    Node* a1 = new Node(3, 2);
    Node* b1 = new Node(5, 2);
    Node* r1 = addPolynomials(a1, b1);
    assert(r1 != nullptr);
    assert(r1->coeff == 8 && r1->exp == 2);
    assert(r1->next == nullptr);
    delete a1;
    delete b1;
    delete r1;
    Node* a2 = new Node(4, 3);
    Node* b2 = new Node(2, 1);
    Node* r2 = addPolynomials(a2, b2);
    assert(r2 != nullptr);
    assert(r2->coeff == 4 && r2->exp == 3);
    assert(r2->next != nullptr);
    assert(r2->next->coeff == 2 && r2->next->exp == 1);
    assert(r2->next->next == nullptr);
    delete a2;
    delete b2;
    delete r2->next;
    delete r2;
    Node* b3 = new Node(6, 1);
    Node* r3 = addPolynomials(nullptr, b3);
    assert(r3 != nullptr);
    assert(r3->coeff == 6 && r3->exp == 1);
    assert(r3->next == nullptr);
    delete b3;
    delete r3;
    Node* a4 = new Node(7, 0);
    Node* r4 = addPolynomials(a4, nullptr);
    assert(r4 != nullptr);
    assert(r4->coeff == 7 && r4->exp == 0);
    assert(r4->next == nullptr);
    delete a4;
    delete r4;
    Node* r5 = addPolynomials(nullptr, nullptr);
    assert(r5 == nullptr);
    cout << "Test successfully passed" << endl;


}

