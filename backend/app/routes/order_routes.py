from fastapi import APIRouter
from ..models.order import OrderRequest
from ..models.order import OrderResponse

router = APIRouter()

@router.post("/order", response_model= OrderResponse)
def submit_order(order : OrderRequest): 
    return{
        "status" : order.symbol, 
        "trades" : [{
            "price" : 10, 
            "quantity" : 20
        }, 
        {
            "price" : 20, 
            "quantity" : 10
        }]
    }