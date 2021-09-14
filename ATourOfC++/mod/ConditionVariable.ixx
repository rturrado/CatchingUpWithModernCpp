module;

#include "Random.h"

export module ConditionVariable;

import <boost/uuid/random_generator.hpp>;
import <boost/uuid/uuid.hpp>;
import <boost/uuid/uuid_io.hpp>;
import <condition_variable>;
import <iostream>;
import <mutex>;
import <queue>;
import <thread>;

class Message {  // object to be communicated
public:
    Message() { id_ = uuid_generator(); }
    Message(const Message& other) : id_{ other.id_ } {}
    std::string id() { return boost::uuids::to_string(id_); }
private:
    boost::uuids::random_generator uuid_generator;  // random UUID generator
    boost::uuids::uuid id_{};
};

std::queue<Message> message_queue;  // the queue of messages
std::condition_variable mq_cond_var;  // the variable communicating events
std::mutex mq_mutex;  // for synchronizing access to mq_cond_var

void consumer(size_t number_of_messages)
{
    while (number_of_messages--)
    {
        std::unique_lock lck{ mq_mutex };  // acquire mmutex

        // release lck and wait
        // re-acquire lck upon wakeup
        // don’t wake up unless message_queue is non-empty
        // lck is passed by reference; neither unique_locks nor scoped_locks can be copied
        mq_cond_var.wait(lck, [] { return !message_queue.empty(); });

        auto m = message_queue.front(); // get the message
        message_queue.pop();

        // ... process message ....
        std::cout << "\tConsuming: " << m.id() << "\n";

        // release lck (at end of scope)
    }
}

void producer(size_t number_of_messages)
{
    while (number_of_messages--)
    {
        // ... fill the message ...
        Message m;

        std::scoped_lock lck{ mq_mutex };  // protect operations

        std::cout << "Producing: " << m.id() << "\n";

        message_queue.push(m);
        mq_cond_var.notify_one();  // notify

        // release lock (at end of scope)
    }
}

export void condition_variable_main()
{
    constexpr size_t number_of_messages{ 20 };

    std::thread producer_thread{ producer, number_of_messages };
    std::thread consumer_thread{ consumer, number_of_messages };

    producer_thread.join();
    consumer_thread.join();

    std::cout << "Bye!\n";
}
