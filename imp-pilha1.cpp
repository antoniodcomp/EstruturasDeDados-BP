#include <iostream>
#include <memory>


using namespace std;

class Node{

public:
    int data;
    unique_ptr<Node> next;

    Node(int d): data(d), next(nullptr){};
};

class PilhaLinkedList{

public:
    unique_ptr<Node> head;

    PilhaLinkedList(): head(nullptr){};


    bool stackEmpty(){
        if(head == nullptr) return true;
        else return false;
    }

    void push(int d){

    if(head == nullptr){
      unique_ptr<Node> ptr = make_unique<Node>(d);
      ptr->next = move(head);
      head = move(ptr);
     }

    else {
     Node *ptr = head.get();

        while(ptr->next != nullptr){
            ptr=ptr->next.get();
        }

      unique_ptr<Node> newNode = make_unique<Node>(d);
      ptr->next = move(newNode);
     }
    }

    void isTranversal(){

    Node* ptr = head.get();

     while(ptr != nullptr){
        cout <<ptr->data << "->";
        ptr=ptr->next.get();
     }
     cout << "NULL";
    }

    int pop(){
     Node* ptr = head.get();
     int x;

     if(stackEmpty()){
        cout << "Pilha esta vazia" <<endl;
        return -1;
     }

     if(ptr->next == nullptr){
        x = ptr->data;
        head = nullptr;
     }
     else {
      while(ptr->next->next != nullptr){
        ptr = ptr->next.get();
      }
      // quando o loop terminar eu já vou ter chegado ao final da lista.
       x = move(ptr->next->data);
       ptr->next = move(nullptr);

       return x;
     }
    }

};


class FilaLinkedList{

public:
    unique_ptr<Node> head;

    FilaLinkedList(): head(nullptr){};

    void enqueue(int d){

         if(head == nullptr){
          unique_ptr<Node> ptr = make_unique<Node>(d);
          ptr->next = move(head);
          head = move(ptr);
         }

        else {
         Node *ptr = head.get();

            while(ptr->next != nullptr){
                ptr=ptr->next.get();
            }

          unique_ptr<Node> newNode = make_unique<Node>(d);
          ptr->next = move(newNode);
         }
    }

    int dequeue(){

        if (head == nullptr) {
        cout << "Erro: Fila vazia!\n";
        return -1; // ou algum valor para indicar erro
        }

        int x = move(head->data);
        head= move(head->next);
        return x;
    }

    void isTranversal(){

    Node* ptr = head.get();

     while(ptr != nullptr){
        cout <<ptr->data << "->";
        ptr=ptr->next.get();
     }
     cout << "NULL";
    }

};


int main(){

    PilhaLinkedList p;
    FilaLinkedList F;

    p.pop();
    p.isTranversal();
return 0;
}
