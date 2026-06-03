from fastapi import FastAPI
from backend.app.routes import order_routes
from backend.app.routes import orderbook_routes
from backend.app.engine.engine_instance import engine
from backend.Cpp_files.bindings import myengine

temp_order = myengine.Order(1, "AAPL", myengine.Side.SELL, myengine.OrderType.LIMIT, 100, 10)
engine.submit_limit_order(temp_order)

app = FastAPI()
app.include_router(order_routes.router)
app.include_router(orderbook_routes.router)

@app.get("/")
def home(): 
    return {
        "Message" : "welcome Home"
    }


