import sys
import os
backend_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
if backend_dir not in sys.path:
    sys.path.append(backend_dir)

from bindings import myengine

engine = myengine.MatchingEngine()


order1 = myengine.Order(1, "AAPL", myengine.Side.SELL, myengine.OrderType.LIMIT, 10, 10)
order2 = myengine.Order(2, "AAPL", myengine.Side.BUY, myengine.OrderType.LIMIT, 10, 5)

print(myengine.Side.BUY)
trades1 = engine.submit_limit_order(order1)
trades2 = engine.submit_limit_order(order2)

print(trades2[0].sell_order_id)