// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <list>


class user_twit
{
public:
    typedef std::string Message;
    typedef std::list<size_t> Followers;
    typedef std::map<size_t, Message> Messages;

    bool add_message(size_t user_id, size_t timestamp, Message& message)
    {
        std::map<size_t, Messages >::iterator it = m_storage.find(user_id);
        if (it != m_storage.end())
        {
            it->second.insert(std::make_pair(timestamp , message));
        }
        else
        {
            Messages my_msg;
            my_msg.insert(std::make_pair(timestamp, message));
            m_storage.insert(std::make_pair(user_id, my_msg));
        }

        return true;
    }

    bool add_follower(size_t user_id, size_t follower_id)
    {
        std::map<size_t, Followers>::iterator it = m_followers.find(user_id);
        if (it != m_followers.end())
        {
            it->second.insert(it->second.begin(), follower_id);
        }
        else
        {
            Followers my_flrs;
            my_flrs.insert(my_flrs.begin(), follower_id);
            m_followers.insert(std::make_pair(user_id, my_flrs));
        }
        return true;
    }

    bool get_messages(size_t user_id, Messages& messages, size_t count)
    {
        std::map<size_t, Messages >::iterator it = m_storage.find(user_id);
        if (it != m_storage.end())
        {
            auto msg_it = it->second.begin();
            for (size_t i = 0; i < count; i++)
            {
                if (msg_it == it->second.end()) break;

                messages.insert(messages.begin(), *msg_it);
                msg_it++;
            }

            return true;
        }

        return false;
    }
    bool get_messages_with_followers(size_t user_id, Messages& messages, size_t count)
    {
        std::map<size_t, Followers>::iterator it_flwrs = m_followers.find(user_id);

        Messages msgs;

        while (it_flwrs != m_followers.end())
        {
            for (auto flr_it = it_flwrs.begin(); flr_it != it_flwrs.end(); it_flwrs++)
            {
                get_messages(*flr_it, msgs, count);
            }
        }

        get_messages(user_id, msgs, count);


        auto it = msgs.begin();
        for (size_t n = 0; n < count; n++)
        {
            if (it == msgs.end()) break;
            messages.insert(*it);
        }

        return true;
    }

protected:
    std::map<size_t, Messages > m_storage;
    std::map<size_t, Followers> m_followers;

};

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
