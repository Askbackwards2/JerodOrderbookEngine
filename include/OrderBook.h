#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include <set>
#include <chrono>
#include <queue>

using Dollar = float;
using Quantity = std::uint32_t;
using HighResClock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

enum OrderType
{
    Invalid,
    Buy,
    Sell
};

struct Order
{
    std::string id = "";
    std::string ticker = "";
    Dollar price = 0;
    Quantity amount = 0;
    OrderType type = OrderType::Invalid;
    TimePoint timestamp = TimePoint::min();
};

struct BuyOrderComparator
{
    bool operator()(const Order& lhs, const Order& rhs) const
    {
        if (lhs.price == rhs.price)
        {
            return lhs.timestamp > rhs.timestamp;
        }
        return lhs.price > rhs.price;
    }
};

struct SellOrderComparator
{
    bool operator()(const Order& lhs, const Order& rhs) const
    {
        if (lhs.price == rhs.price)
        {
            return lhs.timestamp > rhs.timestamp;
        }
        return lhs.price < rhs.price;
    }
};

using BuyPage = std::unordered_map<std::string, std::multiset<Order, BuyOrderComparator>>;
using SellPage = std::unordered_map<std::string, std::multiset<Order, SellOrderComparator>>;

class OrderBook
{
public:
    void AddOrder(Order Order);
    bool BookOrder();

private:

public:
    friend class OrderBookTest;

private:
    std::queue<Order> _addOrderQueue;
    BuyPage _buyOrders;
    SellPage _sellOrders;
};  

#endif