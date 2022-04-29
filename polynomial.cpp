#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only

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

Polynomial::Polynomial(int array[], int arraySize){
    head = new Term;
    Term* current = head;
    int exp = arraySize-1;
    // cout<< "exp: " << exp <<endl;
    for(int i = 0; i < arraySize; i++){
        if(array[i] != 0){
            current->coefficient = array[i];
            // cout<<"coe:"<<current->coefficient<<"\t"<<"array["<<i<<"]"<<array[i];
            // cout<< "-----exp: " << exp <<endl;
            current->exponent = exp;
            current->next = nullptr;
            exp--;
            if(array[i+1] != 0 && exp > 0){
                current->next = new Term;
                current = current->next; 
            }
            
        }
        else
        {
            // cout<<"array["<<i<<"]"<<array[i]<<endl;
            // cout<< "-----exp: " << exp <<endl;
            if(exp > 0){
                exp--;
                if(array[i+1] != 0){
                    current->next = new Term;
                    current = current->next;
                }       
            }   
        }   
    }
}

Polynomial::~Polynomial(){

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
    Term* result = new Term;
    result->next = nullptr;
    result_p.head = result;
    while(one != nullptr){
        while(second != nullptr){
            result->exponent = one->exponent * second->exponent;
            
        }
    }
    return result_p; 
}