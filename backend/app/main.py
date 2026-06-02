from fastapi import FastAPI
from backend.app.routes.order_routes import router
from backend.Cpp_files.bindings import myengine

engine = myengine.MatchingEngine()

print(myengine.Side.BUY)
