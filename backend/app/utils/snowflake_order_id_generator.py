from snowflake import SnowflakeGenerator

generator = SnowflakeGenerator(1)

def generate_order_id(): 
    return next(generator)
