from pydantic import BaseModel

class BookBestBuyResponse(BaseModel):
    symbol : str 
    best_buy_price : int

class BookBestSellResponse(BaseModel):
    symbol : str
    best_sell_price : int