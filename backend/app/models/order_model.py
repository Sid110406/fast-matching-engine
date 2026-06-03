from pydantic import BaseModel, ConfigDict
from enum import Enum
from .trade_model import Trade

class Side(str, Enum): 
    BUY = "BUY"
    SELL = "SELL"

class OrderType(str, Enum): 
    LIMIT = "LIMIT"
    MARKET = "MARKET"

class OrderRequest(BaseModel):
    model_config = ConfigDict(str_strip_whitespace=True) # for removing the white spaces from the strings
    symbol : str
    side : Side
    ordertype : OrderType
    price : int
    quantity : int

class OrderResponse(BaseModel): 
    status : str 
    order_id : int 
    trades : list[Trade]

