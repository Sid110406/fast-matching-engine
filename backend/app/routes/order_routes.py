from fastapi import APIRouter
from ..models import order_model
from ..models import cancel_model
from ..models import book_model
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
        "order_id" : order_id,  
        "trades" : trades
    } 

@router.delete("/order/{symbol}/{order_id}", response_model= cancel_model.CancelResponse)
def cancel_order_endpoint(symbol : str, order_id : int):
    symbol = symbol.upper().strip()
    return cancel_order(symbol, order_id)

@router.get("/book/{symbol}/best_buy_price", response_model= book_model.BookBestBuyResponse)
def book_best_buy_price(symbol : str): 
    symbol = symbol.strip()
    symbol = symbol.upper()
    price = get_book_best_buy(symbol)
    return{
        "symbol" : symbol, 
        "best_buy_price" : price
    }

@router.get("/book/{symbol}/best_sell_price", response_model= book_model.BookBestSellResponse)
def book_best_sell_price(symbol : str): 
    symbol = symbol.strip()
    symbol = symbol.upper()
    price = get_book_best_sell(symbol)
    return{
        "symbol" : symbol, 
        "best_sell_price" : price
    }

    
