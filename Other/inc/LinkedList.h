#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <iostream>
#include <memory>


// Generic single linked list implementation using smart pointers


// Node
template <typename T>
class Node
{
public:
    using NodeSPtr = std::shared_ptr<Node<T>>;
    Node(T t)
        : _t{ t }
    {}
    ~Node()
    {
        std::cout << "Destroying Node: " << _t << "\n";
    }
    void reset_next()
    {
        _next.reset();
    }
    void set_next(NodeSPtr next)
    {
        _next = next;
    }
    NodeSPtr get_next() const
    {
        return _next;
    }
    const T& get() const
    {
        return _t;
    }
private:
    T _t;
    NodeSPtr _next{ };
};


// Linked list
template <typename T>
class LinkedList
{
public:
    using NodeSPtr = std::shared_ptr<Node<T>>;
    NodeSPtr begin() const
    {
        return _head;
    }
    NodeSPtr end() const
    {
        return _tail->get_next();
    }
    NodeSPtr next(const NodeSPtr it) const
    {
        NodeSPtr ret{ it };
        if (it)
        {
            ret = it->get_next();
        }
        return ret;
    }
    void push_front(const T& t)
    {
        NodeSPtr node_sptr = std::make_shared<Node<T>>(t);
        node_sptr->set_next(_head);
        _head = node_sptr;
        if (!_tail)
        {
            _tail = node_sptr;
        }
    }
    void push_back(const T& t)
    {
        NodeSPtr node_sptr = std::make_shared<Node<T>>(t);
        node_sptr->set_next(nullptr);
        if (_tail)
        {
            _tail->set_next(node_sptr);
        }
        _tail = node_sptr;
    }
    void pop_front()
    {
        if (_head)
        {
            _head = _head->get_next();
        }
    }
    void pop_back()
    {
        if (_tail)
        {
            if (_head == _tail)
            {
                _head.reset();
                _tail.reset();
            }
            else
            {
                NodeSPtr node_sptr{ _head };
                while (node_sptr->get_next() != _tail)
                {
                    node_sptr = node_sptr->get_next();
                }
                _tail = node_sptr;
                _tail->reset_next();
            }            
        }
    }
    T front()
    {
        T ret{};
        if (_head)
        {
            ret = _head->get();
        }
        return ret;
    }
    T back()
    {
        T ret{};
        if (_tail)
        {
            ret = _tail->get();
        }
        return ret;
    }
    void clear()
    {
        while (_head)
        {
            NodeSPtr tmp{ _head };
            _head = _head->get_next();
            tmp->reset_next();
        }
        _tail.reset();
    }
private:
    size_t _size{ 0 };
    NodeSPtr _head{ };
    NodeSPtr _tail{ };
};


// operator<< for LinkedList
template <typename T>
concept Printable = requires (std::ostream & os, const T & t) { os << t; };

template <Printable T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    os << "{ ";
    bool first{ true };
    for (auto it = list.begin(); it != list.end(); it = list.next(it))
    {
        os << (first ? "" : ", ") << it->get();
        first = false;
    }
    os << " }";
    return os;
}


void linked_list_main();


#endif
