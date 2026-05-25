from pydantic import BaseModel
from enum import Enum
from models.trade import Trade

class Side(str, Enum): 
    BUY = "BUY"
    SELL = "SELL"

class OrderType(str, Enum): 
    LIMIT = "LIMIT"
    MARKET = "MARKET"

class OrderRequest(BaseModel):
    symbol : str
    side : Side
    ordertype : OrderType
    price : int
    quantity : int

class OrderResponse(BaseModel): 
    status : str 
    trades : list[Trade]
