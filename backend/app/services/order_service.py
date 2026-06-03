from backend.Cpp_files.bindings import myengine
from ..engine.engine_instance import engine

def create_order(order_id : int, symbol, side, orderType, price, quantity):
    cpp_side = getattr(myengine.Side, side.value)
    cpp_OrderType = getattr(myengine.OrderType, orderType.value)
    return myengine.Order(order_id, symbol, cpp_side, cpp_OrderType, price, quantity) 

def process_order(Order: myengine.Order): 
    if(Order.get_order_type() == myengine.OrderType.LIMIT): 
        return engine.submit_limit_order(Order)
    elif Order.get_order_type() == myengine.OrderType.MARKET: 
        return engine.submit_market_order(Order)
    return False; 