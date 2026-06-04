from pydantic import BaseModel, ConfigDict

class CancelResponse(BaseModel): 
    status : str