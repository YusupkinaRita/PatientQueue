#pragma once


template<class T>
struct Node{
    T Data;
    Node* Next=nullptr;
    Node(const T data) {
        Data = data;
    }
};

template<class T>   
class QueueList{
private:
    Node<T>* _head ;
    Node<T>* _tail;
    size_t _size=0;
public:
    QueueList(){
        _head=nullptr;
        _tail=nullptr;
    }


    void Push(const T data){
        if(_head==nullptr){
            _head=new Node<T>(data);
            _tail=_head;
        }
        else{
            Node<T>* newTail=new Node(data);
            _tail->Next=newTail;
            _tail=newTail;
        }
        _size++;
    }

    void Pop(){
        if(_head==nullptr)
            throw "queue is empty";
        _size--;
        if(_head==_tail){
            delete _head;
            _head=nullptr;
            _tail=nullptr;
            return;
        }
        Node<T>* tmp=_head;
        _head=_head->Next;
        delete tmp;
    }

    const T& Front(){
        if(_head==nullptr)
            throw "queue is empty";
        return _head->Data;
    }

    bool Empty(){
        return _head==nullptr;
    }

    size_t GetSize()const{
        return _size;
    }

    




};