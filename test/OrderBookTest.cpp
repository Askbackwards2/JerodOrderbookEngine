#include <exception>
#include <iostream>
#include <print>
#include <cassert>

#include <OrderBook.h>

class OrderBookTest : public OrderBook
{
public:
    SellPage& GetSellOrders()
    {
        return _sellOrders;
    }
    BuyPage& GetBuyOrders()
    {
        return _buyOrders;
    }
    std::queue<Order>& GetOrderQueue()
    {
        return _addOrderQueue;
    }
};

void testOrderBookCreation() 
{
    OrderBook book;
    std::cout << "✓ OrderBook creation test passed" << std::endl;
}

void testAddOrder() 
{
    OrderBookTest book;
    
    // Buy Order 

    Order testOrder;
    testOrder.ticker = "AAPL";
    testOrder.price = 150.0f;
    testOrder.amount = 100;
    testOrder.type = OrderType::Buy;
    
    book.AddOrder(testOrder);
    book.BookOrder();
    auto&& bookBuyOrder = book.GetBuyOrders()["AAPL"].begin();
    assert(bookBuyOrder->ticker == "AAPL");
    assert(bookBuyOrder->price == 150.0f);
    assert(bookBuyOrder->amount == 100);
    assert(testOrder.type == OrderType::Buy);
    std::cout << "✓ Add buy order test passed" << std::endl;

    // Sell Order
    testOrder.ticker = "LOL";
    testOrder.type = OrderType::Sell;
    book.AddOrder(testOrder);
    book.BookOrder();
    auto&& bookSellOrder = book.GetSellOrders()["LOL"].begin();
    assert(bookSellOrder->ticker == "LOL");
    assert(bookSellOrder->price == 150.0f);
    assert(bookSellOrder->amount == 100);
    assert(testOrder.type == OrderType::Sell);
    std::cout << "✓ Add sell order test passed" << std::endl;

    // Invalid Order

    // TODO: Sanitize input 
}

void testBookOrder()
{
    OrderBookTest book;

    Order testOrder;
    testOrder.ticker = "AAPL";
    testOrder.price = 150.0f;
    testOrder.amount = 100;
    testOrder.type = OrderType::Buy;

    book.AddOrder(testOrder);
    testOrder.type = OrderType::Sell;
    book.AddOrder(testOrder);
    book.BookOrder();
    book.BookOrder();

    assert(book.GetBuyOrders()["AAPL"].size() == 0);
    assert(book.GetSellOrders()["AAPL"].size() == 0);

    // TODO: Test large sizes
    // TODO: Test Engine resolution
}

int main()
{
    try 
    {
        printf("Starting OrderBook Tests...\n");

        testOrderBookCreation();
        testAddOrder();
        testBookOrder();

        printf("All tests passed!\n");

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}