from pydantic import BaseModel

class getSymbolResponse(BaseModel): 
    symbols : list[str]
