from fastapi import APIRouter
from ..services.orderbook_services import *
from ..models.engine_model import getSymbolResponse

router = APIRouter(prefix= "/orderbook")

@router.get("/symbols", response_model= getSymbolResponse)
def get_orderbook(): 
    symbol = fetch_orderbooks(); 
    return{
        "symbols" : symbol
    }