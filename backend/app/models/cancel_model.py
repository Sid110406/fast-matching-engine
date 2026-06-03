from pydantic import BaseModel, ConfigDict

class CancelRequest(BaseModel): 
    model_config = ConfigDict(str_strip_whitespace=True)
    symbol : str
    order_id : int

class CancelResponse(BaseModel): 
    status : str