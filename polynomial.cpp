#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only

//helper
int power(int base, int exp){
    int result = 1;
    while (exp != 0) {
        result *= base;
        --exp;
    }
    return result;
}

Polynomial::Polynomial(){
    head = nullptr;
}

Polynomial::Polynomial(const Polynomial& another){
    if(another.head == nullptr){
        this->head = nullptr;
        return;
    }  
    Term* tmp = another.head;
    head = new Term;
    head->coefficient = tmp->coefficient;
    head-> exponent = tmp-> exponent;
    head->next = nullptr;
    
    Term* current = head;
    tmp = tmp->next;
    while(tmp != nullptr){
        current->next = new Term;
        current = current->next;
        current->coefficient = tmp->coefficient;
        current-> exponent = tmp-> exponent;
        current->next = nullptr;
        tmp = tmp->next;
    }

}

// Polynomial::Polynomial(int array[], int arraySize){
//     Term* current = new Term;
//     head = current;
//     int exp = arraySize-1;
//     // cout<< "exp: " << exp <<endl;
//     for(int i = 0; i < arraySize; i++){
//         if(array[i] != 0){
//             current->coefficient = array[i];
//             // cout<<"coe:"<<current->coefficient<<"\t"<<"array["<<i<<"]"<<array[i];
//             // cout<< "-----exp: " << exp <<endl;
//             current->exponent = exp;
//             current->next = nullptr;
            
//             if(array[i+1] != 0 && exp > 0){
//                 current->next = new Term;
//                 current = current->next; 
//             }
//             exp--;
//         }
//         else
//         {
//             // cout<<"array["<<i<<"]"<<array[i]<<endl;
//             // cout<< "-----exp: " << exp <<endl;
//             if(exp > 0){
//                 exp--;
//                 if(array[i+1] != 0){
//                     current->next = new Term;
//                     current = current->next;
//                 }       
//             }   
//         }   
//     }
// }
Polynomial::Polynomial(int array[], int arraySize){
    int exp = arraySize-1;
    head = nullptr;
    for(int i = 0; i < arraySize; i++){
        Term* current = new Term;
        current->coefficient = array[i];
        current->exponent = exp;
        current->next = nullptr;
        Term* p;
        if(head == nullptr){
            head = current;
        }
        else{
            p = head;
            while(p->next){
                p = p->next;
            }
            p->next = current;
        }
        exp--;
    }
}

Polynomial::~Polynomial(){
    while(head){
        Term * temp = head;
        head = head->next;
        delete temp;
    }
    
}

void Polynomial::print() const{
    int count = 0;
    if(head == nullptr){
        cout<<"0";
    }
    else{
        Term* current = head;
        while(current != nullptr){
            if(current->coefficient != 0){ //ignore 0
                if(current->coefficient < 0){ //-ve
                    if(count == 0){//first
                        if(current->coefficient == -1){//dun print -1
                            if(current->exponent == 1)
                                cout<<"-x";
                            else if(current->exponent > 0 && current->exponent != 1){
                                cout<<"-x";
                                    cout<<"^"<<current->exponent;                
                            }
                            else if  (current->exponent == 0)
                                cout<<"-1";
                        }     
                        else{
                            cout<<current->coefficient;   
                            if(current->exponent > 0){
                                cout<<"*x";
                                if(current->exponent != 1){
                                    cout<<"^"<<current->exponent;
                                }                   
                            }      
                        }
                         
                    }    
                    else{
                        if(current->coefficient == -1){
                            if(current->exponent == 1)
                                cout<<" - x";
                            else if(current->exponent > 0 && current->exponent != 1){
                                cout<<" - x";
                                    cout<<"^"<<current->exponent;                
                            }
                            else if  (current->exponent == 0)
                                cout<<" - 1";
                        }
                        else{
                            cout<<" - "<<current->coefficient*(-1);
                            if(current->exponent > 0){
                                cout<<"*x";
                                if(current->exponent != 1){
                                    cout<<"^"<<current->exponent;
                                }                   
                            }   
                        }
                        
                        
                    }
                }

                else{ //+ve
                    if(current->coefficient == 1 ){ //dun print 1 
                        if(current->exponent == 1)
                            cout<<"x";
                        else if(current->exponent > 1){
                            cout<<"x";
                            cout<<"^"<<current->exponent;                
                        }
                        else if  (current->exponent == 0)
                            cout<<"1";
                    }
                    else
                    {
                        cout<< current->coefficient;
                        if(current->exponent > 0){
                            cout<<"*x";
                            if(current->exponent != 1){
                                cout<<"^"<<current->exponent;
                            }                   
                        }   
                    }    
                       
                }
                count = 1; 
            }
                
            if(current->next != nullptr && count == 1){
                if(current->next->coefficient > 0){
                    cout<<" + ";
                }
            }
            current = current->next;
        }      
    }       
}

Polynomial Polynomial::add(const Polynomial& another)const {
    Term* one = this->head;
    Term* second = another.head;
    Polynomial result_p;
    if(one || second){
        Term* result = new Term;
        result->next = nullptr;
        result_p.head = result;
        while(one && second){
            if(one->exponent > second->exponent){
                result->exponent = one->exponent;
                result->coefficient = one->coefficient;
                one = one->next; 
            }
            else if(one->exponent < second->exponent){
                result->exponent = second->exponent;
                result->coefficient = second->coefficient;
                second = second->next;
            }
            else{
                result->exponent = one->exponent;
                result->coefficient = one->coefficient + second->coefficient;
                one = one->next;
                second = second->next;
            }
            if(one || second){
                result->next = new Term;
                result = result->next;
                result->next = nullptr;
            }
            
        }
        while(one || second){
            if(one){
                result->exponent = one->exponent;
                result->coefficient = one->coefficient;
                one = one->next; 
            }
            if(second){
                result->exponent = second->exponent;
                result->coefficient = second->coefficient;
                second = second->next;
            }
            if(one || second){
                result->next = new Term;
                result = result->next;
                result->next = nullptr;
            }
        }  
        
    }
    return result_p;  
    
}

Polynomial Polynomial::subtract(const Polynomial& another) const{
    Term* one = this->head;
    Term* second = another.head;
    Polynomial result_p;
    if(one || second){
        Term* result = new Term;
        result->next = nullptr;
        result_p.head = result;
 
        while(one && second){
            if(one->exponent > second->exponent){
                result->exponent = one->exponent;
                result->coefficient = one->coefficient;
                one = one->next; 
            }
            else if(one->exponent < second->exponent){
                result->exponent = second->exponent;
                result->coefficient = second->coefficient*(-1);
                second = second->next;
            }
            else{
                result->exponent = one->exponent;
                result->coefficient = one->coefficient - second->coefficient;
                one = one->next;
                second = second->next;
            }
            if(one || second){
                result->next = new Term;
                result = result->next;
                result->next = nullptr;
            }
            
        }
        while(one || second){
            if(one){
                result->exponent = one->exponent;
                result->coefficient = one->coefficient;
                one = one->next; 
            }
            if(second){
                result->exponent = second->exponent;
                result->coefficient = second->coefficient*(-1);;
                second = second->next;
            }
            if(one || second){
                result->next = new Term;
                result = result->next;
                result->next = nullptr;
            }
        } 
    } 
    return result_p;  
}

Polynomial Polynomial::multiply(const Polynomial& another) const{
    Term* one = this->head;
    Term* second = another.head;
    Polynomial result_p;
    if(one || second){
        Term* result = new Term;
        result->next = nullptr;
        result_p.head = result;
        while(one != nullptr){//multiply
            while(second != nullptr){
                result->coefficient = one->coefficient * second->coefficient;
                result->exponent = one->exponent + second->exponent;
                if(second->next || one->next){
                    result->next = new Term;
                    result = result->next;
                    result->next = nullptr;
                }
                second = second->next;
            }
            second = another.head;
            one = one->next;
        }

        //combine same exp
        Term* p = result_p.head;
        Term* remove;
        while(p && p->next){
            Term* p2 = p;
            while(p2->next){
                if(p->exponent == p2->next->exponent){
                    p->coefficient = p->coefficient + p2->next->coefficient;
                    remove = p2->next;
                    p2->next = p2->next->next;
                    delete remove;
                }
                else
                {
                    p2 = p2->next;
                }   
            }
            p = p->next;
        }

        //sorting
        Term* current = result_p.head;
        Term* after;
        while(current){
            after = current->next;
            while(after){
                if(current->exponent < after->exponent){
                    Term* temp = new Term;
                    temp->exponent = current->exponent;
                    current->exponent = after->exponent;
                    after->exponent = temp->exponent;
                    temp->coefficient = current->coefficient;
                    current->coefficient = after->coefficient;
                    after->coefficient = temp->coefficient;
                    delete temp;
                }
                after = after->next;
            }
            current = current->next;
        }
        
    }
    return result_p; 
}

int Polynomial::evaluate(int valueOfX) const{
    int x = valueOfX;
    int ans = 0;
    Term* p = head;
    while(p){
        ans += p->coefficient * power(x,p->exponent);
        //cout<<"ans: "<< ans<<endl;
        p = p->next;
    }

    return ans;
}

int Polynomial::compare(const Polynomial& another) const{
    Term* one = this->head;
    Term* second = another.head;
    while(one || second){
        if(one->exponent > second->exponent){
            return 1;
        }
        else if (one->exponent < second->exponent){
            return -1;
        }
        else if(one->exponent == second->exponent){
            if(one->coefficient > second->coefficient){
                return 1;
            }
            else if(one->coefficient < second->coefficient){
                return -1;
            }
            else{
                one = one->next;
                second = second->next;
            }
        }
        if(one && second == nullptr){
            return 1;
        }
        else if(one == nullptr && second){
            return -1;
        }
        
    }
    return 0;
}