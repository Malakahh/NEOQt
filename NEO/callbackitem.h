#ifndef CALLBACKITEM_H
#define CALLBACKITEM_H

#include <vector>
#include <functional>

class CallbackItem
{
public:
    CallbackItem(std::vector<unsigned char>& q, int bTR, std::function<void (const std::vector<char>)>& c)
    {
        this->query = q;
        this->bytesToRead = bTR;
        this->callback = c;
    }

    std::vector<unsigned char> query;
    int bytesToRead;
    //void (* callback)(const std::vector<char>);
    std::function<void (const std::vector<char>)> callback;
};

#endif // CALLBACKITEM_H
