#pragma once
#include<pybind11/pybind11.h>
#include<pybind11/stl.h>

#include "../core/MatchingEngine.h"
#include "../core/OrderBook.h"

namespace py = pybind11; 

PYBIND11_MODULE(myengine, m)
{
    py::enum_<Side>(m, "Side").value("BUY", Side::BUY).value("SELL", Side::SELL); 

    py::enum_<OrderType>(m, "OrderType")
    .value("LIMIT", OrderType::LIMIT)
    .value("MARKET", OrderType::MARKET);

    py::class_<Trade>(m, "Trade")
    .def_readonly("buy_order_id", &Trade::buy_order_id)
    .def_readonly("sell_order_id", &Trade::sell_order_id)
    .def_readonly("price", &Trade::price)
    .def_readonly("quantity", &Trade::quantity); 

    py::class_<MatchingEngine>(m, "MatchingEngine")
    .def(py::init<>())
    .def("submit_limit_order", &MatchingEngine::submit_limit_order)
    .def("submit_market_order", &MatchingEngine::submit_market_order)
    .def("cancel_order", &MatchingEngine::cancel_order)
    .def("best_buy_price", &MatchingEngine::best_buy_price)
    .def("best_sell_price", &MatchingEngine::best_sell_price);

    py::class_<Order>(m, "Order")
    .def(py::init<uint64_t, std::string, Side, OrderType, int, int>()); 
}
