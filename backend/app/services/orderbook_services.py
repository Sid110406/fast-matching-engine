from ..engine.engine_instance import engine

def fetch_orderbooks(): 
    return engine.get_symbols()