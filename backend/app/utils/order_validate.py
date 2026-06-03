from fastapi import HTTPException
from backend.app.engine.engine_instance import engine
from ..models.order_model import OrderRequest
from ..models.order_model import OrderType

MAX_PRICE = 1000000000
MAX_QUANTITY = 1000000000
def validate_price(price : int) -> None: 
    if price <= 0: 
        raise HTTPException(
            status_code=400, 
            detail= "Price must be positive"
        )
    if price > MAX_PRICE: 
        raise HTTPException(
            status_code=400, 
            detail= "Price exceeds the maximum allowed value"
        )
    
def validate_quantity(quantity : int)-> None: 
    if(quantity <= 0): 
        raise HTTPException(
            status_code=400, 
            detail= "Quantity must be positive"
        )
    if quantity > MAX_QUANTITY: 
        raise HTTPException(
            status_code=400, 
            detail="Quantity exceeds the maximum allowed limit"
        )

def validate_symbol(symbol : str) -> None: 
    if not symbol: 
        raise HTTPException(
            status_code = 400,
            detail = "Symbol cannot be empty"
        )
    if not engine.book_exists(symbol): 
        raise HTTPException(
            status_code = 400, 
            detail= "The symbol does not exsits"
        )

def validate_order(Order : OrderRequest): 
    if(Order.ordertype == OrderType.LIMIT): 
        validate_price(Order.price) 
    validate_quantity(Order.quantity)
    validate_symbol(Order.symbol)

