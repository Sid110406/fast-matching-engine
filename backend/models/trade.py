from pydantic import BaseModel

class Trade(BaseModel): 
    price : int
    quantity : int