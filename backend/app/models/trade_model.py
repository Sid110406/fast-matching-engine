from pydantic import BaseModel

class Trade(BaseModel): 
    buy_order_id:int
    sell_order_id: int
    price : int
    quantity : int