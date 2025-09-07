#include <print>

#include "OrderBook.h"

void OrderBook::AddOrder(Order Order)
{
    // TODO: Sanitize Order and sanity check

    Order.timestamp = HighResClock::now();
    _addOrderQueue.emplace(Order);
}

bool OrderBook::BookOrder()
{
    if (_addOrderQueue.empty())
    {
        // No orders to process
        return false;
    }

    Order newOrder = _addOrderQueue.front();
    _addOrderQueue.pop();

    if (newOrder.type == OrderType::Buy)
    {
        // Check for usable Sell Order
        if (!_sellOrders[newOrder.ticker].empty())
        {
            auto sellOrderIt = _sellOrders[newOrder.ticker].begin();
            // See if top sell order works
            if ((*sellOrderIt).price <= newOrder.price)
            {
                // Resolve Order
                std::println("Matched | Sell Order: {} | Buy Order: {}", (*sellOrderIt).id, newOrder.id);

                // Sell order is complete so remove it
                _sellOrders[newOrder.ticker].erase(sellOrderIt);

                return true;
            }
        }
        
        // Store order
        _buyOrders[newOrder.ticker].insert(newOrder);
    }
    else if(newOrder.type == OrderType::Sell)
    {
        // Check for usable Buy Order
        if (!_buyOrders[newOrder.ticker].empty())
        {
            auto buyOrderIt = _buyOrders[newOrder.ticker].begin();
            // See if top buy order works
            if ((*buyOrderIt).price >= newOrder.price)
            {
                // Resolve Order
                std::println("Matched | Sell Order: {} | Buy Order: {}", newOrder.id, (*buyOrderIt).id);

                // Buy order is complete so remove it
                _buyOrders[newOrder.ticker].erase(buyOrderIt);

                return true;
            }
        }

        // Store order
        _sellOrders[newOrder.ticker].insert(newOrder);
    }
    else
    {
        // Invalid order
        return false;
    }

    return true;
}
