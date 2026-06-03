from fastapi import APIRouter
from ..models import order_model
from ..utils import order_validate
from ..services.order_service import *
from ..utils.snowflake_order_id_generator import generate_order_id
router = APIRouter()

@router.post("/order", response_model= order_model.OrderResponse)
def submit_order(order : order_model.OrderRequest): 
    order.symbol = order.symbol.upper()
    order_validate.validate_order(order)
    order_id = generate_order_id()
    cppOrder = create_order(order_id, order.symbol, order.side, order.ordertype, order.price, order.quantity)
    trades = process_order(cppOrder)
    return{
        "status" : "Succesfully added the order", 
        "trades" : trades
    } 
    
